/*
 * $Id: thwbrk.h,v 1.3 2001-07-30 11:37:39 ott Exp $
 * thwbrk.h - Thai wide-char word segmentation
 * Created: 2001-05-17
 */

#ifndef THAI_THWBRK_H
#define THAI_THWBRK_H

#include <thai/thailib.h>

BEGIN_CDECL

/*
 * Find word break positions in Thai Unicode string s
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
extern int th_wbrk(const thwchar_t *s, int pos[], size_t n);

/*
 * Find word break positions in Thai string in
 *
 * @param in : the input string to be processed
 * @param out : the output string after processed
 * @param n : the size of "out"
 * @param cutcode : user-defined word-break code
 * On returns: at most n breaking positions stored in pos[],
 *             from left to right
 * Returns: the actual size of the processed string
 */
extern int th_wbrk_line(const thwchar_t *in, thwchar_t *_out, size_t n, const thwchar_t* _cutCode );


END_CDECL

#endif  /* THAI_THWBRK_H */

