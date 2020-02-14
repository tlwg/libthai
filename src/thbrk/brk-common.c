/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * libthai - Thai Language Support Library
 * Copyright (C) 2001  Theppitak Karoonboonyanan <theppitak@gmail.com>
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
 * brk-common.c - Common code for word break backends
 * Created: 2014-08-03
 * Author:  Theppitak Karoonboonyanan <theppitak@gmail.com>
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <datrie/trie.h>
#include <thai/tis.h>
#include <thai/thctype.h>
#include "thbrk-utils.h"
#include "brk-common.h"

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>

#if !defined (__GNUC__) && !defined (__clang__)
#ifdef MSVC_BUILD_LIBTHAI_TESTS
/* Externally refer to brk_free_shared_brk() when building the tests for
 * Visual Studio so that we do not need to depend on $(srcroot)\src\libthai.c
 * to build the tests
 */
extern void brk_free_shared_brk ();
#define _libthai_on_unload brk_free_shared_brk

#else
extern void _libthai_on_unload ();
#endif /* MSVC_BUILD_LIBTHAI_TESTS */
#endif /* !__GNUC__ && !__clang__ */

/* This way, we can use the current directory where the .exe is if no DLL is built, such as in tests */
static HMODULE libthai_dll = NULL;

BOOL WINAPI DllMain(HINSTANCE hinstDLL,
                    DWORD     fdwReason,
                    LPVOID    lpvReserved);

BOOL WINAPI DllMain(HINSTANCE hinstDLL,
                    DWORD     fdwReason,
                    LPVOID    lpvReserved)
{
    switch (fdwReason)
        {
            case DLL_PROCESS_ATTACH:
                libthai_dll = hinstDLL;
                break;

#if !defined (__GNUC__) && !defined (__clang__)
            /* fallback for lack of GCC's __attribute__((destructor)) */
            case DLL_PROCESS_DETACH:
                _libthai_on_unload ();
                break;
#endif
        }

    return TRUE;
}

/*
 * modelled around GLib's g_win32_get_package_installation_directory_of_module()
 * without Cygwin support
 */
#ifndef __CYGWIN__
char *
libthai_get_installdir (HMODULE hmodule)
{
    char *retval;
	char *filename;
    char *p;
    wchar_t wc_fn[MAX_PATH];
    size_t length;
    size_t converted = 0;

    /* NOTE: it relies that GetModuleFileNameW returns only canonical paths */
    if (!GetModuleFileNameW (hmodule, wc_fn, MAX_PATH))
      return NULL;

    length = wcslen(wc_fn);
    filename = (char *)malloc (sizeof(char) * (length * 2 + 1));
    wcstombs_s(&converted, filename, length * 2, wc_fn, _TRUNCATE);

    if ((p = strrchr (filename, '\\')) != NULL)
        *p = '\0';

    retval = (char *)malloc (sizeof(char) * (length * 2 + 1));
	memcpy (retval, filename, strlen(filename));

    do
        {
            p = strrchr (retval, '\\');
            if (p == NULL)
                break;

            *p = '\0';

            if (_stricmp (p + 1, "bin") == 0 ||
                _stricmp (p + 1, "lib") == 0)
                break;
        }
    while (p != NULL);

    if (p == NULL)
        {
          free (retval);
          retval = filename;
        }
    else
        free (filename);

    return retval;
}
#endif /* !__CYGWIN__ */
#endif /* _WIN32 */

#define DICT_NAME   "thbrk"

static char *
full_path (const char *path, const char *name, const char *ext)
{
    int full_size = strlen (path) + strlen (name) + strlen (ext) + 2;
    char *full_path_buff = (char *) malloc (full_size);
    sprintf (full_path_buff, "%s/%s%s", path, name, ext);
    return full_path_buff;
}

