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
 * thcoll.c - Thai string collating function definition
 * Created: 12 Nov 1998
 * Author: Theppitak Karoonboonyanan <thep@linux.thai.net>
 */

/*
 * The ordering algorithm is in accordance
 * with the Thai Royal Institute Dictionary
 * 2525 B.E. Edition
 */

#include <thai/thcoll.h>
#include <thai/thctype.h>
#include "cweight.h"

/* FIXME: temporary implementation */
/* #define th_isldvowel(c) ((0xe0 <= (c)) && ((c) <= 0xe4)) */

static const thchar_t*
th_non_ignore_ (const thchar_t* p, int level)
{
    while (*p && th_char_weight_ (*p, level) == IGNORE) {
        ++p;
    }
    return p;
}

/**
 * @brief  Compare two Thai strings for collation
 *
 * @param  s1 : first string (null-terminated)
 * @param  s2 : second string (null-terminated)
 *
 * @return  < 0 if @a s1 precedes @a s2; 0 if @a s1 equals @a s2;
 *          > 0 if @a s1 succeeds @a s2
 */
int
th_strcoll (const thchar_t *s1, const thchar_t *s2)
{
    const thchar_t *p1, *p2;
    int   l;

    while (*s1 == *s2 && *s1 != 0) {
        s1++; s2++;
    }
    if (*s1 == 0 && *s2 == 0)
        return 0;

    /* compare at level 0 */
    p1 = th_non_ignore_ (s1, 0);
    p2 = th_non_ignore_ (s2, 0);
    while (*p1 && *p2) {
        thchar_t w1 = th_char_weight_ (*p1, 0);
        thchar_t w2 = th_char_weight_ (*p2, 0);
        if (th_isldvowel (*p1)) {
            const thchar_t* q1 = th_non_ignore_ (p1+1, 0);
            thchar_t ww1 = th_char_weight_ (*q1, 0);
            if (th_isldvowel (*p2)) {
                const thchar_t* q2 = th_non_ignore_ (p2+1, 0);
                thchar_t ww2 = th_char_weight_ (*q2, 0);
                if (ww1 != ww2)
                    return ww1 - ww2;
                if (w1 != w2)
                    return w1 - w2;
                p1 = th_non_ignore_ (q1+1, 0);
                p2 = th_non_ignore_ (q2+1, 0);
            } else {
                return (ww1 != w2) ? ww1 - w2 : 1;
            }
        } else {
            if (th_isldvowel (*p2)) {
                const thchar_t* q2 = th_non_ignore_ (p2+1, 0);
                thchar_t ww2 = th_char_weight_ (*q2, 0);
                return (w1 != ww2) ? w1 - ww2 : -1;
            } else {
                if (w1 != w2)
                    return w1 - w2;
                p1 = th_non_ignore_ (p1+1, 0);
                p2 = th_non_ignore_ (p2+1, 0);
            }
        }
    }
    if (*p1 != 0)
        return 1;
    if (*p2 != 0)
        return -1;

    /* compare at level 1 and higher */
    for (l = 1; l < TOT_LEVELS; l++) {
        for (p1 = th_non_ignore_ (s1, l), p2 = th_non_ignore_ (s2, l);
             *p1 && *p2;
             p1 = th_non_ignore_ (p1+1, l), p2 = th_non_ignore_ (p2+1, l))
        {
            thchar_t w1 = th_char_weight_ (*p1, l);
            thchar_t w2 = th_char_weight_ (*p2, l);
            if (w1 != w2)
                return w1 - w2;
        }
        if (*p1 != 0)
            return 1;
        if (*p2 != 0)
            return -1;
    }

    return 0;
}

static int
th_put_weight_ (thchar_t *dst, size_t n, thchar_t w, int *d)
{
    if (*d < n-1) {
        if (dst) {
            dst[*d] = w; 
        }
        ++*d;
        return 1;
    }
    return 0;
}

/**
 * @brief  Transform string into collatable form
 *
 * @param  dest : the destination string buffer
 * @param  src  : the string to transform
 * @param  n    : the size of @a dest buffer
 *
 * @returns  the number of bytes required to store the result in @a dest,
 *           excluding the terminating '\\0'.
 *           If the return value >= @a n, @a dest is undefined.
 *
 * Transforms @a src into a form from which comparison using strcmp() yields
 * the same result as that from th_strcoll(). At most @a n characters are
 * put in @a dest.
 */
size_t
th_strxfrm (thchar_t dest[], const thchar_t *src, size_t n)
{
    const thchar_t *p;
    int   d = 0;
    int   l;

    /* encode level 0 */
    for (p = th_non_ignore_ (src, 0); *p; ) {
        thchar_t w = th_char_weight_ (*p, 0);
        if (th_isldvowel (*p)) {
            /* swap with next counting char */
            p = th_non_ignore_ (p+1, 0);
            if (*p) {
                if (!th_put_weight_ (dest, n, th_char_weight_ (*p, 0), &d))
                    return d;
                if (!th_put_weight_ (dest, n, w, &d))
                    return d;
            }
        } else {
            if (!th_put_weight_ (dest, n, w, &d))
                return d;
            p = th_non_ignore_ (p+1, 0);
        }
    }
    /* encode level 1 and higher */
    for (l = 1; l < TOT_LEVELS; ++l) {
        if (!th_put_weight_ (dest, n, th_char_weight_delim_ (l), &d))
            return d;
        for (p = src; *p; p = th_non_ignore_ (p+1, l)) {
            if (!th_put_weight_ (dest, n, th_char_weight_ (*p, l), &d))
                return d;
        }
    }
    if (dest) {
        dest[d] = '\0';
    }

    return d;
}

/*
vi:ts=4:ai:expandtab
*/
