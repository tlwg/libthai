/*
 * $Id: thrend.h,v 1.11 2006-08-01 11:46:57 thep Exp $
 * thrend.h - Thai string rendering
 * Created: 2001-05-17
 */

#ifndef THAI_THREND_H
#define THAI_THREND_H

#include <thai/thailib.h>
#include <thai/thcell.h>

BEGIN_CDECL

/**
 * @file   thrend.h
 * @brief  Thai string rendering
 */

/**
 * @brief  Glyph code type
 */
typedef unsigned char thglyph_t;

/**
 * @brief  Blank base glyph, for floating upper/lower vowel
 */
#define TH_BLANK_BASE_GLYPH  0xdd

extern int th_render_cell_tis(struct thcell_t cell,
                              thglyph_t res[], size_t res_sz,
                              int is_decomp_am);

extern int th_render_cell_win(struct thcell_t cell,
                              thglyph_t res[], size_t res_sz,
                              int is_decomp_am);

extern int th_render_cell_mac(struct thcell_t cell,
                              thglyph_t res[], size_t res_sz,
                              int is_decomp_am);


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

