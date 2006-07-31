/*
 * $Id: thailib.h,v 1.6 2006-07-31 11:07:46 thep Exp $
 * thailib.h - general declarations for libthai
 * Created: 2001-05-17
 */

#ifndef THAI_THAILIB_H
#define THAI_THAILIB_H

/**
 * @file   thailib.h
 * @brief  General declarations for libthai
 */

#include <stddef.h>

#ifdef __cplusplus
# define  BEGIN_CDECL extern "C" {
# define  END_CDECL   }
#else  /* !__cplusplus */
# define  BEGIN_CDECL
# define  END_CDECL
#endif /* __cplusplus */

/**
 * @brief  Character value indicating error
 */
#define THCHAR_ERR  ((thchar_t)~0)

/**
 * @brief  Thai character type for storing TIS-620 character
 */
typedef unsigned char thchar_t;

#endif  /* THAI_THAILIB_H */

