/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
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
 * brk-common.c - Common code for word break backends
 * Created: 2014-08-03
 * Author:  Theppitak Karoonboonyanan <thep@linux.thai.net>
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <datrie/trie.h>
#include <thai/tis.h>
#include <thai/thctype.h>
#include "brk-common.h"

#define DICT_NAME   "thbrk"

static Trie *brk_dict = 0;

void
brk_on_unload ()
{
    if (brk_dict) {
        trie_free (brk_dict);
    }
}

Trie *
brk_get_dict ()
{
    static int is_dict_tried = 0;

    if (!brk_dict && !is_dict_tried) {
        const char *dict_dir;
        char        path[512];

        /* Try LIBTHAI_DICTDIR env first */
        if (NULL != (dict_dir = getenv ("LIBTHAI_DICTDIR"))) {
            snprintf (path, sizeof path, "%s/%s.tri", dict_dir, DICT_NAME);
            brk_dict = trie_new_from_file (path);
        }

        /* Then, fall back to default DICT_DIR macro */
        if (!brk_dict) {
            brk_dict = trie_new_from_file (DICT_DIR "/" DICT_NAME ".tri");
        }

        if (!brk_dict) {
            if (dict_dir) {
                fprintf (stderr,
                         "LibThai: Fail to open dictionary at '%s' and '%s'.\n",
                         path, DICT_DIR "/" DICT_NAME ".tri");
            } else {
                fprintf (stderr,
                         "LibThai: Fail to open dictionary at '%s'.\n",
                         DICT_DIR "/" DICT_NAME ".tri");
            }
        }

        is_dict_tried = 1;
    }

    return brk_dict;
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
