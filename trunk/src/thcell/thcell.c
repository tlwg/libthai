/*
 * $Id: thcell.c,v 1.1 2001-08-08 12:39:19 thep Exp $
 * thcell.c - Thai string cell custering
 * Created: 2001-08-08 (split from thrend.c)
 */

#include <thai/thcell.h>
#include <thai/thctype.h>
#include <thai/wtt.h>
#include <thai/tis.h>

#define is_composible(c1,c2) (TACio_op(c1,c2)==CP)

const thchar_t *th_next_cell(const thchar_t *s, size_t len,
                             struct thcell *cell, size_t *nchars,
                             int is_decomp_am)
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
    *nchars = n;
    return s;
}

const thchar_t *th_make_cells(const thchar_t *s, size_t len,
                              struct thcell cells[], size_t *ncells,
                              int is_decomp_am)
{
    size_t left = *ncells;

    while (len > 0 && left > 0) {
        size_t nchars = 0;

        s = th_next_cell(s, len, cells, &nchars, is_decomp_am);
        len -= nchars;
        ++cells; --left;
    }
    *ncells -= left;
    return s;
}

