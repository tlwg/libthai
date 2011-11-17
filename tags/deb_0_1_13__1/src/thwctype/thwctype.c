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


/**
 * @brief  Is the wide character convertible to a valid TIS-620 code?
 *
 * TIS-620 here means US-ASCII plus TIS-620 extension.
 */
int th_wcistis(thwchar_t wc)     { return th_istis(th_uni2tis(wc)); }

/**
 * @brief  Is the wide character a Thai character?
 */
int th_wcisthai(thwchar_t wc)    { return th_isthai(th_uni2tis(wc)); }
/**
 * @brief  Is the wide character an English character?
 */
int th_wciseng(thwchar_t wc)     { return th_iseng(th_uni2tis(wc)); }

/* Thai letter classification */
/**
 * @brief  Is the wide character a Thai consonant?
 */
int th_wcisthcons(thwchar_t wc)  { return th_isthcons(th_uni2tis(wc)); }
/**
 * @brief  Is the wide character a Thai vowel?
 */
int th_wcisthvowel(thwchar_t wc) { return th_isthvowel(th_uni2tis(wc)); }
/**
 * @brief  Is the wide character a Thai tone mark?
 */
int th_wcisthtone(thwchar_t wc)  { return th_isthtone(th_uni2tis(wc)); }
/**
 * @brief  Is the wide character a Thai diacritic?
 */
int th_wcisthdiac(thwchar_t wc)  { return th_isthdiac(th_uni2tis(wc)); }
/**
 * @brief  Is the character a Thai digit?
 */
int th_wcisthdigit(thwchar_t wc) { return th_isthdigit(th_uni2tis(wc)); }
/**
 * @brief  Is the character a Thai punctuation?
 */
int th_wcisthpunct(thwchar_t wc) { return th_isthpunct(th_uni2tis(wc)); }

/* Thai consonant shapes classification */
/**
 * @brief  Is the wide character a Thai consonant that fits the x-height?
 */
int th_wcistaillesscons(thwchar_t wc)
    { return th_istaillesscons(th_uni2tis(wc)); }
/**
 * @brief  Is the wide character a Thai consonant with stem above ascender?
 */
int th_wcisovershootcons(thwchar_t wc)
    { return th_isovershootcons(th_uni2tis(wc)); }
/**
 * @brief  Is the wide character a Thai consonant with stem below baseline?
 */
int th_wcisundershootcons(thwchar_t wc)
    { return th_isundershootcons(th_uni2tis(wc)); }
/**
 * @brief  Is the wide character a Thai consonant with split part below 
 *         baseline?
 */
int th_wcisundersplitcons(thwchar_t wc)
    { return th_isundersplitcons(th_uni2tis(wc)); }

/* Thai vowel classification */
/**
 * @brief  Is the wide character a Thai leading vowel?
 */
int th_wcisldvowel(thwchar_t wc) { return th_isldvowel(th_uni2tis(wc)); }
/**
 * @brief  Is the wide character a Thai following vowel?
 */
int th_wcisflvowel(thwchar_t wc) { return th_isflvowel(th_uni2tis(wc)); }
/**
 * @brief  Is the wide character a Thai upper vowel?
 */
int th_wcisupvowel(thwchar_t wc) { return th_isupvowel(th_uni2tis(wc)); }
/**
 * @brief  Is the wide character a Thai below vowel?
 */
int th_wcisblvowel(thwchar_t wc) { return th_isblvowel(th_uni2tis(wc)); }

/**
 * @brief  Position for rendering:
 *   @li   3 = above/top
 *   @li   2 = top
 *   @li   1 = above
 *   @li   0 = base
 *   @li  -1 = below
 */
int th_wcchlevel(thwchar_t wc)   { return th_chlevel(th_uni2tis(wc)); }
