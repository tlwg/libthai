/*
 * $Id: thwctype.h,v 1.3 2001-09-14 14:36:04 thep Exp $
 * thwctype.h - Thai wide-char character classifications
 * Created: 2001-05-17
 */

#ifndef THAI_THWCTYPE_H
#define THAI_THWCTYPE_H

#include <thai/thailib.h>
#include <thai/thwchar.h>

BEGIN_CDECL

extern int th_wcistis(thwchar_t wc);

extern int th_wcisthai(thwchar_t wc);
extern int th_wciseng(thwchar_t wc);

/* Thai letter classification */
extern int th_wcisthcons(thwchar_t wc);
extern int th_wcisthvowel(thwchar_t wc);
extern int th_wcisthtone(thwchar_t wc);
extern int th_wcisthdigit(thwchar_t wc);
extern int th_wcisthpunct(thwchar_t wc);

/* Thai vowel classification */
extern int th_wcisldvowel(thwchar_t wc);
extern int th_wcisflvowel(thwchar_t wc);
extern int th_wcisupvowel(thwchar_t wc);
extern int th_wcisblvowel(thwchar_t wc);

/*
 * For rendering :
 *   2 = top
 *   1 = above
 *   0 = base
 *  -1 = below
 */
extern int th_wcchlevel(thwchar_t wc);


/*
 * implementation parts
 */
#include <thai/thctype.h>

#define th_wcistis(wc)      th_istis(th_uni2tis(wc))

#define th_wcisthai(wc)     th_isthai(th_uni2tis(wc))
#define th_wciseng(wc)      th_iseng(th_uni2tis(wc))

/* Thai letter classification */
#define th_wcisthcons(wc)   th_isthcons(th_uni2tis(wc))
#define th_wcisthvowel(wc)  th_isthvowel(th_uni2tis(wc))
#define th_wcisthtone(wc)   th_isthtone(th_uni2tis(wc))
#define th_wcisthdigit(wc)  th_isthdigit(th_uni2tis(wc))
#define th_wcisthpunct(wc)  th_isthpunct(th_uni2tis(wc))

/* Thai vowel classification */
#define th_wcisldvowel(wc)  th_isldvowel(th_uni2tis(wc))
#define th_wcisflvowel(wc)  th_isflvowel(th_uni2tis(wc))
#define th_wcisupvowel(wc)  th_isupvowel(th_uni2tis(wc))
#define th_wcisblvowel(wc)  th_isblvowel(th_uni2tis(wc))

#define th_wcchlevel(wc)    th_chlevel(th_uni2tis(wc))

END_CDECL

#endif  /* THAI_THWCTYPE_H */

