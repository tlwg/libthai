/*
 * thcoll.h - Thai string collation
 * Created: 2001-05-17
 */

#ifndef THAI_THCOLL_H
#define THAI_THCOLL_H

#include <thai/thailib.h>
#include <stddef.h>

BEGIN_CDECL

extern int    th_strcoll(thchar_t *s1, thchar_t *s2);
extern size_t th_strxfrm(thchar_t *dest, thchar_t *src, size_t n);

END_CDECL

#endif  /* THAI_THCOLL_H */

