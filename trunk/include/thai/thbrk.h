/*
 * $Id: thbrk.h,v 1.1 2001-05-17 18:04:35 thep Exp $
 * thbrk.h - Thai word segmentation
 * Created: 2001-05-17
 */

#ifndef THAI_THBRK_H
#define THAI_THBRK_H

#include <thai/thailib.h>

BEGIN_CDECL

/*
 * Find word break positions in Thai string s
 * On returns: at most n breaking positions stored in pos[],
 *             from left to right
 * Returns: the actual number of positions stored in pos[]
 */
extern int th_brk(const thchar_t *s, int pos[], size_t n);

END_CDECL

#endif  /* THAI_THBRK_H */

