/**
 * $Id: thbrk.h,v 1.6 2006-07-31 12:54:02 thep Exp $
 * thbrk.h - Thai word segmentation
 * Created: 2001-05-17
 */

#ifndef THAI_THBRK_H
#define THAI_THBRK_H

#include <thai/thailib.h>

BEGIN_CDECL

/**
 * @file   thbrk.h
 * @brief  Thai word segmentation
 */

extern int th_brk(const thchar_t *s, int pos[], size_t n);

extern int th_brk_line(const thchar_t *in, thchar_t *out, size_t n,
                       const char *delim);

END_CDECL

#endif  /* THAI_THBRK_H */

