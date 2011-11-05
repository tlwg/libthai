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
 * thwstr.c - Thai string manipulators (Unicode wrapper)
 * Created: 2001-09-30
 * Author:  Theppitak Karoonboonyanan <thep@linux.thai.net>
 */

#include <thai/thwstr.h>
#include <thai/thwchar.h>
#include <thai/thstr.h>
#include <stdlib.h>
#include <assert.h>

static int
th_wthaichunk (thchar_t dest[], const thwchar_t *wsrc, size_t n)
{
    if (*wsrc == 0)
        return 0;

    if (th_uni2tis (*wsrc) == THCHAR_ERR) {
        /* skip THCHAR_ERR chunk */
        int len = 0;
        while (*wsrc && th_uni2tis (*wsrc) == THCHAR_ERR) {
            ++wsrc; ++len;
        }
        return -len; /* always non-positive */
    } else {
        size_t left = n;
        thchar_t c;

        /* convert Thai chunk */
        while (left > 1 && *wsrc && (c = th_uni2tis (*wsrc)) != THCHAR_ERR) {
            *dest++ = c; ++wsrc; --left;
        }
        *dest = 0;
        return n - left; /* always non-negative, null-terminator excluded */
    }
}

/**
 * @brief  Normalize character order and remove excessive characters
 *
 * @param  wdest : the destination wide-char string buffer
 * @param  wsrc  : the wide-char string to normalize
 * @param  n     : the size of @a dest buffer (as number of elements)
 *
 * @return  total number of elements written to @a wdest, excluding the 
 *          terminating '\\0'.
 *
 * Corrects combining character order and remove excessive characters.
 * At most @a n characters are put in @a wdest.
 */
size_t
th_wnormalize (thwchar_t wdest[], const thwchar_t *wsrc, size_t n)
{
    size_t left = n;
    thchar_t *src8 = (thchar_t*) malloc(n * sizeof (thchar_t));
    thchar_t *norm8 = (thchar_t*) malloc(n * sizeof (thchar_t));

    while (left > 1 && *wsrc) {
        int chunk_len = th_wthaichunk (src8, wsrc, n-1);
        src8[n-1] = 0;  /* ensure null-termination */
        if (chunk_len > 0) {
            int i;
            int norm_len = th_normalize (norm8, src8, n);
            for (i = 0; left > 1 && i < norm_len; ++i) {
                *wdest++ = th_tis2uni (norm8[i]); --left;
            }
        } else {
            int i;
            chunk_len = -chunk_len;
            for (i = 0; left > 1 && i < chunk_len; ++i) {
                *wdest++ = wsrc[i]; --left;
            }
        }
        assert (chunk_len >= 0);
        wsrc += chunk_len;
    }

    *wdest = 0;

    free (norm8);
    free (src8);

    return n - left;
}

/*
vi:ts=4:ai:expandtab
*/
