/*
 * thwrend.h - Thai wide-char string rendering
 * Created: 2001-05-17
 */

#ifndef THAI_THWREND_H
#define THAI_THWREND_H

#include <thai/thailib.h>
#include <thai/thrend.h>

BEGIN_CDECL

extern const thwchar_t *th_wcnext_cell(const thwchar_t *s, size_t len,
                                       struct thcell *cell, size_t *nchars);
extern const thwchar_t *th_wcmake_cells(const thwchar_t *s, size_t len,
                                        struct thcell cells[], size_t *ncells);

extern void th_wcrender_cell_tis(struct thcell cell,
                                 thglyph_t res[], size_t res_sz);
extern void th_wcrender_cell_win(struct thcell cell,
                                 thglyph_t res[], size_t res_sz);
extern void th_wcrender_cell_mac(struct thcell cell,
                                 thglyph_t res[], size_t res_sz);

extern int th_wcrender_text_tis(const thwchar_t *s,
                                thglyph_t res[], size_t res_sz);
extern int th_wcrender_text_win(const thwchar_t *s,
                                thglyph_t res[], size_t res_sz);
extern int th_wcrender_text_mac(const thwchar_t *s,
                                thglyph_t res[], size_t res_sz);

END_CDECL

#endif  /* THAI_THWREND_H */

