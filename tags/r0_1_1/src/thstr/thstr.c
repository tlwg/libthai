/*
 * $Id: thstr.c,v 1.2 2001-08-14 06:11:42 thep Exp $
 * thstr.c - Thai string manipulators
 * Created: 2001-08-03
 */

#include <thai/thstr.h>
#include <thai/thctype.h>

/* FIXME: should use WTT 2.0 instead? */
size_t th_normalize(thchar_t dest[], const thchar_t *src, size_t n)
{
    thchar_t top, up, middle, low;
    size_t   left = n;

    top = up = middle = low = 0;
    while (*src && left > 1) {
        switch (th_chlevel(*src)) {
        case 0 : 
            if (middle) {
                *dest++ = middle; --left;
                if (left > 1) {
                    if (low) { *dest++ = low; --left; }
                    else if (up) { *dest++ = up; --left; }
                }
                if (left > 1 && top) { *dest++ = top; --left; }
            }
            top = up = low = 0;
            middle = *src; break;
        case -1 : 
            low = *src; break;
        case 1 : 
            up = *src; break;
        case 2 : 
            top = *src; break;
        }
        ++src;
    }

    if (left > 1 && middle) {
        *dest++ = middle; --left;
        if (left > 1) {
            if (low) { *dest++ = low; --left; }
            else if (up) { *dest++ = up; --left; }
        }
        if (left > 1 && top) { *dest++ = top; --left; }
    }
    *dest = 0;

    return n - left;
}

