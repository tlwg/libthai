/*
 * $Id: thwchar.h,v 1.9 2006-07-31 12:54:02 thep Exp $
 * thwchar.h - wide char support for Thai
 * Created: 2001-05-17
 */

#ifndef THAI_THWCHAR_H
#define THAI_THWCHAR_H

#include <thai/thailib.h>
#include <wchar.h>

BEGIN_CDECL

/**
 * @file   thwchar.h
 * @brief  Wide char support for Thai
 */

/**
 * @brief  Wide-character value indicating error
 */
#define THWCHAR_ERR  (~(thwchar_t)0)

/**
 * @brief  Thai character type for storing Unicode character
 */
typedef wchar_t thwchar_t;

/**
 * @brief  Convert character code from TIS-620 to Unicode
 *
 * @param  c : TIS-620 character to convert
 *
 * @return  Corresponding Unicode code
 */
extern thwchar_t th_tis2uni(thchar_t c);

/**
 * @brief  Convert string from TIS-620 to Unicode
 *
 * @param  s      : source TIS-620 string (null-terminated)
 * @param  result : buffer for storing resulting Unicode string
 * @param  n      : size of @a result buffer (as number of elements)
 *
 * @return  the length of the output Unicode string
 */
extern int th_tis2uni_line(const thchar_t* s, thwchar_t* result, size_t n);

/**
 * @brief  Convert character code from Thai Windows extended code to Unicode
 *
 * @param  c : Thai Windows character/glyph to convert
 *
 * @return  Corresponding Unicode code
 */
extern thwchar_t th_winthai2uni(thchar_t c);
/**
 * @brief  Convert character code from Mac Thai extended code to Unicode
 *
 * @param  c : Mac Thai character/glyph to convert
 *
 * @return  Corresponding Unicode code
 */
extern thwchar_t th_macthai2uni(thchar_t c);

/**
 * @brief  Convert character code from Unicode to TIS-620
 *
 * @param  c : Unicode character to convert
 *
 * @return  Corresponding TIS-620 code,
 *          or @c TH_ERR if conversion is impossible
 */
extern thchar_t th_uni2tis(thwchar_t c);

/**
 * @brief  Convert string from Unicode to TIS-620
 *
 * @param  s      : source Unicode string (null-terminated)
 * @param  result : buffer for storing resulting TIS-620 string
 * @param  n      : size of @a result buffer (as number of elements)
 *
 * @return  the length of the output TIS-620 string
 *
 * Note that, since the conversion is lossy, some characters in the 
 * convesion result may be @c TH_ERR, indicating conversion error.
 */
extern int th_uni2tis_line(const thwchar_t* s, thchar_t* result, size_t n);

/**
 * @brief  Convert character code from Unicode to Thai Windows extended code
 *
 * @param  c : Unicode code to convert
 *
 * @return  Corresponding Thai Windows extended code,
 *          or @c TH_ERR if conversion is impossible
 */
extern thchar_t th_uni2winthai(thwchar_t c);
/**
 * @brief  Convert character code from Unicode to Mac Thai extended code
 *
 * @param  c : Unicode code to convert
 *
 * @return  Corresponding Mac Thai extended code,
 *          or @c TH_ERR if conversion is impossible
 */
extern thchar_t th_uni2macthai(thwchar_t c);

END_CDECL

#endif  /* THAI_THWCHAR_H */

