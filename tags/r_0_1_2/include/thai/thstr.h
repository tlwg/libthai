/*
 * $Id: thstr.h,v 1.1 2001-08-03 10:51:51 thep Exp $
 * thstr.h - Thai string manipulators
 * Created: 2001-08-03
 */

#ifndef THAI_THSTR_H
#define THAI_THSTR_H

#include <thai/thailib.h>

BEGIN_CDECL

/*
 * fix combining character order and remove excessive characters.
 * At most n characters are put in dest.
 * Returns: total bytes written to dest, excluding the terminating '\0'
 */
extern size_t th_normalize(thchar_t dest[], const thchar_t *src, size_t n);

END_CDECL

#endif  /* THAI_THSTR_H */

