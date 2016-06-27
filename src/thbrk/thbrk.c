/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * libthai - Thai Language Support Library
 * Copyright (C) 2001  Theppitak Karoonboonyanan <theppitak@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

/*
 * thbrk.c - Thai word break routine
 * Created: 2006-08-20
 * Author:  Theppitak Karoonboonyanan <theppitak@gmail.com>
 */

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <datrie/trie.h>
#include <thai/tis.h>
#include <thai/thctype.h>
#include <thai/thbrk.h>
#include "thbrk-priv.h"
#include "thbrk-utils.h"
#include "brk-ctype.h"
#include "brk-maximal.h"
#include "brk-common.h"

#define MAX_ACRONYM_FRAG_LEN  3

/**
 * @brief  Create a dictionary-based word breaker
 *
 * @param  dictpath : the dictionary path, or NULL for default
 *
 * @return  the created instance, or NULL on failure
 *
 * Loads the dictionary from the given file and returns the created word
 * breaker. If @a dictpath is NULL, first searches in the directory given
 * by the LIBTHAI_DICTDIR environment variable, then in the library
 * installation directory. Returns NULL if the dictionary file is not
 * found or cannot be loaded.
 *
 * The returned ThBrk object should be destroyed after use using
 * th_brk_delete().
 *
 * In multi-thread environments, th_brk_new() and th_brk_delete()
 * should be used to create and destroy a word breaker instance inside
 * critical sections (i.e. with mutex). And the word breaker methods
 * can then be safely called in parallel during its lifetime.
 *
 * (Available since version 0.1.25, libthai.so.0.3.0)
 */
ThBrk *
th_brk_new (const char *dictpath)
{
    ThBrk *     brk;
    Trie *      dict_trie;

    brk = (ThBrk *) malloc (sizeof (ThBrk));
    if (UNLIKELY (!brk)) {
        return NULL;
    }

    if (dictpath) {
        dict_trie = trie_new_from_file (dictpath);
    } else {
        dict_trie = brk_load_default_dict ();
    }
    if (UNLIKELY (!dict_trie)) {
        free (brk);
        return NULL;
    }

    brk->dict_trie = dict_trie;

    return brk;
}

/**
 * @brief  Delete a word breaker
 *
 * @param  brk : the word breaker
 *
 * Frees memory associated with the word breaker.
 *
 * (Available since version 0.1.25, libthai.so.0.3.0)
 */
void
th_brk_delete (ThBrk *brk)
{
    trie_free (brk->dict_trie);
    free (brk);
}

/**
 * @brief  Insert word delimitors in given string
 *
 * @param  brk : the word breaker
 * @param  in  : the input string to be processed
 * @param  out : the output buffer
 * @param  out_sz : the size of @a out
 * @param  delim  : the word delimitor to insert
 *
 * @return  the actual size of the processed string
 *
 * Analyzes the input string and store the string in output buffer
 * with the given word delimitor inserted at every word boundary.
 *
 * (Available since version 0.1.25, libthai.so.0.3.0)
 */
int
th_brk_insert_breaks (ThBrk *brk, const thchar_t *in,
                      thchar_t *out, size_t out_sz,
                      const char *delim)
{
    int        *brk_pos;
    size_t      n_brk_pos, i, j;
    int         delim_len;
    thchar_t   *p_out;

    n_brk_pos = strlen ((const char *) in);
    if (UNLIKELY (n_brk_pos > SIZE_MAX / sizeof (int)))
        return 0;
    brk_pos = (int *) malloc (n_brk_pos * sizeof (int));
    if (UNLIKELY (!brk_pos))
        return 0;

    n_brk_pos = th_brk_find_breaks (brk, in, brk_pos, n_brk_pos);

    delim_len = strlen (delim);
    for (i = j = 0, p_out = out; out_sz > 1 && i < n_brk_pos; i++) {
        while (out_sz > 1 && j < brk_pos[i]) {
            *p_out++ = in [j++];
            --out_sz;
        }
        if (out_sz > delim_len + 1) {
            strcpy ((char *) p_out, delim);
            p_out += delim_len;
            out_sz -= delim_len;
        }
    }
    while (out_sz > 1 && in [j]) {
        *p_out++ = in [j++];
        --out_sz;
    }
    *p_out = '\0';

    free (brk_pos);

    return p_out - out;
}

/**
 * @brief  Find word break positions in Thai string
 *
 * @param  brk : the word breaker
 * @param  s   : the input string to be processed
 * @param  pos : array to keep breaking positions
 * @param  pos_sz : size of @a pos[]
 *
 * @return  the actual number of breaking positions occurred
 *
 * Finds word break positions in Thai string @a s and stores at most @a pos_sz
 * breaking positions in @a pos[], from left to right.
 *
 * (Available since version 0.1.25, libthai.so.0.3.0)
 */
