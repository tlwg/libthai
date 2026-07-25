/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * libthai - Thai Language Support Library
 * Copyright (C) 2015  Theppitak Karoonboonyanan <theppitak@gmail.com>
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
 * priv-utils.h - Common private utilities
 * Created: 2015-05-06
 * Author:  Theppitak Karoonboonyanan <theppitak@gmail.com>
 */

#ifndef __PRIV_UTILS_H
#define __PRIV_UTILS_H

#if defined(__GNUC__) && (__GNUC__ > 2) && defined(__OPTIMIZE__)
#define LIKELY(expr) (__builtin_expect (!!(expr), 1))
#define UNLIKELY(expr) (__builtin_expect (!!(expr), 0))
#else
#define LIKELY(expr) (expr)
#define UNLIKELY(expr) (expr)
#endif

#if defined (_WIN32) && !defined (__CYGWIN__)
#include <wchar.h>

/* Absolute directory of the loaded libthai DLL, or NULL on failure.
 * The returned pointer is cached and owned by the library;
 * valid for the process's lifetime, the caller must not free it. */
wchar_t * win_inst_dir (void);

/* Free the pointer cached by win_inst_dir(). Call once on unload. */
void win_inst_dir_free (void);
#endif

#endif  /* __PRIV_UTILS_H */

/*
vi:ts=4:ai:expandtab
*/
