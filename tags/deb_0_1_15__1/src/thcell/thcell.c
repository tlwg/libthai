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
 * thcell_t.c - Thai string cell custering
 * Created: 2001-08-08 (split from thrend.c)
 * Author: Theppitak Karoonboonyanan <thep@linux.thai.net>
 */

#include <thai/thcell.h>
#include <thai/thctype.h>
#include <thai/wtt.h>
#include <thai/tis.h>

#define is_composible(c1,c2) (TACio_op(c1,c2)==CP)

/**
 * @brief  Initialize a Thai cell
 *
 * @param  cell : pointer to the cell to initialize
 *
 * Initializes values in the Thai cell struct.
 */
void
th_init_cell (struct thcell_t *cell)
{
    cell->base = 0;
    cell->hilo = 0;
    cell->top = 0;
}

/**
 * @brief  Get first cell from string
 *
 * @param  s    : the string
 * @param  len  : the length of string
 * @param  cell : the output buffer
 * @param  is_decomp_am : whether SARA AM is to be decomposed into 
 *                        NIKHANIT and SARA AA and to be in separate cells
 *
 * @returns  total chars consumed by the cell
 *
 * Gets first cell from the string bounded by @a s and @a len, and, if @a cell
 * is not null, stores the cell data in it.
 */
size_t
th_next_cell (const thchar_t *s, size_t len,
              struct thcell_t *cell, int is_decomp_am)
{
    size_t n = 0;
    struct thcell_t acell;
    acell.base = acell.hilo = acell.top = 0;
    if (len > 0) {
        do {
            switch (th_chlevel (*s)) {
            case 0:
                if (is_decomp_am && *s == TIS_SARA_AM) {
                    acell.hilo = *s++;
                } else {
                    acell.base = *s++;
                }
                break;
            case -1:
            case 1:
                acell.hilo = *s++;
                break;
            case 2:
                acell.top  = *s++;
                break;
            case 3:
                if (!acell.hilo) {
                    acell.hilo = *s++;
                } else {
                    acell.top = *s++;
                }
                break;
            }
            ++n; --len;
        } while (
            len > 0 && (
                is_composible (s[-1], s[0]) || (
                    is_decomp_am && s[0] == TIS_SARA_AM
                    && th_isthcons (acell.base) && acell.hilo == 0
                )
            )
        );
    }
    if (cell) {
        *cell = acell;
    }
    return n;
}

/**
 * @brief  Get previous cell from string
 *
 * @param  s    : the string
 * @param  pos  : the position in string to get cell previous to
 * @param  cell : the output buffer
 * @param  is_decomp_am : whether SARA AM is to be decomposed into 
 *                        NIKHANIT and SARA AA and to be in separate cells
 *
 * @returns  total chars consumed by the cell
 *
 * Gets last cell from the string bounded by @a s and @a pos, and if @a cell
 * is not null, stores the cell data in it.
 */
size_t
th_prev_cell (const thchar_t *s, size_t pos,
              struct thcell_t *cell, int is_decomp_am)
{
    size_t n = 0;
    struct thcell_t acell;
    acell.base = acell.hilo = acell.top = 0;
    if (pos > 0) {
        do {
            thchar_t c = s[pos-1];
            switch (th_chlevel (c)) {
            case 0:
                if (is_decomp_am && c == TIS_SARA_AM) {
                    acell.hilo = c;
                } else {
                    acell.base = c;
                }
                break;
            case 1: 
                if (acell.hilo && th_chlevel(acell.hilo) == 3) {
                    acell.top = acell.hilo;
                }
                /* fall through */
            case -1:
                acell.hilo = c;
                break;
            case 2:
                acell.top  = c;
                break;
            case 3:
                if (!acell.hilo) {
                    acell.hilo = c;
                } else {
                    acell.top = c;
                }
                break;
            }
            ++n; --pos;
        } while (
            pos > 0 && (
                is_composible (s[pos-1], s[pos]) || (
                    acell.hilo == TIS_SARA_AM &&
                    !acell.base && (
                        (!acell.top && th_isthtone (s[pos-1])) ||
                        th_isthcons (s[pos-1])
                    )
                )
            )
        );
    }
    if (cell) {
        *cell = acell;
    }
    return n;
}

/**
 * @brief  Tokenize string into cells
 *
 * @param  s      : the string
 * @param  len    : the length of string
 * @param  cells  : the array of output cells buffer
 * @param  ncells : the address of integer storing the number of cells 
 *                  provided by the buffer, and to keep the number of resulting 
 *                  cells on return
 * @param  is_decomp_am : whether SARA AM is to be decomposed into 
 *                        NIKHANIT and SARA AA and to be in separate cells
 *
 * @returns  total characters consumed
 *
 * Tokenizes the string bounded by @a s and @a len into cells, and stores
 * at most @a *ncells resulting cells in the @a cells buffer. On return,
 * @a *ncells is also set to the total cells stored in @a cells[].
 */
size_t
th_make_cells (const thchar_t *s, size_t len,
               struct thcell_t cells[], size_t *ncells, int is_decomp_am)
{
    size_t left = *ncells;
    size_t nchars = 0;

    while (len > 0 && left > 0) {
        size_t n = th_next_cell(s + nchars, len, cells, is_decomp_am);
        nchars += n; len -= n;
        ++cells; --left;
    }
    *ncells -= left;
    return nchars;
}

/*
vi:ts=4:ai:expandtab
*/
