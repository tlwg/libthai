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
 * thstr.c - Thai string manipulators
 * Created: 2001-08-03
 * Author:  Theppitak Karoonboonyanan <thep@linux.thai.net>
 */

#include <thai/thstr.h>
#include <thai/thctype.h>

/**
 * @brief  Normalize character order and remove excessive characters
 *
 * @param  dest : the destination string buffer
 * @param  src  : the string to normalize
 * @param  n    : the size of @a dest buffer
 *
 * @return  total bytes written to @a dest, excluding the terminating '\\0'.
 *
 * Corrects combining character order and remove excessive characters.
 * At most @a n characters are put in @a dest.
 */
size_t
th_normalize (thchar_t dest[], const thchar_t *src, size_t n)
{
    thchar_t top, up, middle, low;
    size_t   left = n;

    /* FIXME: should use WTT 2.0 instead? */
    top = up = middle = low = 0;
    while (*src && left > 1) {
        switch (th_chlevel (*src)) {
        case 0: 
            if (middle) {
                *dest++ = middle; --left;
                if (left > 1) {
                    if (low) {
                        *dest++ = low; --left;
                    } else if (up) {
                        *dest++ = up; --left;
                    }
                }
                if (left > 1 && top) {
                    *dest++ = top; --left;
                }
            }
            top = up = low = 0;
            middle = *src;
            break;
        case -1: 
            low = *src;
            break;
        case 1: 
            if (up && th_chlevel (up) == 3) {
                top = up;
            }
            up = *src;
            break;
        case 2 : 
            top = *src;
            break;
        case 3 : 
            if (!up) {
                up = *src;
            } else {
                top = *src;
            }
            break;
        }
        ++src;
    }

    if (left > 1 && middle) {
        *dest++ = middle; --left;
        if (left > 1) {
            if (low) {
                *dest++ = low; --left;
            } else if (up) {
                *dest++ = up; --left;
            }
        }
        if (left > 1 && top) {
            *dest++ = top; --left;
        }
    }
    *dest = 0;

    return n - left;
}

/*
vi:ts=4:ai:expandtab
*/
