/*
 * $Id: thwctype.c,v 1.2 2006-07-31 12:54:02 thep Exp $
 * thwctype.c - Thai wide-char character classifications
 * Created: 2001-09-14
 */

#include <thai/thwctype.h>

#undef th_wcistis

#undef th_wcisthai
#undef th_wciseng

/* Thai letter classification */
#undef th_wcisthcons
#undef th_wcisthvowel
#undef th_wcisthtone
#undef th_wcisthdigit
#undef th_wcisthdiac
#undef th_wcisthpunct

/* Thai consonant shapes classification */
#undef th_wcistaillesscons
#undef th_wcisovershootcons
#undef th_wcisundershootcons
#undef th_wcisundersplitcons

/* Thai vowel classification */
#undef th_wcisldvowel
#undef th_wcisflvowel
#undef th_wcisupvowel
#undef th_wcisblvowel

#undef th_wcchlevel


int th_wcistis(thwchar_t wc)     { return th_istis(th_uni2tis(wc)); }

int th_wcisthai(thwchar_t wc)    { return th_isthai(th_uni2tis(wc)); }
int th_wciseng(thwchar_t wc)     { return th_iseng(th_uni2tis(wc)); }

/* Thai letter classification */
int th_wcisthcons(thwchar_t wc)  { return th_isthcons(th_uni2tis(wc)); }
int th_wcisthvowel(thwchar_t wc) { return th_isthvowel(th_uni2tis(wc)); }
int th_wcisthtone(thwchar_t wc)  { return th_isthtone(th_uni2tis(wc)); }
int th_wcisthdigit(thwchar_t wc) { return th_isthdigit(th_uni2tis(wc)); }
int th_wcisthdiac(thwchar_t wc)  { return th_isthdiac(th_uni2tis(wc)); }
int th_wcisthpunct(thwchar_t wc) { return th_isthpunct(th_uni2tis(wc)); }

/* Thai consonant shapes classification */
int th_wcistaillesscons(thwchar_t wc)
    { return th_istaillesscons(th_uni2tis(wc)); }
int th_wcisovershootcons(thwchar_t wc)
    { return th_isovershootcons(th_uni2tis(wc)); }
int th_wcisundershootcons(thwchar_t wc)
    { return th_isundershootcons(th_uni2tis(wc)); }
int th_wcisundersplitcons(thwchar_t wc)
    { return th_isundersplitcons(th_uni2tis(wc)); }

/* Thai vowel classification */
int th_wcisldvowel(thwchar_t wc) { return th_isldvowel(th_uni2tis(wc)); }
int th_wcisflvowel(thwchar_t wc) { return th_isflvowel(th_uni2tis(wc)); }
int th_wcisupvowel(thwchar_t wc) { return th_isupvowel(th_uni2tis(wc)); }
int th_wcisblvowel(thwchar_t wc) { return th_isblvowel(th_uni2tis(wc)); }

int th_wcchlevel(thwchar_t wc)   { return th_chlevel(th_uni2tis(wc)); }

