/*
 * $Id: thbrk.h,v 1.2 2001-07-15 16:35:24 ott Exp $
 * thbrk.h - Thai word segmentation
 * Created: 2001-05-17
 */

#ifndef THAI_THBRK_H
#define THAI_THBRK_H

#include <thai/thailib.h>

BEGIN_CDECL

/*
 * Find word break positions in Thai string s
 *
 * @param s : the input string to be processed
 * @param pos : array to keep breaking positions (see on return)
 * @pram n : size of pos[]
 *
 * On returns: at most n breaking positions stored in pos[],
 *             from left to right
 * Returns: the actual number of breaking positions occurred
 *
 */
extern int th_brk(const thchar_t *s, int pos[], size_t n);

/*
 * Find word break positions in Thai string in
 *
 * @param in : the input string to be processed
 * @param out : the output string after processed
 * @param n : the size of "out"
 * @param cutcode : the word-break character (default = 254)
 * On returns: at most n breaking positions stored in pos[],
 *             from left to right
 * Returns: the actual size of the processed string
 */
extern int th_brk_line(const thchar_t *in, thchar_t *out, size_t n, int _cutcode );

END_CDECL

#endif  /* THAI_THBRK_H */

