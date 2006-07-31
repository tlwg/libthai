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

/**
 * @brief  Find word break positions in Thai wide-char string
 *
 * @param  s   : the input string to be processed
 * @param  pos : array to keep breaking positions
 * @param  n   : size of @a pos[]
 *
 * @return  the actual number of breaking positions occurred
 *
 * Finds word break positions in Thai string @a s and stores at most @a n 
 * breaking positions in @a pos[], from left to right.
 */
extern int th_wbrk(const thwchar_t *s, int pos[], size_t n);

/**
 * @brief  Insert word delimitors in given wide-char string
 *
 * @param  in  : the input wide-char string to be processed
 * @param  out : the output wide-char buffer
 * @param  n   : the size of @a out (as number of elements)
 * @param  delim : the wide-char word delimitor to insert
 *
 * @return  the actual size of the processed string (as number of elements)
 *
 * Analyzes the input string and store the string in output buffer
 * with the given word delimitor inserted at every word boundary.
 */
extern int th_wbrk_line(const thwchar_t *in, thwchar_t *out, size_t n,
                        const thwchar_t *delim);


END_CDECL

#endif  /* THAI_THWBRK_H */

