/*
 * $Id: thwctype.h,v 1.4 2006-07-31 12:54:02 thep Exp $
 * thwctype.h - Thai wide-char character classifications
 * Created: 2001-05-17
 */

#ifndef THAI_THWCTYPE_H
#define THAI_THWCTYPE_H

#include <thai/thailib.h>
#include <thai/thwchar.h>

BEGIN_CDECL

/**
 * @file   thwctype.h
 * @brief  Thai wide-char character classifications
 */

extern int th_wcistis(thwchar_t wc);

extern int th_wcisthai(thwchar_t wc);
extern int th_wciseng(thwchar_t wc);

/* Thai letter classification */
extern int th_wcisthcons(thwchar_t wc);
extern int th_wcisthvowel(thwchar_t wc);
extern int th_wcisthtone(thwchar_t wc);
extern int th_wcisthdiac(thwchar_t wc);
extern int th_wcisthdigit(thwchar_t wc);
extern int th_wcisthpunct(thwchar_t wc);

/* Thai consonant shapes classification */
extern int th_wcistaillesscons(thwchar_t wc);
extern int th_wcisovershootcons(thwchar_t wc);
extern int th_wcisundershootcons(thwchar_t wc);
extern int th_wcisundersplitcons(thwchar_t wc);

/* Thai vowel classification */
extern int th_wcisldvowel(thwchar_t wc);
extern int th_wcisflvowel(thwchar_t wc);
extern int th_wcisupvowel(thwchar_t wc);
extern int th_wcisblvowel(thwchar_t wc);

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
#define th_wcisthdiac(wc)   th_isthdiac(th_uni2tis(wc))
#define th_wcisthpunct(wc)  th_isthpunct(th_uni2tis(wc))

/* Thai consonant shapes classification */
#define th_wcistaillesscons(wc)   th_istaillesscons(th_uni2tis(wc))
#define th_wcisovershootcons(wc)  th_isovershootcons(th_uni2tis(wc))
#define th_wcisundershootcons(wc) th_isundershootcons(th_uni2tis(wc))
#define th_wcisundersplitcons(wc) th_isundersplitcons(th_uni2tis(wc))

/* Thai vowel classification */
#define th_wcisldvowel(wc)  th_isldvowel(th_uni2tis(wc))
#define th_wcisflvowel(wc)  th_isflvowel(th_uni2tis(wc))
#define th_wcisupvowel(wc)  th_isupvowel(th_uni2tis(wc))
#define th_wcisblvowel(wc)  th_isblvowel(th_uni2tis(wc))

#define th_wcchlevel(wc)    th_chlevel(th_uni2tis(wc))

END_CDECL

#endif  /* THAI_THWCTYPE_H */
