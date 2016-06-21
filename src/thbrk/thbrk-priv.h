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
 * thbrk-priv.h - Private declarations for thbrk.c
 * Created: 2015-05-06
 * Author:  Theppitak Karoonboonyanan <theppitak@gmail.com>
 */

#ifndef __THBRK_PRIV_H
#define __THBRK_PRIV_H

#include <datrie/trie.h>
#include <thai/thbrk.h>

struct _ThBrk {
    Trie           *dict_trie;
};

ThBrk * brk_get_shared_brk ();

void    brk_free_shared_brk ();

#endif  /* __THBRK_PRIV_H */

/*
vi:ts=4:ai:expandtab
*/