int
th_brk_find_breaks (ThBrk *brk, const thchar_t *s, int pos[], size_t pos_sz)
{
    BrkEnv         *env;
    brk_class_t     prev_class, effective_class;
    const thchar_t *thai_chunk, *acronym_end, *p;
    int             cur_pos;

    if (!*s)
        return 0;

    p = thai_chunk = acronym_end = s;
    prev_class = effective_class = brk_class (*p);
    cur_pos = 0;

    env = brk_env_new (brk ? brk : brk_get_shared_brk ());

    while (*++p && cur_pos < pos_sz) {
        brk_class_t  new_class;
        brk_op_t     op;

        new_class = brk_class (*p);
        op = brk_op (effective_class, new_class);

        if (BRK_CLASS_THAI == prev_class) {
            /* handle acronyms */
            if ('.' == *p && p - acronym_end <= MAX_ACRONYM_FRAG_LEN) {
                /* the fullstop after Thai is part of Thai acronym */
                new_class = BRK_CLASS_THAI;
                acronym_end = p + 1;
            } else if (acronym_end > thai_chunk) {
                /* an acronym was marked */
                if (BRK_CLASS_THAI != new_class
                    || p - acronym_end > MAX_ACRONYM_FRAG_LEN)
                {
                    /* end of Thai chunk or entered non-acronym Thai word,
                     * jump back to the acronym end */
                    prev_class = effective_class = brk_class ('.');
                    p = thai_chunk = acronym_end;
                    new_class = brk_class (*p);
                    op = brk_op (effective_class, new_class);
                }
            }

            /* break chunk if leaving Thai chunk */
            if (BRK_CLASS_THAI != new_class && p > thai_chunk) {
                int n_brk, i;

                n_brk = brk_maximal_do (thai_chunk, p - thai_chunk,
                                        pos + cur_pos, pos_sz - cur_pos, env);
                for (i = 0; i < n_brk; i++)
                    pos [cur_pos + i] += thai_chunk - s;
                cur_pos += n_brk;

                /* remove last break if at string end
                 * note that even if it's allowed, the table-lookup
                 * operation below will take care of it anyway
                 */
                if (LIKELY (cur_pos > 0) && pos[cur_pos - 1] == p - s)
                    --cur_pos;

                if (cur_pos >= pos_sz)
                    break;
            }
        } else {
            /* set chunk if entering Thai chunk */
            if (BRK_CLASS_THAI == new_class)
                thai_chunk = acronym_end = p;
        }

        switch (op) {
        case BRK_OP_ALLOWED:
            if ('\n' == *p && '\r' == *(p - 1))
                break;

            pos [cur_pos++] = p - s;
            break;
        case BRK_OP_INDIRECT:
            /* assert (BRK_CLASS_SPACE != new_class); */
            if (BRK_CLASS_SPACE == prev_class)
                pos [cur_pos++] = p - s;
            break;
        default:
            break;
        }

        prev_class = new_class;
        if (BRK_OP_ALLOWED == op || BRK_CLASS_SPACE != new_class)
            effective_class = new_class;
    }

    /* break last Thai non-acronym chunk */
    if (BRK_CLASS_THAI == prev_class && acronym_end <= thai_chunk
        && cur_pos < pos_sz)
    {
        int n_brk, i;

        n_brk = brk_maximal_do (thai_chunk, p - thai_chunk,
                                pos + cur_pos, pos_sz - cur_pos, env);
        for (i = 0; i < n_brk; i++)
            pos [cur_pos + i] += thai_chunk - s;
        cur_pos += n_brk;

        /* remove last break if at string end */
        if (pos[cur_pos - 1] == p - s)
            --cur_pos;
    }

    brk_env_free (env);

    return cur_pos;
}

/**
 * @brief  Insert word delimitors in given string
 *
 * @param  in  : the input string to be processed
 * @param  out : the output buffer
 * @param  out_sz : the size of @a out
 * @param  delim  : the word delimitor to insert
 *
 * @return  the actual size of the processed string
 *
 * Analyzes the input string and store the string in output buffer
 * with the given word delimitor inserted at every word boundary.
 * Uses the shared word breaker.
 *
 * (This function is deprecated since version 0.1.25, in favor of
 * th_brk_insert_breaks(), which is more thread-safe.)
 */
int
th_brk_line (const thchar_t *in, thchar_t *out, size_t out_sz,
             const char *delim)
{
    return th_brk_insert_breaks ((ThBrk *) NULL, in, out, out_sz, delim);
}

/**
 * @brief  Find word break positions in Thai string
 *
 * @param  s   : the input string to be processed
 * @param  pos : array to keep breaking positions
 * @param  pos_sz : size of @a pos[]
 *
 * @return  the actual number of breaking positions occurred
 *
 * Finds word break positions in Thai string @a s and stores at most @a n
 * breaking positions in @a pos[], from left to right.
 * Uses the shared word breaker.
 *
 * (This function is deprecated since version 0.1.25, in favor of
 * th_brk_find_breaks(), which is more thread-safe.)
 */
int
th_brk (const thchar_t *s, int pos[], size_t pos_sz)
{
    return th_brk_find_breaks ((ThBrk *) NULL, s, pos, pos_sz);
}

static ThBrk *brk_shared_brk = NULL;

ThBrk *
brk_get_shared_brk ()
{
    static int is_tried = 0;

    if (UNLIKELY (!brk_shared_brk && !is_tried)) {
        brk_shared_brk = th_brk_new (NULL);
    }

    return brk_shared_brk;
}

void
brk_free_shared_brk ()
{
    if (brk_shared_brk) {
        th_brk_delete (brk_shared_brk);
        brk_shared_brk = NULL;
    }
}

/*
vi:ts=4:ai:expandtab
*/
