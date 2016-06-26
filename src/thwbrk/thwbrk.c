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
 * thwbrk.c - Thai word break routine, wide char version
 * Created 2001-07-15
 * Author:  Theppitak Karoonboonyanan <theppitak@gmail.com>
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#include <thai/thailib.h>
#include <thai/thwchar.h>
#include <thai/thbrk.h>


/**
 * @brief  Find word break positions in Thai wide-char string
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
th_brk_wc_find_breaks (ThBrk *brk, const thwchar_t *s, int pos[], size_t pos_sz)
{
    thchar_t*   tis_str;
    size_t      alloc_size;
    int         ret;

    /* convert to tis-620 string */
    alloc_size = wcslen (s) + 1;
    tis_str = malloc (alloc_size);
    if (!tis_str)
        return 0;
    th_uni2tis_line (s, tis_str, alloc_size);

    /* do word break */
    ret = th_brk_find_breaks (brk, tis_str, pos, pos_sz);

    free (tis_str);

    return ret;
}

/**
 * @brief  Insert word delimitors in given wide-char string
 *
 * @param  brk : the word breaker
 * @param  in  : the input wide-char string to be processed
 * @param  out : the output wide-char buffer
 * @param  out_sz : the size of @a out (as number of elements)
 * @param  delim : the wide-char word delimitor to insert
 *
 * @return  the actual size of the processed string (as number of elements)
 *
 * Analyzes the input string and store the string in output buffer
 * with the given word delimitor inserted at every word boundary.
 *
 * (Available since version 0.1.25, libthai.so.0.3.0)
 */
int
th_brk_wc_insert_breaks (ThBrk *brk, const thwchar_t *in,
                         thwchar_t *out, size_t out_sz,
                         const thwchar_t* delim)
{
    int        *brk_pos;
    size_t      n_brk_pos, i, j;
    int         delim_len;
    thwchar_t  *p_out;

    n_brk_pos = wcslen (in);
    if (n_brk_pos > SIZE_MAX / sizeof (int))
        return 0;
    brk_pos = (int *) malloc (n_brk_pos * sizeof (int));
    if (!brk_pos)
        return 0;

    n_brk_pos = th_brk_wc_find_breaks (brk, in, brk_pos, n_brk_pos);

    delim_len = wcslen (delim);
    for (i = j = 0, p_out = out; out_sz > 1 && i < n_brk_pos; i++) {
        while (out_sz > 1 && j < brk_pos[i]) {
            *p_out++ = in[j++];
            --out_sz;
        }
        if (out_sz > delim_len + 1) {
            wcscpy (p_out, delim);
            p_out += delim_len;
            out_sz -= delim_len;
        }
    }
    while (out_sz > 1 && in [j]) {
        *p_out++ = in[j++];
        --out_sz;
    }
    *p_out = 0;

    free (brk_pos);

    return p_out - out;
}

/**
 * @brief  Find word break positions in Thai wide-char string
 *
 * @param  s   : the input string to be processed
 * @param  pos : array to keep breaking positions
 * @param  pos_sz : size of @a pos[]
 *
 * @return  the actual number of breaking positions occurred
 *
 * Finds word break positions in Thai string @a s and stores at most @a pos_sz
 * breaking positions in @a pos[], from left to right.
 * Uses the shared word breaker.
 *
 * (This function is deprecated since version 0.1.25, in favor of
 * th_brk_wc_find_breaks(), which is more thread-safe.)
 */
int
th_wbrk (const thwchar_t *s, int pos[], size_t pos_sz)
{
    return th_brk_wc_find_breaks ((ThBrk *) NULL, s, pos, pos_sz);
}

/**
 * @brief  Insert word delimitors in given wide-char string
 *
 * @param  in  : the input wide-char string to be processed
 * @param  out : the output wide-char buffer
 * @param  out_sz : the size of @a out (as number of elements)
 * @param  delim : the wide-char word delimitor to insert
 *
 * @return  the actual size of the processed string (as number of elements)
 *
 * Analyzes the input string and store the string in output buffer
 * with the given word delimitor inserted at every word boundary.
 * Uses the shared word breaker.
 *
 * (This function is deprecated since version 0.1.25, in favor of
 * th_brk_wc_insert_breaks(), which is more thread-safe.)
 */
int
th_wbrk_line (const thwchar_t *in, thwchar_t *out, size_t out_sz,
              const thwchar_t* delim )
{
    return th_brk_wc_insert_breaks ((ThBrk *) NULL, in, out, out_sz, delim);
}

/*
vi:ts=4:ai:expandtab
*/
