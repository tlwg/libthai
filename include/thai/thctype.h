/*
 * $Id: thctype.h,v 1.4 2001-06-15 12:01:18 thep Exp $
 * thctype.h - Thai character classifications
 * Created: 2001-05-17
 * Author:  Theppitak Karoonboonyanan <thep@links.nectec.or.th>
 */

#ifndef THAI_THCTYPE_H
#define THAI_THCTYPE_H

#include <thai/thailib.h>

BEGIN_CDECL

extern int th_istis(thchar_t c);
extern int th_iswinthai(thchar_t c);
extern int th_ismacthai(thchar_t c);

extern int th_isthai(thchar_t c);
extern int th_iseng(thchar_t c);

/* Thai letter classification */
extern int th_isthcons(thchar_t c);
extern int th_isthvowel(thchar_t c);
extern int th_isthtone(thchar_t c);
extern int th_isthdiac(thchar_t c);
extern int th_isthdigit(thchar_t c);
extern int th_isthpunct(thchar_t c);

/* Thai vowel classification */
extern int th_isldvowel(thchar_t c);
extern int th_lsflvowel(thchar_t c);
extern int th_isupvowel(thchar_t c);
extern int th_isblvowel(thchar_t c);

/*
 * For rendering :
 *   2 = top
 *   1 = above
 *   0 = base
 *  -1 = below
 */
extern int th_chlevel(thchar_t c);

/*
 * implementation parts
 */
#define _th_ISbit(bit)  (1 << (bit))
#define _th_bitfld(base, val)  ((val) << (base))
#define _th_bitmsk(base, bits) (~(~((~0) << (bits)) << (base)))

enum {
  _th_IStis   = _th_ISbit(0),        /* TIS-620 char */
  _th_ISwin   = _th_ISbit(1),        /* Windows Thai extension */
  _th_ISmac   = _th_ISbit(2),        /* MacThai extension */

  _th_IScons  = _th_ISbit(3),        /* Thai consonant */
  _th_ISvowel = _th_ISbit(4),        /* Thai vowel */
  _th_IStone  = _th_ISbit(5),        /* Thai tone mark */
  _th_ISdiac  = _th_ISbit(6),        /* Thai tone mark */
  _th_ISdigit = _th_ISbit(7),        /* Thai digit */
  _th_ISpunct = _th_ISbit(8),        /* Thai punctuation */

  _th_VClassMsk = _th_bitmsk(9, 2),  /* Thai vowel class masks */
  _th_VCflvowel = _th_bitfld(9, 0),  /* Thai following vowel */
  _th_VCldvowel = _th_bitfld(9, 1),  /* Thai leading vowel */
  _th_VCupvowel = _th_bitfld(9, 2),  /* Thai upper vowel */
  _th_VCblvowel = _th_bitfld(9, 3)   /* Thai below vowel */
};

extern const unsigned short _th_ctype_tbl[];

#define _th_isctype(c, type)      (_th_ctype_tbl[c] & (type))
#define _th_isbits(c, mask, val)  (_th_ctype_tbl[c] & (mask) == (val))

#define th_istis(c)         _th_isctype((c), _th_IStis)
#define th_iswinthai(c)     _th_isctype((c), _th_ISwin)
#define th_ismacthai(c)     _th_isctype((c), _th_ISmac)

#define th_isthai(c)        (th_istis(c) && ((c) & 0x80))
#define th_iseng(c)         isascii(c)

/* Thai letter classification */
#define th_isthcons(c)      _th_isctype((c), _th_IScons)
#define th_isthvowel(c)     _th_isctype((c), _th_ISvowel)
#define th_isthtone(c)      _th_isctype((c), _th_IStone)
#define th_isthdiac(c)      _th_isctype((c), _th_ISdiac)
#define th_isthdigit(c)     _th_isctype((c), _th_ISdigit)
#define th_isthpunct(c)     _th_isctype((c), _th_ISpunct)

/* Thai vowel classification */
#define th_isldvowel(c)     _th_isbits((c), _th_VClassMsk, _th_VCldvowel)
#define th_lsflvowel(c)     _th_isbits((c), _th_VClassMsk, _th_VCflvowel)
#define th_isupvowel(c)     _th_isbits((c), _th_VClassMsk, _th_VCupvowel)
#define th_isblvowel(c)     _th_isbits((c), _th_VClassMsk, _th_VCblvowel)

extern const int            _th_chlevel_tbl[];

#define th_chlevel(c)       (_th_chlevel_tbl[c])

END_CDECL

#endif  /* THAI_THCTYPE_H */

