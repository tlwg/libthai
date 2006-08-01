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

/**
 * @brief  Render the given cell using TIS-620 glyph set
 *
 * @param  cell   : the cell to render
 * @param  res    : the buffer for storing output glyph string
 * @param  res_sz : the size of @a res buffer
 * @param  is_decomp_am : whether SARA AM is to be decomposed into 
 *                        NIKHANIT and SARA AA and to be in separate cells
 *
 * @return  total number of glyphs written to @a res[]
 *
 * Calculates glyphs from TIS-620 glyph set for the given @a cell,
 * and store the glyph string in @a res, terminated with '\\0'.
 * If resulting glyphs are longer than the provided buffer, only
 * the first @a res_sz glyphs are stored.
 */
extern int th_render_cell_tis(struct thcell_t cell,
                              thglyph_t res[], size_t res_sz,
                              int is_decomp_am);

/**
 * @brief  Render the given cell using Thai Windows glyph set
 *
 * @param  cell   : the cell to render
 * @param  res    : the buffer for storing output glyph string
 * @param  res_sz : the size of @a res buffer
 * @param  is_decomp_am : whether SARA AM is to be decomposed into 
 *                        NIKHANIT and SARA AA and to be in separate cells
 *
 * @return  total number of glyphs written to @a res[]
 *
 * Calculates glyphs from Thai Windows glyph set for the given @a cell,
 * and store the glyph string in @a res, terminated with '\\0'.
 * If resulting glyphs are longer than the provided buffer, only
 * the first @a res_sz glyphs are stored.
 */
extern int th_render_cell_win(struct thcell_t cell,
                              thglyph_t res[], size_t res_sz,
                              int is_decomp_am);

/**
 * @brief  Render the given cell using Mac Thai glyph set
 *
 * @param  cell   : the cell to render
 * @param  res    : the buffer for storing output glyph string
 * @param  res_sz : the size of @a res buffer
 * @param  is_decomp_am : whether SARA AM is to be decomposed into 
 *                        NIKHANIT and SARA AA and to be in separate cells
 *
 * @return  total number of glyphs written to @a res[]
 *
 * Calculates glyphs from Mac Thai glyph set for the given @a cell,
 * and store the glyph string in @a res, terminated with '\\0'.
 * If resulting glyphs are longer than the provided buffer, only
 * the first @a res_sz glyphs are stored.
 */
extern int th_render_cell_mac(struct thcell_t cell,
                              thglyph_t res[], size_t res_sz,
                              int is_decomp_am);


/**
 * @brief  Render the given text using TIS-620 glyph set
 *
 * @param  s      : the string to render
 * @param  res    : the buffer for storing output glyph string
 * @param  res_sz : the size of @a res buffer
 * @param  is_decomp_am : whether SARA AM is to be decomposed into 
 *                        NIKHANIT and SARA AA and to be in separate cells
 *
 * @return  total number of glyphs written to @a res[]
 *
 * Calculates glyphs from TIS-620 glyph set for the given string @a s,
 * and store the glyph string in @a res, terminated with '\\0'.
 * If resulting glyphs are longer than the provided buffer, only
 * the first @a res_sz glyphs are stored.
 */
extern int th_render_text_tis(const thchar_t *s,
                              thglyph_t res[], size_t res_sz,
                              int is_decomp_am);

/**
 * @brief  Render the given text using Thai Windows glyph set
 *
 * @param  s      : the string to render
 * @param  res    : the buffer for storing output glyph string
 * @param  res_sz : the size of @a res buffer
 * @param  is_decomp_am : whether SARA AM is to be decomposed into 
 *                        NIKHANIT and SARA AA and to be in separate cells
 *
 * @return  total number of glyphs written to @a res[]
 *
 * Calculates glyphs from Thai Windows glyph set for the given string @a s,
 * and store the glyph string in @a res, terminated with '\\0'.
 * If resulting glyphs are longer than the provided buffer, only
 * the first @a res_sz glyphs are stored.
 */
extern int th_render_text_win(const thchar_t *s,
                              thglyph_t res[], size_t res_sz,
                              int is_decomp_am);

/**
 * @brief  Render the given text using Mac Thai glyph set
 *
 * @param  s      : the string to render
 * @param  res    : the buffer for storing output glyph string
 * @param  res_sz : the size of @a res buffer
 * @param  is_decomp_am : whether SARA AM is to be decomposed into 
 *                        NIKHANIT and SARA AA and to be in separate cells
 *
 * @return  total number of glyphs written to @a res[]
 *
 * Calculates glyphs from Mac Thai glyph set for the given string @a s,
 * and store the glyph string in @a res, terminated with '\\0'.
 * If resulting glyphs are longer than the provided buffer, only
 * the first @a res_sz glyphs are stored.
 */
extern int th_render_text_mac(const thchar_t *s,
                              thglyph_t res[], size_t res_sz,
                              int is_decomp_am);

END_CDECL

#endif  /* THAI_THREND_H */

