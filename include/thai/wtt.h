/*
 * $Id: wtt.h,v 1.1 2001-08-04 13:04:49 thep Exp $
 * wtt.h - WTT I/O implementation
 * Created: 2001-08-04
 */

#ifndef THAI_WTT_H
#define THAI_WTT_H

#include <thai/thailib.h>

BEGIN_CDECL

/* Classification of characters in TIS620 according to WTT */

#define CTRL    0   /* control chars */
#define NON     1   /* non composibles */
#define CONS    2   /* consonants */
#define LV      3   /* leading vowels */
#define FV1     4   /* following vowels */
#define FV2     5
#define FV3     6
#define BV1     7   /* below vowels */
#define BV2     8
#define BD      9   /* below diacritics */
#define TONE    10  /* tonemarks */
#define AD1     11  /* above diacritics */
#define AD2     12
#define AD3     13
#define AV1     14  /* above vowels */
#define AV2     15
#define AV3     16

/* Composibility checking tables */
#define CP  1   /* COMPOSIBLE - following char is displayed in the same cell
                                as leading char, also implies ACCEPT */
#define XC  2   /* Non-display */
#define AC  3   /* ACCEPT - display the following char in the next cell */
#define RJ  4   /* REJECT - discard that following char, ignore it */
#define SR  5   /* STRICT REJECT - REJECT only if in strict mode */

extern int TACchtype(thchar_t c);
extern int TACio_op(thchar_t c1, thchar_t c2);

/*
 * implementation parts
 */

extern short _TACchtype[256];
extern short _TACio_op[17][17];

#define TACchtype(c)     (_TACchtype[c])
#define TACio_op(c1, c2) (_TACio_op[TACchtype(c1)][TACchtype(c2)])

END_CDECL

#endif  /* THAI_WTT_H */

