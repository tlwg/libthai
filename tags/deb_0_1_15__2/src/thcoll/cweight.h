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
 * cweight.h - Thai Character Weight table for TIS-620/2533 Collating
 * Created: 6 Nov 1998
 * Author:  Theppitak Karoonboonyanan <thep@linux.thai.net>
 */

/*
 * The ordering algorithm is in accordance
 * with the Thai Royal Institute Dictionary
 * 2525 B.E. Edition
 */

#ifndef CWEIGHT_H
#define CWEIGHT_H

#include <thai/thailib.h>

BEGIN_CDECL

#define TOT_LEVELS  4
#define IGNORE      0

extern thchar_t th_char_weight_(thchar_t c, int level);
extern thchar_t th_char_weight_delim_(int level);

END_CDECL

#endif  /* CWEIGHT_H */

/*
vi:ts=4:ai:expandtab
*/
