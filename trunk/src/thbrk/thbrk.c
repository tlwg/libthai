/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * libthai - Thai Language Support Library
 * Copyright (C) 2001  Theppitak Karoonboonyanan <thep@linux.thai.net>
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
 * Author:  Theppitak Karoonboonyanan <thep@linux.thai.net>
 */

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <thai/tis.h>
#include <thai/thctype.h>
#include <thai/thbrk.h>
#include "thbrk-private.h"
#include "brk-ctype.h"
#include "brk-maximal.h"

#define DICT_NAME   "thbrk"

#define MAX_ACRONYM_FRAG_LEN  3

static Trie *thbrk_dict = 0;

void
thbrk_on_unload ()
{
    if (thbrk_dict) {
        trie_free (thbrk_dict);
    }
}

Trie *
thbrk_get_dict ()
{
    static int is_dict_tried = 0;

    if (!thbrk_dict && !is_dict_tried) {
        const char *dict_dir;
        char        path[512];

        /* Try LIBTHAI_DICTDIR env first */
        if (NULL != (dict_dir = getenv ("LIBTHAI_DICTDIR"))) {
            snprintf (path, sizeof path, "%s/%s.tri", dict_dir, DICT_NAME);
            thbrk_dict = trie_new_from_file (path);
        }

        /* Then, fall back to default DICT_DIR macro */
        if (!thbrk_dict) {
            thbrk_dict = trie_new_from_file (DICT_DIR "/" DICT_NAME ".tri");
        }

        if (!thbrk_dict) {
            if (dict_dir) {
                fprintf (stderr,
                         "LibThai: Fail to open dictionary at '%s' and '%s'.\n",
                         path, DICT_DIR "/" DICT_NAME ".tri");
            } else {
                fprintf (stderr,
                         "LibThai: Fail to open dictionary at '%s'.\n",
                         DICT_DIR "/" DICT_NAME ".tri");
            }
        }

        is_dict_tried = 1;
    }

    return thbrk_dict;
}

void
thbrk_brkpos_hints (const thchar_t *str, int len, char *hints)
{
    int  i;

    if (len < 0)
        len = strlen ((const char *)str);

    memset (hints, 0, len);

    for (i = 0; i < len; /* nop */) {
        if (th_isthcons (str[i])) {
            if (i+1 < len && str[i+1] == TIS_THANTHAKHAT) {
                i += 2; /* the cons + THANTHAKHAT */
            } else if (i+2 < len && str[i+2] == TIS_THANTHAKHAT) {
                i += 3; /* the cons + intermediate char + THANTHAKHAT */
            } else if (i+2 < len
                       && str[i] != TIS_KO_KAI && str[i+1] == TIS_MAITAIKHU
                       && (str[i+2] == TIS_O_ANG || str[i+2] == TIS_WO_WAEN))
            {
                hints[i] = 1;
                i += 4; /* the cons + MAITAIKHU + OANG/WOWAEN + cons */
            } else if ((i > 0
                        && (str[i-1] == TIS_MAI_HAN_AKAT
                            || str[i-1] == TIS_SARA_UEE))
                       || (i > 1 && th_isthtone (str[i-1])
                           && (str[i-2] == TIS_MAI_HAN_AKAT
                               || str[i-2] == TIS_SARA_UEE)))
            {
                i++;
            } else {
                hints[i++] = 1;
            }
        } else if (str[i] == TIS_SARA_E || str[i] == TIS_SARA_AE) {
            hints[i] = 1; /* sara e/ae */
            i += 2; /* sara e/ae + the supposedly cons */
            if (i >= len)
                break;
            if (str[i] == TIS_MAITAIKHU) {
                i += 2; /* MAITAIKHU + the supposedly cons */
            } else if (th_isupvowel (str[i])) {
                i++; /* the upper vowel, as part of composite vowel */
                if (i < len && th_isthtone (str[i]))
                    i++;
                i++; /* the supposedly cons */
            } else if (i+2 < len
                       && ((str[i+1] == TIS_SARA_AA && str[i+2] == TIS_SARA_A)
                            || (str[i] != TIS_KO_KAI
                                && str[i+1] == TIS_MAITAIKHU
                                && str[i+2] != TIS_O_ANG
                                && str[i+2] != TIS_WO_WAEN)))
            {
                i += 3; /* 2nd cons + SARA_AA + SARA_A, or
                         * 2nd cons + MAITAIKHU + final cons
                         */
            }
        } else if (th_isldvowel (str[i])) {
            hints[i] = 1; /* the ldvowel */
            i += 2; /* the ldvowel + the supposedly cons */
        } else if (str[i] == TIS_RU || str[i] == TIS_LU) {
            hints[i++] = 1;
        } else {
            i++;
        }
    }
}

