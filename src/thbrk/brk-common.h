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
 * brk-common.h - Common code for word break backends
 * Created: 2008-12-23
 * Author:  Theppitak Karoonboonyanan <theppitak@gmail.com>
 */

#ifndef __BRK_COMMON_H
#define __BRK_COMMON_H

#include <thai/thbrk.h>
#include <thai/thctype.h>
#include <datrie/trie.h>

ThBrk * brk_dict_new (const char *dictpath);

void    brk_dict_delete (ThBrk *brk);

Trie *  brk_dict_trie (ThBrk *brk);

ThBrk * brk_get_shared_dict ();

void    brk_free_shared_dict ();

void    brk_brkpos_hints (const thchar_t *str, int len, char *hints);

#endif  /* __BRK_COMMON_H */

/*
vi:ts=4:ai:expandtab
*/
