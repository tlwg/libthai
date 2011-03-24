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
 * thwbrk.c - Thai word break routine, wide char version
 * Created 2001-07-15
 * Author:  Theppitak Karoonboonyanan <thep@linux.thai.net>
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
th_wbrk (const thwchar_t *s, int pos[], size_t n)
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
    ret = th_brk (tis_str, pos, n);

    free (tis_str);

    return ret;
}

/**
 * @brief  Insert word delimitors in given wide-char string
 *
 * @param  in  : the input wide-char string to be processed
 * @param  out : the output wide-char buffer
 * @param  n   : the size of @a out (as number of elements)
 * @param  delim : the wide-char word delimitor to insert
 *
 * @return  the actual size of the processed string (as number of elements)
 *
 * Analyzes the input string and store the string in output buffer
 * with the given word delimitor inserted at every word boundary.
 */
int
th_wbrk_line (const thwchar_t *in, thwchar_t *out, size_t n,
              const thwchar_t* delim )
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

    n_brk_pos = th_wbrk (in, brk_pos, n_brk_pos);
    
    delim_len = wcslen (delim);
    for (i = j = 0, p_out = out; n > 1 && i < n_brk_pos; i++) {
        while (n > 1 && j < brk_pos[i]) {
            *p_out++ = in[j++];
            --n;
        }
        if (n > delim_len + 1) {
            wcscpy (p_out, delim);
            p_out += delim_len;
            n -= delim_len;
        }
    }
    while (n > 1 && in [j]) {
        *p_out++ = in[j++];
        --n;
    }
    *p_out = 0;

    free (brk_pos);

    return p_out - out;
}

/*
vi:ts=4:ai:expandtab
*/
