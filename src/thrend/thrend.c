/*
 * $Id: thrend.c,v 1.1 2001-08-06 14:08:05 thep Exp $
 * thrend.h - Thai string rendering
 * Created: 2001-08-06
 */

#include <thai/thrend.h>
#include <thai/thctype.h>
#include <thai/wtt.h>

#define is_composible(c1,c2) (TACio_op(c1,c2)==CP)

const thchar_t *th_next_cell(const thchar_t *s, size_t len,
                             struct thcell *cell, size_t *nchars)
{
    size_t n = 0;
    cell->base = cell->hilo = cell->top = 0;
    if (len > 0) {
        do {
            switch (th_chlevel(*s)) {
                case 0: cell->base = *s++; break;
                case -1:
                case 1: cell->hilo = *s++; break;
                case 2: cell->top  = *s++; break;
            }
            ++n;
        } while (--len > 0 && is_composible(s[-1], s[0]));
    }
    *nchars = n;
    return s;
}

const thchar_t *th_make_cells(const thchar_t *s, size_t len,
                              struct thcell cells[], size_t *ncells)
{
    size_t left = *ncells;

    while (len > 0 && left > 0) {
        size_t nchars = 0;

        s = th_next_cell(s, len, cells, &nchars);
        len -= nchars;
        ++cells; --left;
    }
    *ncells -= left;
    return s;
}


void th_render_cell_tis(struct thcell cell,
                        thglyph_t res[], size_t res_sz)
{
    /* FIXME: do it */
}

void th_render_cell_win(struct thcell cell,
                        thglyph_t res[], size_t res_sz)
{
    /* FIXME: do it */
}

void th_render_cell_mac(struct thcell cell,
                        thglyph_t res[], size_t res_sz)
{
    /* FIXME: do it */
}


int th_render_text_tis(const thchar_t *s,
                       thglyph_t res[], size_t res_sz)
{
    /* FIXME: do it */
    return 0;
}

int th_render_text_win(const thchar_t *s,
                       thglyph_t res[], size_t res_sz)
{
    /* FIXME: do it */
    return 0;
}

int th_render_text_mac(const thchar_t *s,
                       thglyph_t res[], size_t res_sz)
{
    /* FIXME: do it */
    return 0;
}