/**
 * @brief  Insert word delimitors in given string
 *
 * @param  in  : the input string to be processed
 * @param  out : the output buffer
 * @param  n   : the size of @a out
 * @param  delim : the word delimitor to insert
 *
 * @return  the actual size of the processed string
 *
 * Analyzes the input string and store the string in output buffer
 * with the given word delimitor inserted at every word boundary.
 */
int
th_brk_line (const thchar_t *in, thchar_t *out, size_t n, const char *delim)
{
    int        *brk_pos;
    size_t      n_brk_pos, i, j;
    int         delim_len;
    thchar_t   *p_out;

    n_brk_pos = strlen ((const char *) in);
    if (n_brk_pos > SIZE_MAX / sizeof (int))
        return 0;
    brk_pos = (int *) malloc (n_brk_pos * sizeof (int));
    if (!brk_pos)
        return 0;

    n_brk_pos = th_brk (in, brk_pos, n_brk_pos);
    
    delim_len = strlen (delim);
    for (i = j = 0, p_out = out; n > 1 && i < n_brk_pos; i++) {
        while (n > 1 && j < brk_pos[i]) {
            *p_out++ = in [j++];
            --n;
        }
        if (n > delim_len + 1) {
            strcpy ((char *) p_out, delim);
            p_out += delim_len;
            n -= delim_len;
        }
    }
    while (n > 1 && in [j]) {
        *p_out++ = in [j++];
        --n;
    }
    *p_out = '\0';

    free (brk_pos);

    return p_out - out;
}

/**
 * @brief  Find word break positions in Thai string
 *
 * @param  s   : the input string to be processed
 * @param  pos : array to keep breaking positions
 * @param  n   : size of @a pos[]
 *
 * @return  the actual number of breaking positions occurred
 *
 * Finds word break positions in Thai string @a s and stores at most @a n 
 * breaking positions in @a pos[], from left to right.
 */
int
th_brk (const thchar_t *s, int pos[], size_t n)
{
    brk_class_t     prev_class, effective_class;
    const thchar_t *thai_chunk, *acronym_end, *p;
    int             cur_pos;

    if (!*s)
        return 0;

    brk_maximal_init ();

    p = thai_chunk = acronym_end = s;
    prev_class = effective_class = brk_class (*p);
    cur_pos = 0;

    while (*++p && cur_pos < n) {
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
                                        pos + cur_pos, n - cur_pos);
                for (i = 0; i < n_brk; i++)
                    pos [cur_pos + i] += thai_chunk - s;
                cur_pos += n_brk;

                /* remove last break if at string end
                 * note that even if it's allowed, the table-lookup
                 * operation below will take care of it anyway
                 */
                if (pos[cur_pos - 1] == p - s)
                    --cur_pos;

                if (cur_pos >= n)
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
        && cur_pos < n)
    {
        int n_brk, i;

        n_brk = brk_maximal_do (thai_chunk, p - thai_chunk,
                                pos + cur_pos, n - cur_pos);
        for (i = 0; i < n_brk; i++)
            pos [cur_pos + i] += thai_chunk - s;
        cur_pos += n_brk;

        /* remove last break if at string end */
        if (pos[cur_pos - 1] == p - s)
            --cur_pos;
    }

    brk_maximal_quit ();

    return cur_pos;
}


/*
vi:ts=4:ai:expandtab
*/
