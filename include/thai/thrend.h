/*
 * $Id: thrend.h,v 1.3 2001-08-06 14:08:05 thep Exp $
 * thrend.h - Thai string rendering
 * Created: 2001-05-17
 */

#ifndef THAI_THREND_H
#define THAI_THREND_H

#include <thai/thailib.h>

BEGIN_CDECL

/* Thai char cell representation */
struct thcell {
    thchar_t base;
    thchar_t hilo;
    thchar_t top;
};

/* Glyph code type */
typedef unsigned int thglyph_t;

/*
 * get first cell from the string bounded by s and len
 * On return: *cell = the cell; *nchars = total chars consumed by the cell
 * Returns: pointer to the position next to the cell
 */
extern const thchar_t *th_next_cell(const thchar_t *s, size_t len,
                                    struct thcell *cell, size_t *nchars);
/*
 * tokenizes the string bounded by s and len into cells
 * No more than *ncells will be stored in (*cells)[]
 * On return: cells[] = the cells;
 *            *ncells = total cells stored in (*cells)[]
 * Returns: pointer to the position next to the last cell stored in (*cells)[]
 */
extern const thchar_t *th_make_cells(const thchar_t *s, size_t len,
                                     struct thcell cells[], size_t *ncells);

/*
 * render the given cell using corresponding glyph map
 * On return: First res_sz glyph codes stored in res, '\0' terminated
 */
extern void th_render_cell_tis(struct thcell cell,
                               thglyph_t res[], size_t res_sz);
extern void th_render_cell_win(struct thcell cell,
                               thglyph_t res[], size_t res_sz);
extern void th_render_cell_mac(struct thcell cell,
                               thglyph_t res[], size_t res_sz);

/*
 * render the given text using corresponding glyph map
 * On return: First res_sz glyph codes stored in res, '\0' terminated
 */
extern int th_render_text_tis(const thchar_t *s,
                              thglyph_t res[], size_t res_sz);
extern int th_render_text_win(const thchar_t *s,
                              thglyph_t res[], size_t res_sz);
extern int th_render_text_mac(const thchar_t *s,
                              thglyph_t res[], size_t res_sz);

END_CDECL

#endif  /* THAI_THREND_H */

