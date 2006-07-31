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

/**
 * @brief  Compare two Thai strings for collation
 *
 * @param  s1 : first string (null-terminated)
 * @param  s2 : second string (null-terminated)
 *
 * @return  < 0 if @a s1 precedes @a s2; 0 if @a s1 equals @a s2;
 *          > 0 if @a s1 succeeds @a s2
 */
extern int    th_strcoll(const thchar_t *s1, const thchar_t *s2);

/**
 * @brief  Transform string into collatable form
 *
 * @param  dest : the destination string buffer
 * @param  src  : the string to transform
 * @param  n    : the size of @a dest buffer
 *
 * @returns  the number of bytes required to store the result in @a dest,
 *           excluding the terminating '\\0'.
 *           If the return value >= @a n, @a dest is undefined.
 *
 * Transforms @a src into a form from which comparison using strcmp() yields
 * the same result as that from th_strcoll(). At most @a n characters are
 * put in @a dest.
 */
extern size_t th_strxfrm(thchar_t dest[], const thchar_t *src, size_t n);

END_CDECL

#endif  /* THAI_THCOLL_H */

