/*
 * $Id: thinp.h,v 1.5 2001-08-04 13:04:49 thep Exp $
 * thinp.h - Thai string input sequence filtering
 * Created: 2001-05-17
 */

#ifndef THAI_THINP_H
#define THAI_THINP_H

#include <thai/thailib.h>

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

/*
 * Is *c2 allowed to be placed after *c1? And if not, and if swapping
 * them makes it valid, do it.
 * Returns: 1 if (*c1, *c2) is a valid sequence in the first place
 *          2 if (*c1, *c2) has been swapped and the sequence becomes valid
 *          0 if (*c1, *c2) is invalid, no matter how
 */
extern int th_validate(thchar_t *c1, thchar_t *c2, thstrict_t s);

END_CDECL

#endif  /* THAI_THINP_H */

