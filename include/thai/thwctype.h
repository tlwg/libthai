/*
 * thwctype.h - Thai wide-char character classifications
 * Created: 2001-05-17
 */

#ifndef THAI_THWCTYPE_H
#define THAI_THWCTYPE_H

#include <thai/thailib.h>

BEGIN_CDECL

extern int th_wcistis(thwchar_t c);
extern int th_wciswinthai(thwchar_t c);
extern int th_wcismacthai(thwchar_t c);

extern int th_wcisthai(thwchar_t c);
extern int th_wciseng(thwchar_t c);

/* Thai letter classification */
extern int th_wcisthcons(thwchar_t c);
extern int th_wcisthvowel(thwchar_t c);
extern int th_wcisthtone(thwchar_t c);
extern int th_wcisthdigit(thwchar_t c);
extern int th_wcisthpunct(thwchar_t c);

/* Thai vowel classification */
extern int th_wcisldvowel(thwchar_t c);
extern int th_wclsflvowel(thwchar_t c);
extern int th_wcisupvowel(thwchar_t c);
extern int th_wcisblvowel(thwchar_t c);

/*
 * For rendering :
 *   2 = top
 *   1 = above
 *   0 = base
 *  -1 = below
 */
extern int th_wcchlevel(thwchar_t c);

END_CDECL

#endif  /* THAI_THWCTYPE_H */