Trie *
brk_load_default_dict ()
{
    const char *dict_dir;
    Trie       *dict_trie = NULL;

    /* Try LIBTHAI_DICTDIR env first */
    dict_dir = getenv ("LIBTHAI_DICTDIR");
    if (dict_dir) {
        char *path = full_path (dict_dir, DICT_NAME, ".tri");
        dict_trie = trie_new_from_file (path);
        free (path);
    }

    /* Then, fall back to default DICT_DIR macro or relative $(datadir)\share\libthai for native Windows DLL */
    if (!dict_trie) {
#if defined (_WIN32) && !defined (__CYGWIN__)
        char *basedir = libthai_get_installdir (libthai_dll);
        const char *sharedir = "share\\libthai\\" DICT_NAME ".tri";
        size_t total_len = strlen (basedir) + strlen (sharedir) + 1; /* '+ 1' for the '\\' that we are using below */
        char *filepath = (char *) malloc (sizeof (char) * (total_len + 1));
        sprintf (filepath, "%s\\%s", basedir, sharedir);
        dict_trie = trie_new_from_file (filepath);
        free (filepath);
        free (basedir);
#else
        dict_trie = trie_new_from_file (DICT_DIR "/" DICT_NAME ".tri");
#endif
    }

    return dict_trie;
}

void
brk_brkpos_hints (const thchar_t *str, int len, char *hints)
{
    int  i;

    if (len < 0)
        len = strlen ((const char *)str);

    memset (hints, 0, len);

    for (i = 0; i < len; /* nop */) {
        if (th_isthcons (str[i])) {
            if (i+1 < len && str[i+1] == TIS_THANTHAKHAT) {
                i += 2; /* the cons + THANTHAKHAT */
            } else if (i+2 < len && str[i+2] == TIS_THANTHAKHAT) {
                i += 3; /* the cons + intermediate char + THANTHAKHAT */
            } else if (i+2 < len
                       && str[i] != TIS_KO_KAI && str[i+1] == TIS_MAITAIKHU
                       && (str[i+2] == TIS_O_ANG || str[i+2] == TIS_WO_WAEN))
            {
                hints[i] = 1;
                i += 4; /* the cons + MAITAIKHU + OANG/WOWAEN + cons */
            } else if ((i > 0
                        && (str[i-1] == TIS_MAI_HAN_AKAT
                            || str[i-1] == TIS_SARA_UEE))
                       || (i > 1 && th_isthtone (str[i-1])
                           && (str[i-2] == TIS_MAI_HAN_AKAT
                               || str[i-2] == TIS_SARA_UEE)))
            {
                i++;
            } else {
                hints[i++] = 1;
            }
        } else if (str[i] == TIS_SARA_E || str[i] == TIS_SARA_AE) {
            hints[i] = 1; /* sara e/ae */
            i += 2; /* sara e/ae + the supposedly cons */
            if (i >= len)
                break;
            if (str[i] == TIS_MAITAIKHU) {
                i += 2; /* MAITAIKHU + the supposedly cons */
            } else if (th_isupvowel (str[i])) {
                i++; /* the upper vowel, as part of composite vowel */
                if (i < len && th_isthtone (str[i]))
                    i++;
                i++; /* the supposedly cons */
            } else if (i+2 < len
                       && ((str[i+1] == TIS_SARA_AA && str[i+2] == TIS_SARA_A)
                            || (str[i] != TIS_KO_KAI
                                && str[i+1] == TIS_MAITAIKHU
                                && str[i+2] != TIS_O_ANG
                                && str[i+2] != TIS_WO_WAEN)))
            {
                i += 3; /* 2nd cons + SARA_AA + SARA_A, or
                         * 2nd cons + MAITAIKHU + final cons
                         */
            }
        } else if (th_isldvowel (str[i])) {
            hints[i] = 1; /* the ldvowel */
            i += 2; /* the ldvowel + the supposedly cons */
        } else if (str[i] == TIS_RU || str[i] == TIS_LU) {
            hints[i++] = 1;
        } else {
            i++;
        }
    }
}

/*
vi:ts=4:ai:expandtab
*/
