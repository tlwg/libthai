/*
 * $Id: thstr.h,v 1.2 2006-07-31 11:07:46 thep Exp $
 * thstr.h - Thai string manipulators
 * Created: 2001-08-03
 */

#ifndef THAI_THSTR_H
#define THAI_THSTR_H

#include <thai/thailib.h>

BEGIN_CDECL

/**
 * @file   thstr.h
 * @brief  Thai string manipulators
 */

extern size_t th_normalize(thchar_t dest[], const thchar_t *src, size_t n);

END_CDECL

#endif  /* THAI_THSTR_H */

