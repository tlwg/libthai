/*
 * $Id: thwbrk.h,v 1.4 2006-07-31 12:54:02 thep Exp $
 * thwbrk.h - Thai wide-char word segmentation
 * Created: 2001-05-17
 */

#ifndef THAI_THWBRK_H
#define THAI_THWBRK_H

#include <thai/thailib.h>

BEGIN_CDECL

/**
 * @file   thwbrk.h
 * @brief  Thai wide-char word segmentation
 */

extern int th_wbrk(const thwchar_t *s, int pos[], size_t n);

extern int th_wbrk_line(const thwchar_t *in, thwchar_t *out, size_t n,
                        const thwchar_t *delim);


END_CDECL

#endif  /* THAI_THWBRK_H */

