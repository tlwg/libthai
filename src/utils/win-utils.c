/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * libthai - Thai Language Support Library
 *
 * SPDX-FileCopyrightText: 2001-2026 Theppitak Karoonboonyanan <theppitak@gmail.com>
 * SPDX-FileType: SOURCE
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */

/*
 * win-utils.c - Windows-specific private utilities
 * Created: 2026-07-25
 * Author: Arthit Suriyawongkul <suriyawa@tcd.ie>
 */

#include "utils/win-utils.h"

#if defined (_WIN32) && !defined (__CYGWIN__)
#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>
#include <stdlib.h>
#include <wchar.h>

void _libthai_on_unload (void);

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved);

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    (void) hinstDLL;
    if (fdwReason == DLL_PROCESS_DETACH) {
        /* Skip cleanup if the whole process is exiting (lpvReserved != NULL);
         * other DLLs may already be gone */
        if (!lpvReserved)
            _libthai_on_unload ();
    }
    return TRUE;
}

/* Reverse search for needle in the first n wchar_t of haystack;
 * NULL if absent.
 */
static const wchar_t *
wmemrchr_bound (const wchar_t *haystack, wchar_t needle, size_t n)
{
    const wchar_t *p;
    if (n == 0)
        return NULL;
    for (p = haystack + n - 1; p >= haystack; --p) {
        if (*p == needle)
            return p;
    }
    return NULL;
}

/* True if s starts with marker (case-insensitively) followed by '\\'. */
static int
segment_matches (const wchar_t *s, const wchar_t *marker)
{
    size_t len = wcslen (marker);
    return _wcsnicmp (s, marker, len) == 0 && s[len] == L'\\';
}

/* Install dir = parent of nearest "bin"/"lib"/"bin64"/"lib64" ancestor,
 * else path's own dir.
 * C:\Program Files\App\bin\libthai.dll -> C:\Program Files\App
 * C:\Program Files\App\libthai.dll     -> C:\Program Files\App
 */
static wchar_t *
win_find_inst_dir (const wchar_t *filepath)
{
    size_t n = wcslen (filepath);
    const wchar_t *base_end = NULL;
    size_t len;
    wchar_t *result;

    /* Scan segments right-to-left for a known install-layout marker dir */
    for (;;) {
        const wchar_t *p = wmemrchr_bound (filepath, L'\\', n);
        if (!p)
            break;
        if (segment_matches (p + 1, L"bin") ||
            segment_matches (p + 1, L"lib") ||
            segment_matches (p + 1, L"bin64") ||
            segment_matches (p + 1, L"lib64")) {
            base_end = p;
            break;
        }
        n = (size_t) (p - filepath);
    }

    /* Not found: fall back to the DLL's own directory */
    if (!base_end) {
        const wchar_t *p = wcsrchr (filepath, L'\\');
        base_end = p ? p : filepath;
    }

    len = (size_t) (base_end - filepath);
    result = (wchar_t *) malloc ((len + 1) * sizeof (wchar_t));
    if (!result)
        return NULL;
    wmemcpy (result, filepath, len);
    result[len] = L'\0';
    return result;
}

static wchar_t *cached_dir = NULL;
static int computed = 0;

wchar_t *
win_inst_dir (void)
{
    /* Windows stores paths natively as UTF-16 */
    /* Cached: the install dir is invariant for the process's life. */
    HMODULE hmod = NULL;
    wchar_t *path;
    DWORD len;

    if (computed)
        return cached_dir;
    computed = 1;

    if (!GetModuleHandleExW (GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,
                              (LPCWSTR) &win_inst_dir, &hmod))
        return NULL;

    path = (wchar_t *) malloc (MAX_PATH * sizeof (wchar_t));
    if (!path)
        return NULL;

    len = GetModuleFileNameW (hmod, path, MAX_PATH);
    if (len == 0 || len >= MAX_PATH) {
        free (path);
        return NULL;
    }

    cached_dir = win_find_inst_dir (path);
    free (path);
    return cached_dir;
}

void
win_inst_dir_free (void)
{
    free (cached_dir);
    cached_dir = NULL;
    computed = 0;
}
#endif /* _WIN32 && !__CYGWIN__ */

/*
vi:ts=4:ai:expandtab
*/
