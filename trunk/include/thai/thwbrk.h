/*
 * $Id: thwbrk.h,v 1.2 2001-05-17 17:58:56 thep Exp $
 * thwbrk.h - Thai wide-char word segmentation
 * Created: 2001-05-17
 */

#ifndef THAI_THWBRK_H
#define THAI_THWBRK_H

#include <thai/thailib.h>

BEGIN_CDECL

extern int th_wcbrk(const thwchar_t *s, int pos[], size_t n);

END_CDECL

#endif  /* THAI_THWBRK_H */

