/*
 * libthai - Thai Language Support Library
 * Copyright (C) 2001  Theppitak Karoonboonyanan <thep@linux.thai.net>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

/*
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

