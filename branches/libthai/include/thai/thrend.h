/*
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
};

extern const thchar_t *th_next_cell(const thchar_t *s, size_t len,
                                    struct thcell *cell, size_t *nchars);
extern const thchar_t *th_make_cells(const thchar_t *s, size_t len,
                                     struct thcell **cells, size_t *ncells);

extern void th_render_cell_tis(struct thcell cell,
                               thchar_t *res, size_t res_sz);
extern void th_render_cell_win(struct thcell cell,
                               thchar_t *res, size_t res_sz);
extern void th_render_cell_mac(struct thcell cell,
                               thchar_t *res, size_t res_sz);

extern int th_render_text_tis(const thchar_t *s, thchar_t *res, size_t res_sz);
extern int th_render_text_win(const thchar_t *s, thchar_t *res, size_t res_sz);
extern int th_render_text_mac(const thchar_t *s, thchar_t *res, size_t res_sz);

END_CDECL

#endif  /* THAI_THREND_H */

