/*
 * $Id: thwstr.h,v 1.1 2001-08-03 10:51:51 thep Exp $
 * thwstr.h - Thai wide-char string manipulators
 * Created: 2001-08-03
 */

#ifndef THAI_THWSTR_H
#define THAI_THWSTR_H

#include <thai/thailib.h>

BEGIN_CDECL

/*
 * fix combining character order and remove excessive characters.
 * At most n characters are put in dest.
 * Returns: total bytes written to dest, excluding the terminating '\0'
 */
extern size_t th_wnormalize(thwchar_t dest[], const thwchar_t *src, size_t n);

END_CDECL

#endif  /* THAI_THWSTR_H */

