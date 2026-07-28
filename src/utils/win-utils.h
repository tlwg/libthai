/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * libthai - Thai Language Support Library
 *
 * SPDX-FileCopyrightText: 2001-2026 Theppitak Karoonboonyanan <theppitak@gmail.com>
 * SPDX-FileType: SOURCE
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */

/*
 * win-utils.h - Windows-specific private utilities
 * Created: 2026-07-29
 * Author: Arthit Suriyawongkul <suriyawa@tcd.ie>
 */

#ifndef __WIN_UTILS_H
#define __WIN_UTILS_H

#if defined (_WIN32) && !defined (__CYGWIN__)
#include <wchar.h>

/* Absolute directory of the loaded libthai DLL, or NULL on failure.
 * The returned pointer is cached and owned by the library;
 * valid for the process's lifetime, the caller must not free it. */
wchar_t * win_inst_dir (void);

/* Free the pointer cached by win_inst_dir(). Call once on unload. */
void win_inst_dir_free (void);
#endif

#endif  /* __WIN_UTILS_H */

/*
vi:ts=4:ai:expandtab
*/
