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
 * libthai.c - main source for libthai
 * Created: 2008-12-23
 * Author:  Theppitak Karoonboonyanan <thep@linux.thai.net>
 */

/**
 * @mainpage
 *
 * LibThai is a set of Thai language support routines aimed to ease
 * developers' tasks to incorporate Thai language support in their
 * applications. It includes important Thai-specific functions e.g. word
 * breaking, input and output methods as well as basic character and
 * string supports. LibThai is an Open Source and collaborative effort
 * initiated by Thai Linux Working Group and opened for all contributors.
 *
 * @section LibThaiFuncs LibThai Functions by Category
 *
 * LibThai provides functions to handle both tis-620 character
 * set (single-byte) and unicode (multi-byte). A function name which
 * includes `w', such as th_wbrk() is unicode version of th_brk() function. 
 *
 * @subsection ThCType Functions for classifying characters
 *
 * th_istis(), th_isthai(), th_iseng(), th_isthcons(), th_isthvowel(), 
 * th_isthtone(), th_isthdiac(), th_isthdigit(), th_isthpunct(), 
 * th_istaillesscons(), th_isovershootcons(), th_isundershootcons(), 
 * th_isundersplitcons(), th_isldvowel(), th_isflvowel(), th_isupvowel(), 
 * th_isblvowel(), th_chlevel(), th_iscombchar(), th_wcistis(), th_wcisthai(), 
 * th_wciseng(), th_wcisthcons(), th_wcisthvowel(), th_wcisthtone(), 
 * th_wcisthdiac(), th_wcisthdigit(), th_wcisthpunct(), th_wcistaillesscons(), 
 * th_wcisovershootcons(), th_wcisundershootcons(), th_wcisundersplitcons(), 
 * th_wcisldvowel(), th_wcisflvowel(), th_wcisupvowel(), th_wcisblvowel(), 
 * th_wcchlevel(), th_wciscombchar()
 *
 * @subsection ThBrk Functions for word segmentation
 *
 * th_brk(), th_brk_line(), th_wbrk(), th_wbrk_line()
 *
 * @subsection ThColl Functions for Thai string collation
 *
 * th_strcoll(), th_strxfrm(), th_wcstrcoll(), th_wcstrxfrm()
 *
 * @subsection ThStr Functions for correct the sequence of Thai string
 *
 * th_normalize(), th_wnormalize()
 *
 * @subsection ThCell Functions for Thai string cell operation
 *
 * th_next_cell(), th_prev_cell(), th_make_cells()
 *
 * @subsection ThInp Functions for Thai characters input
 *
 * th_isaccept(), th_validate()
 *
 * @subsection ThRend Functions for Thai string rendering
 *
 * th_render_cell_tis(), th_render_cell_win(), th_render_cell_mac(),
 * th_render_text_tis(), th_render_text_win(), th_render_text_mac()
 *
 * @subsection ThWChar Functions for converting between unicode and tis-620
 *
 * th_tis2uni(), th_tis2uni_line(), th_winthai2uni(), th_macthai2uni(),
 * th_uni2tis(), th_uni2tis_line(), th_uni2winthai(), th_uni2macthai()
 *
 */

#include "thbrk/brk-common.h"

__attribute__ ((destructor)) void
_libthai_on_unload ()
{
    brk_on_unload ();
}

/*
vi:ts=4:ai:expandtab
*/
