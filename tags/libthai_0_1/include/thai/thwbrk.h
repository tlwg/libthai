/*
 * thwbrk.h - Thai word segmentation
 * Created: 2001-05-17
 */

#ifndef THAI_THWBRK_H
#define THAI_THWBRK_H

#include <thai/thailib.h>

BEGIN_CDECL

extern int th_wbrk(thchar_t *s, int *pos, size_t n);

END_CDECL

#endif  /* THAI_THWBRK_H */

