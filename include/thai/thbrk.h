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

/**
 * @brief  Find word break positions in Thai string
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
extern int th_brk(const thchar_t *s, int pos[], size_t n);

/**
 * @brief  Insert word delimitors in given string
 *
 * @param  in  : the input string to be processed
 * @param  out : the output buffer
 * @param  n   : the size of @a out
 * @param  delim : the word delimitor to insert
 *
 * @return  the actual size of the processed string
 *
 * Analyzes the input string and store the string in output buffer
 * with the given word delimitor inserted at every word boundary.
 */
extern int th_brk_line(const thchar_t *in, thchar_t *out, size_t n,
                       const char *delim);

END_CDECL

#endif  /* THAI_THBRK_H */

