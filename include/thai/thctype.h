/*
 * $Id: thctype.h,v 1.7 2001-08-07 09:12:58 thep Exp $
 * thctype.h - Thai character classifications
 * Created: 2001-05-17
 * Author:  Theppitak Karoonboonyanan <thep@links.nectec.or.th>
 */

#ifndef THAI_THCTYPE_H
#define THAI_THCTYPE_H

#include <thai/thailib.h>

BEGIN_CDECL

extern int th_istis(thchar_t c);

extern int th_isthai(thchar_t c);
extern int th_iseng(thchar_t c);

/* Thai letter classification */
extern int th_isthcons(thchar_t c);
extern int th_isthvowel(thchar_t c);
extern int th_isthtone(thchar_t c);
extern int th_isthdiac(thchar_t c);
extern int th_isthdigit(thchar_t c);
extern int th_isthpunct(thchar_t c);

/* Thai consonant shapes classification */
extern int th_istaillesscons(thchar_t c);
extern int th_isovershootcons(thchar_t c);
extern int th_isundershootcons(thchar_t c);
extern int th_isundersplitcons(thchar_t c);

/* Thai vowel classification */
extern int th_isldvowel(thchar_t c);
extern int th_isflvowel(thchar_t c);
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

/* is combining character? */
extern int th_iscombchar(thchar_t c);

/*
 * implementation parts
 */
#include <ctype.h>
#define _th_ISbit(bit)  (1 << (bit))
#define _th_bitfld(base, val)  ((val) << (base))
#define _th_bitmsk(base, bits) (~((~(unsigned short)0) << (bits)) << (base))

enum {
  _th_IStis   = _th_ISbit(0),        /* TIS-620 char */

  _th_IScons  = _th_ISbit(1),        /* Thai consonant */
  _th_CClassMsk = _th_bitmsk(1, 3),  /*   Thai consonant shape masks */
  _th_CCtailless   = _th_bitfld(2, 0)|_th_IScons,   /* tailless cons */
  _th_CCovershoot  = _th_bitfld(2, 1)|_th_IScons,   /* overshoot cons */
  _th_CCundershoot = _th_bitfld(2, 2)|_th_IScons,   /* undershoot cons */
  _th_CCundersplit = _th_bitfld(2, 3)|_th_IScons,   /* undersplit cons */
  _th_ISvowel = _th_ISbit(4),        /* Thai vowel */
  _th_VClassMsk = _th_bitmsk(4, 3),  /*   Thai vowel class masks */
  _th_VCflvowel = _th_bitfld(5, 0)|_th_ISvowel,  /*   Thai following vowel */
  _th_VCldvowel = _th_bitfld(5, 1)|_th_ISvowel,  /*   Thai leading vowel */
  _th_VCupvowel = _th_bitfld(5, 2)|_th_ISvowel,  /*   Thai upper vowel */
  _th_VCblvowel = _th_bitfld(5, 3)|_th_ISvowel,  /*   Thai below vowel */
  _th_IStone  = _th_ISbit(7),        /* Thai tone mark */
  _th_ISdiac  = _th_ISbit(8),        /* Thai diacritic */
  _th_ISdigit = _th_ISbit(9),        /* digit */
  _th_ISpunct = _th_ISbit(10),       /* punctuation */
};

extern const unsigned short _th_ctype_tbl[];

#define _th_isctype(c, type)      (_th_ctype_tbl[c] & (type))
#define _th_isbits(c, mask, val)  ((_th_ctype_tbl[c] & (mask)) == (val))

#define th_istis(c)         _th_isctype((c), _th_IStis)

#define th_isthai(c)        (th_istis(c) && ((c) & 0x80))
#define th_iseng(c)         isascii(c)

/* Thai letter classification */
#define th_isthcons(c)      _th_isctype((c), _th_IScons)
#define th_isthvowel(c)     _th_isctype((c), _th_ISvowel)
#define th_isthtone(c)      _th_isctype((c), _th_IStone)
#define th_isthdiac(c)      _th_isctype((c), _th_ISdiac)
#define th_isthdigit(c)     _th_isctype((c), _th_ISdigit)
#define th_isthpunct(c)     _th_isctype((c), _th_ISpunct)

/* Thai consonant shapes classification */
#define th_istaillesscons(c)   _th_isbits((c), _th_CClassMsk, _th_CCtailless)
#define th_isovershootcons(c)  _th_isbits((c), _th_CClassMsk, _th_CCovershoot)
#define th_isundershootcons(c) _th_isbits((c), _th_CClassMsk, _th_CCundershoot)
#define th_isundersplitcons(c) _th_isbits((c), _th_CClassMsk, _th_CCundersplit)

/* Thai vowel classification */
#define th_isldvowel(c)     _th_isbits((c), _th_VClassMsk, _th_VCldvowel)
#define th_isflvowel(c)     _th_isbits((c), _th_VClassMsk, _th_VCflvowel)
#define th_isupvowel(c)     _th_isbits((c), _th_VClassMsk, _th_VCupvowel)
#define th_isblvowel(c)     _th_isbits((c), _th_VClassMsk, _th_VCblvowel)

extern const int            _th_chlevel_tbl[];

#define th_chlevel(c)       (_th_chlevel_tbl[c])
#define th_iscombchar(c)    (th_chlevel(c) != 0)

END_CDECL

#endif  /* THAI_THCTYPE_H */

