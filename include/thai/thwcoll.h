/*
 * $Id: thwcoll.h,v 1.2 2001-05-17 17:58:56 thep Exp $
 * thwcoll.h - Thai wide-char string collation
 * Created: 2001-05-17
 */

#ifndef THAI_THWCOLL_H
#define THAI_THWCOLL_H

#include <thai/thailib.h>
#include <stddef.h>

BEGIN_CDECL

extern int    th_wcstrcoll(const thwchar_t *s1, const thwchar_t *s2);
extern size_t th_wcstrxfrm(thwchar_t dest[], const thwchar_t *src, size_t n);

END_CDECL

#endif  /* THAI_THCOLL_H */

