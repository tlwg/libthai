/*
 * thwcoll.h - Thai wide-char string collation
 * Created: 2001-05-17
 */

#ifndef THAI_THWCOLL_H
#define THAI_THWCOLL_H

#include <thai/thailib.h>
#include <stddef.h>

BEGIN_CDECL

extern int    th_wcstrcoll(thwchar_t *s1, thwchar_t *s2);
extern size_t th_wcstrxfrm(thwchar_t *dest, thwchar_t *src, size_t n);

END_CDECL

#endif  /* THAI_THCOLL_H */

