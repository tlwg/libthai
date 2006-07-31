/*
 * $Id: thwstr.h,v 1.3 2006-07-31 12:54:02 thep Exp $
 * thwstr.h - Thai wide-char string manipulators
 * Created: 2001-08-03
 */

#ifndef THAI_THWSTR_H
#define THAI_THWSTR_H

#include <thai/thailib.h>
#include <thai/thwchar.h>

BEGIN_CDECL

/**
 * @file   thwstr.h
 * @brief  Thai wide-char string manipulators
 */

/**
 * @brief  Normalize character order and remove excessive characters
 *
 * @param  dest : the destination wide-char string buffer
 * @param  src  : the wide-char string to normalize
 * @param  n    : the size of @a dest buffer (as number of elements)
 *
 * @return  total number of elements written to @a dest, excluding the 
 *          terminating '\\0'.
 *
 * Corrects combining character order and remove excessive characters.
 * At most @a n characters are put in @a dest.
 */
extern size_t th_wnormalize(thwchar_t dest[], const thwchar_t *src, size_t n);

END_CDECL

#endif  /* THAI_THWSTR_H */

