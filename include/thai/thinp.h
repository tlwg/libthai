/*
 * $Id: thinp.h,v 1.6 2001-08-05 12:42:16 thep Exp $
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
 * Given the context c_2 at position (n-2), and c_1 at position (n-1),
 * consider if c could be placed at position n or if any conversion
 * can make it fit otherwise.
 * Returns: 1 if (c_2,c_1,c) is a valid sequence in the first place
 *          2 if (c_1, c) can be converted to become valid, in which case
 *            the converted string meaning to replace (c_1, c) is written
 *            in conv[]
 *          0 if (c_1, c) CANNOT be validated, no matter how
 */
extern int th_validate(thchar_t c_2, thchar_t c_1, thchar_t c,
                       thchar_t conv[3], thstrict_t s);

END_CDECL

#endif  /* THAI_THINP_H */

