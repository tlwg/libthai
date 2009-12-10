/*
 * $Id: thcell.c,v 1.10 2007-10-18 14:52:29 thep Exp $
 * thcell_t.c - Thai string cell custering
 * Created: 2001-08-08 (split from thrend.c)
 * Author: Theppitak Karoonboonyanan <thep@linux.thai.net>
 */

#include <thai/thcell.h>
#include <thai/thctype.h>
#include <thai/wtt.h>
#include <thai/tis.h>

#define is_composible(c1,c2) (TACio_op(c1,c2)==CP)

void th_init_cell(struct thcell_t *cell)
{
    cell->base = 0;
    cell->hilo = 0;
    cell->top = 0;
}

size_t th_next_cell(const thchar_t *s, size_t len,
                    struct thcell_t *cell, int is_decomp_am)
{
    size_t n = 0;
    struct thcell_t acell;
    acell.base = acell.hilo = acell.top = 0;
    if (len > 0) {
        do {
            switch (th_chlevel(*s)) {
                case 0:
                    if (is_decomp_am && *s == SARA_AM) { acell.hilo = *s++; }
                    else { acell.base = *s++; }
                    break;
                case -1:
                case 1: acell.hilo = *s++; break;
                case 2: acell.top  = *s++; break;
                case 3:
                    if (!acell.hilo) { acell.hilo = *s++; }
		    else { acell.top = *s++; }
		    break;
            }
            ++n; --len;
        } while (
            len > 0 && (
                is_composible(s[-1], s[0]) || (
                    is_decomp_am && s[0] == SARA_AM
                    && th_isthcons(acell.base) && acell.hilo == 0
                )
            )
        );
    }
    if (cell) { *cell = acell; }
    return n;
}

size_t th_prev_cell(const thchar_t *s, size_t pos,
                    struct thcell_t *cell, int is_decomp_am)
{
    size_t n = 0;
    struct thcell_t acell;
    acell.base = acell.hilo = acell.top = 0;
    if (pos > 0) {
        do {
            thchar_t c = s[pos-1];
            switch (th_chlevel(c)) {
                case 0:
                    if (is_decomp_am && c == SARA_AM) { acell.hilo = c; }
                    else { acell.base = c; }
                    break;
                case 1: 
                    if (acell.hilo && th_chlevel(acell.hilo) == 3) {
                        acell.top = acell.hilo;
                    }
                    /* fall through */
                case -1: acell.hilo = c; break;
                case 2: acell.top  = c; break;
                case 3:
                    if (!acell.hilo) { acell.hilo = c; }
		    else { acell.top = c; }
		    break;
            }
            ++n; --pos;
        } while (
            pos > 0 && (
                is_composible(s[pos-1], s[pos]) || (
                    acell.hilo == SARA_AM &&
                    !acell.base && (
                        (!acell.top && th_isthtone(s[pos-1])) ||
                        th_isthcons(s[pos-1])
                    )
                )
            )
        );
    }
    if (cell) { *cell = acell; }
    return n;
}

size_t th_make_cells(const thchar_t *s, size_t len,
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

