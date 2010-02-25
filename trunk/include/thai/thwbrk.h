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
 * thwbrk.h - Thai wide-char word segmentation
 * Created: 2001-05-17
 */

#ifndef THAI_THWBRK_H
#define THAI_THWBRK_H

#include <thai/thailib.h>

BEGIN_CDECL

/**
 * @file   thwbrk.h
 * @brief  Thai wide-char word segmentation
 */

extern int th_wbrk(const thwchar_t *s, int pos[], size_t n);

extern int th_wbrk_line(const thwchar_t *in, thwchar_t *out, size_t n,
                        const thwchar_t *delim);


END_CDECL

#endif  /* THAI_THWBRK_H */

