/*
 * $Id: thailib.h,v 1.3 2001-05-18 04:51:02 thep Exp $
 * thailib.h - general declarations for libthai
 * Created: 2001-05-17
 */

#ifndef THAI_THAILIB_H
#define THAI_THAILIB_H

#include <stddef.h>

#ifdef __cplusplus
# define  BEGIN_CDECL extern "C" {
# define  END_CDECL   }
#else  /* !__cplusplus */
# define  BEGIN_CDECL
# define  END_CDECL
#endif /* __cplusplus */

#define THCHAR_ERR  (~(thchar_t)0)
typedef unsigned char thchar_t;

#endif  /* THAI_THAILIB_H */

