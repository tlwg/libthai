/*
 * $Id: thcoll.h,v 1.2 2001-05-17 17:58:56 thep Exp $
 * thcoll.h - Thai string collation
 * Created: 2001-05-17
 */

#ifndef THAI_THCOLL_H
#define THAI_THCOLL_H

#include <thai/thailib.h>
#include <stddef.h>

BEGIN_CDECL

/*
 * compare two Thai strings for collation
 * Returns: < 0 if s1 precedes s2; 0 if s1 equals s2; > 0 if s1 succeeds s2
 */
extern int    th_strcoll(const thchar_t *s1, const thchar_t *s2);

/*
 * transform src into a form from which comparison using strcmp() yields
 * the same result as that from th_strcoll(). At most n characters are
 * put in dest.
 * Returns: the number of bytes required to store the result in dest,
 *          excluding the terminating '\0'
 *          If the return value >= n, dest is indeterminate.
 */
extern size_t th_strxfrm(thchar_t dest[], const thchar_t *src, size_t n);

END_CDECL

#endif  /* THAI_THCOLL_H */

