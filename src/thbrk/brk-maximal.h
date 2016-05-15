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
 * brk-maximal.h - Thai word break with maximal matching scheme
 * Created: 2006-08-20
 * Author:  Theppitak Karoonboonyanan <theppitak@gmail.com>
 */

#ifndef __BRK_MAXIMAL_H
#define __BRK_MAXIMAL_H

#include <thai/thailib.h>
#include <thai/thbrk.h>

typedef struct _BrkEnv BrkEnv;

BrkEnv *
brk_env_new (const ThDict *dict);

void
brk_env_free (BrkEnv *env);

int
brk_maximal_do (const thchar_t *s, int len, int pos[], size_t n, BrkEnv *env);

#endif /* __BRK_MAXIMAL_H */

/*
vi:ts=4:ai:expandtab
*/
