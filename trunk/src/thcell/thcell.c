/*
 * $Id: thcell.c,v 1.4 2001-08-09 11:52:54 thep Exp $
 * thcell_t.c - Thai string cell custering
 * Created: 2001-08-08 (split from thrend.c)
 */

#include <thai/thcell.h>
#include <thai/thctype.h>
#include <thai/wtt.h>
#include <thai/tis.h>

#define is_composible(c1,c2) (TACio_op(c1,c2)==CP)

size_t th_next_cell(const thchar_t *s, size_t len,
                    struct thcell_t *cell, int is_decomp_am)
{
    size_t n = 0;
    cell->base = cell->hilo = cell->top = 0;
    if (len > 0) {
        do {
            switch (th_chlevel(*s)) {
                case 0:
                    if (is_decomp_am && *s == SARA_AM) { cell->hilo = *s++; }
                    else { cell->base = *s++; }
                    break;
                case -1:
                case 1: cell->hilo = *s++; break;
                case 2: cell->top  = *s++; break;
            }
            ++n; --len;
        } while (
            len > 0 && (
                is_composible(s[-1], s[0]) || (
                    is_decomp_am && s[0] == SARA_AM && th_isthcons(cell->base)
                )
            )
        );
    }
    return n;
}

size_t th_prev_cell(const thchar_t *s, size_t pos,
                    struct thcell_t *cell, int is_decomp_am)
{
    size_t n = 0;
    cell->base = cell->hilo = cell->top = 0;
    if (pos > 0) {
        do {
            thchar_t c = s[pos-1];
            switch (th_chlevel(c)) {
                case 0:
                    if (is_decomp_am && c == SARA_AM) { cell->hilo = c; }
                    else { cell->base = c; }
                    break;
                case -1:
                case 1: cell->hilo = c; break;
                case 2: cell->top  = c; break;
            }
            ++n; --pos;
        } while (
            pos > 0 && (
                is_composible(s[pos-1], s[pos]) || (
                    cell->hilo == SARA_AM &&
                    !cell->base && (
                        (!cell->top && th_isthtone(s[pos-1])) ||
                        th_isthcons(s[pos-1])
                    )
                )
            )
        );
    }
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

