/*
 * $Id: thwstr.h,v 1.3 2006-07-31 12:54:02 thep Exp $
 * thwstr.h - Thai wide-char string manipulators
 * Created: 2001-08-03
 */

#ifndef THAI_THWSTR_H
#define THAI_THWSTR_H

#include <thai/thailib.h>
#include <thai/thwchar.h>

BEGIN_CDECL

/**
 * @file   thwstr.h
 * @brief  Thai wide-char string manipulators
 */

extern size_t th_wnormalize(thwchar_t dest[], const thwchar_t *src, size_t n);

END_CDECL

#endif  /* THAI_THWSTR_H */

