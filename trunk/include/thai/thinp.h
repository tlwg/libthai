/*
 * $Id: thinp.h,v 1.7 2001-08-08 17:52:10 thep Exp $
 * thinp.h - Thai string input sequence filtering
 * Created: 2001-05-17
 */

#ifndef THAI_THINP_H
#define THAI_THINP_H

#include <thai/thailib.h>
#include <thai/thcell.h>

BEGIN_CDECL

/*
 * strictness of input sequence checking, according to WTT 2.0
 */
typedef enum {
    ISC_PASSTHROUGH = 0,
    ISC_BASICCHECK  = 1,
    ISC_STRICT      = 2
} thstrict_t;

/*
 * Is c2 allowed to be placed after c1?
 * Returns: non-zero if yes, 0 otherwise
 */
extern int th_isaccept(thchar_t c1, thchar_t c2, thstrict_t s);

struct thinpconv_t {
    thchar_t conv[4];  /* (null-terminated) string to put into input buffer */
    int      offset;   /* offset (<=0) from cur pos where the conv begin */
};

/*
 * Given the previous cell as context, edit the input buffer using
 * the given input c, maintaining WTT canonical order, and do some
 * convenient conversion.
 * Returns: 0 if the input is to be rejected
 *          non-zero otherwise.
 */
extern int th_validate(struct thcell context, thchar_t c,
                       struct thinpconv_t *conv);

END_CDECL

#endif  /* THAI_THINP_H */

