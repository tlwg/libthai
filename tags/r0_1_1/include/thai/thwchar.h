/*
 * $Id: thwchar.h,v 1.6 2001-08-04 14:58:00 thep Exp $
 * thwchar.h - wide char support for Thai
 * Created: 2001-05-17
 */

#ifndef THAI_THWCHAR_H
#define THAI_THWCHAR_H

#include <thai/thailib.h>
#include <wchar.h>

BEGIN_CDECL

#define THWCHAR_ERR  (~(thwchar_t)0)
typedef wchar_t thwchar_t;

/* 
 * th_tis2uni -- Character converter from tis620-0 to Unicode
 *
 * @param c : source tis620-0 character
 * Returns: result Unicode character
 */
extern thwchar_t th_tis2uni(thchar_t c);

/* 
 * th_tis2uni_line -- String converter from tis620-0 to Unicode
 *
 * @param s : source tis620-0 string
 * @param result : result Unicode string
 * @param n : allocated size of result variable
 * Returns: the length of the real output Unicode string size
 */
extern int th_tis2uni_line(const thchar_t* s, thwchar_t* result, size_t n);

extern thwchar_t th_winthai2uni(thchar_t c);
extern thwchar_t th_macthai2uni(thchar_t c);

/* 
 * th_uni2tis -- Character converter from Unicode to tis620-0
 *
 * @param c : source Unicode character
 * Returns: result tis620-0 character
 */
extern thchar_t th_uni2tis(thwchar_t c);

/*
 * th_uni2tis_line -- String converter from Unicode to tis620-0
 *
 * @param s : source Unicode string
 * @param result : result tis620-0 string
 * @param n : allocated size of result variable
 * Returns: the length of the real output string size
 */
extern int th_uni2tis_line(const thwchar_t* s, thchar_t* result, size_t n);

extern thchar_t th_uni2winthai(thwchar_t c);
extern thchar_t th_uni2macthai(thwchar_t c);

END_CDECL

#endif  /* THAI_THWCHAR_H */

