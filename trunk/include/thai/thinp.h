/*
 * $Id: thinp.h,v 1.2 2001-05-17 17:58:56 thep Exp $
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
} strict_t;

/*
 * Is c2 allowed to be placed after c1?
 * Returns: non-zero if yes, 0 otherwise
 */
extern int th_iscompose(thchar_t c1, thchar_t c2, strict_t s);

/*
 * Is c2 allowed to be placed after c1? And if not, swap them.
 * Returns: non-zero if the swap happenned, 0 otherwise
 */
extern int th_validate(thchar_t *c1, thchar_t *c2, strict_t s);

END_CDECL

#endif  /* THAI_THINP_H */

