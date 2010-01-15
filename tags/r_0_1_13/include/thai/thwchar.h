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

extern thwchar_t th_tis2uni(thchar_t c);

extern int th_tis2uni_line(const thchar_t* s, thwchar_t* result, size_t n);

extern thwchar_t th_winthai2uni(thchar_t c);
extern thwchar_t th_macthai2uni(thchar_t c);

extern thchar_t th_uni2tis(thwchar_t wc);

extern int th_uni2tis_line(const thwchar_t* s, thchar_t* result, size_t n);

extern thchar_t th_uni2winthai(thwchar_t wc);
extern thchar_t th_uni2macthai(thwchar_t wc);

END_CDECL

#endif  /* THAI_THWCHAR_H */

