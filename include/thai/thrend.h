/*
 * $Id: thrend.h,v 1.7 2001-08-08 17:57:22 thep Exp $
 * thrend.h - Thai string rendering
 * Created: 2001-05-17
 */

#ifndef THAI_THREND_H
#define THAI_THREND_H

#include <thai/thailib.h>
#include <thai/thcell.h>

BEGIN_CDECL

/* Glyph code type */
typedef unsigned int thglyph_t;

/*
 * render the given cell using corresponding glyph map
 * On return: First res_sz glyph codes stored in res, '\0' terminated
 * Returns: total number of glyphs written to res[]
 */
extern int th_render_cell_tis(struct thcell_t cell,
                              thglyph_t res[], size_t res_sz,
                              int is_decomp_am);
extern int th_render_cell_win(struct thcell_t cell,
                              thglyph_t res[], size_t res_sz,
                              int is_decomp_am);
extern int th_render_cell_mac(struct thcell_t cell,
                              thglyph_t res[], size_t res_sz,
                              int is_decomp_am);

/*
 * render the given text using corresponding glyph map
 * On return: First res_sz glyph codes stored in res, '\0' terminated
 * Returns: total number of glyphs written to res[]
 */
extern int th_render_text_tis(const thchar_t *s,
                              thglyph_t res[], size_t res_sz,
                              int is_decomp_am);
extern int th_render_text_win(const thchar_t *s,
                              thglyph_t res[], size_t res_sz,
                              int is_decomp_am);
extern int th_render_text_mac(const thchar_t *s,
                              thglyph_t res[], size_t res_sz,
                              int is_decomp_am);

END_CDECL

#endif  /* THAI_THREND_H */

