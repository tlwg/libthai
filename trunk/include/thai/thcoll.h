/*
 * $Id: thcoll.h,v 1.5 2006-07-31 12:54:02 thep Exp $
 * thcoll.h - Thai string collation
 * Created: 2001-05-17
 */

#ifndef THAI_THCOLL_H
#define THAI_THCOLL_H

#include <thai/thailib.h>

BEGIN_CDECL

/**
 * @file   thcoll.h
 * @brief  Thai string collation
 */

extern int    th_strcoll(const thchar_t *s1, const thchar_t *s2);

extern size_t th_strxfrm(thchar_t dest[], const thchar_t *src, size_t n);

END_CDECL

#endif  /* THAI_THCOLL_H */

