/*
 * $Id: thctype.h,v 1.2 2001-05-17 17:58:56 thep Exp $
 * thctype.h - Thai character classifications
 * Created: 2001-05-17
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

END_CDECL

#endif  /* THAI_THCTYPE_H */

