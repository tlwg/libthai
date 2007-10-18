/*
 * $Id: thwstr.c,v 1.3 2007-10-18 14:52:29 thep Exp $
 * thwstr.c - Thai string manipulators (Unicode wrapper)
 * Created: 2001-09-30
 * Author:  Theppitak Karoonboonyanan <thep@linux.thai.net>
 */

#include <thai/thwstr.h>
#include <thai/thwchar.h>
#include <thai/thstr.h>
#include <stdlib.h>
#include <assert.h>

static int th_wthaichunk(thchar_t dest[], const thwchar_t *wsrc, size_t n)
{
    if (*wsrc == 0) { return 0; }

    if (th_uni2tis(*wsrc) == THCHAR_ERR) {
        /* skip THCHAR_ERR chunk */
        int len = 0;
        while (*wsrc && th_uni2tis(*wsrc) == THCHAR_ERR) {
            ++wsrc; ++len;
        }
        return -len; /* always non-positive */
    } else {
        size_t left = n;
        thchar_t c;

        /* convert Thai chunk */
        while (left > 1 && *wsrc && (c = th_uni2tis(*wsrc)) != THCHAR_ERR) {
            *dest++ = c; ++wsrc; --left;
        }
        *dest = 0;
        return n - left; /* always non-negative, null-terminator excluded */
    }
}

size_t th_wnormalize(thwchar_t wdest[], const thwchar_t *wsrc, size_t n)
{
    size_t left = n;
    thchar_t *src8 = (thchar_t*) malloc(n * sizeof (thchar_t));
    thchar_t *norm8 = (thchar_t*) malloc(n * sizeof (thchar_t));

    while (left > 1 && *wsrc) {
        int chunk_len = th_wthaichunk(src8, wsrc, n-1);
        src8[n-1] = 0;  /* ensure null-termination */
	if (chunk_len > 0) {
            int i;
            int norm_len = th_normalize(norm8, src8, n);
            for (i = 0; left > 1 && i < norm_len; ++i) {
                *wdest++ = th_tis2uni(norm8[i]); --left;
            }
        } else {
            int i;
            chunk_len = -chunk_len;
            for (i = 0; left > 1 && i < chunk_len; ++i) {
                *wdest++ = wsrc[i]; --left;
            }
        }
        assert(chunk_len >= 0);
        wsrc += chunk_len;
    }

    *wdest = 0;

    free(norm8);
    free(src8);

    return n - left;
}

