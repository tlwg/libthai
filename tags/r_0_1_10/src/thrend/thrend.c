/*
 * $Id: thrend.c,v 1.14 2007-10-18 14:52:29 thep Exp $
 * thrend.h - Thai string rendering
 * Created: 2001-08-06
 * Author:  Theppitak Karoonboonyanan <thep@linux.thai.net>
 */

#include <string.h>
#include <thai/thrend.h>
#include <thai/thctype.h>
#include <thai/tis.h>


typedef struct {
    thglyph_t ShiftDown_TONE_AD[8];
    thglyph_t ShiftDownLeft_TONE_AD[8];
    thglyph_t ShiftLeft_TONE_AD[8];
    thglyph_t ShiftLeft_AV[7];
    thglyph_t ShiftDown_BV_BD[3];
    thglyph_t TailCutCons[4];
} ThaiShapeTable;

#define shiftdown_tone_ad(c,tbl)     ((tbl)->ShiftDown_TONE_AD[(c)-MAITAIKHU])
#define shiftdownleft_tone_ad(c,tbl) ((tbl)->ShiftDownLeft_TONE_AD[(c)-MAITAIKHU])
#define shiftleft_tone_ad(c,tbl)     ((tbl)->ShiftLeft_TONE_AD[(c)-MAITAIKHU])
#define shiftleft_av(c,tbl)          ((tbl)->ShiftLeft_AV[(c)-MAIHUNAKAT])
#define shiftdown_bv_bd(c,tbl)       ((tbl)->ShiftDown_BV_BD[(c)-SARA_U])
#define tailcutcons(c,tbl)           ((tbl)->TailCutCons[(c)-YOYING])

/*
 * No adjusted vowel/tonemark glyphs (tis620-0)
 */
static const ThaiShapeTable tis620_0_shape_table_ = {
    { 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xEE },
    { 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xEE },
    { 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xEE },
    { 0xD1, 0x00, 0x00, 0xD4, 0xD5, 0xD6, 0xD7 },
    { 0xD8, 0xD9, 0xDA },
    { 0xAD, 0x00, 0x00, 0xB0 }
};

/*
 * Macintosh
 */
static const ThaiShapeTable Mac_shape_table_ = {
    { 0xE7, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0xED, 0xEE },
    { 0x93, 0x83, 0x84, 0x85, 0x86, 0x87, 0x8F, 0xEE },
    { 0x93, 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x8F, 0xEE },
    { 0x92, 0x00, 0x00, 0x94, 0x95, 0x96, 0x97 },
    { 0xFC, 0xFD, 0xFE },
    { 0x90, 0x00, 0x00, 0x80 }
};

/*
 * Microsoft Window
 */
static const ThaiShapeTable Win_shape_table_ = {
    { 0xE7, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0xED, 0xEE },
    { 0x9A, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x99, 0xEE },
    { 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F, 0x99, 0xEE },
    { 0x98, 0x00, 0x00, 0x81, 0x82, 0x83, 0x84 },
    { 0xFC, 0xFD, 0xFE },
    { 0x90, 0x00, 0x00, 0x80 }
};

static
int th_render_cell_(struct thcell_t cell,
                    thglyph_t res[], size_t res_sz,
                    int is_decomp_am,
                    const ThaiShapeTable *tbl)
{
    size_t left = res_sz;

    /* put base character */
    if (left > 0) {
        thchar_t c = cell.base;
        if (th_isundersplitcons(c) && th_chlevel(cell.hilo) < 0) {
            c = tailcutcons(c, tbl);
        }
        *res++ = c ? c : TH_BLANK_BASE_GLYPH; --left;
    }
    /* put hilo character */
    if (left > 0 && cell.hilo) {
        thchar_t c = 0;
        if (cell.hilo != SARA_AM) { c = cell.hilo; }
        else if (is_decomp_am) { c = NIKHAHIT; }
        if (c) {
            if (th_isovershootcons(cell.base) && th_chlevel(c) > 0) {
		c = th_isupvowel(c) ? shiftleft_av(c, tbl)
		                    : shiftleft_tone_ad(c, tbl);
            } else if (th_isundershootcons(cell.base) && th_chlevel(c) < 0) {
                c = shiftdown_bv_bd(c, tbl);
            }
            *res++ = c; --left;
        }
    }
    /* put top character */
    if (left > 0 && cell.top) {
        thchar_t c = cell.top;
        if (th_isupvowel(cell.hilo) || (is_decomp_am && cell.hilo == SARA_AM)) {
            c = th_isovershootcons(cell.base) ? shiftleft_tone_ad(c, tbl) : c;
        } else {
            c = th_isovershootcons(cell.base) ? shiftdownleft_tone_ad(c, tbl)
                                              : shiftdown_tone_ad(c, tbl);
        }
        *res++ = c; --left;
    }
    /* put extra character */
    if (left > 0 && cell.hilo == SARA_AM) {
        *res++ = (is_decomp_am) ? SARA_AA : SARA_AM; --left;
    }

    /* null terminate */
    if (left > 0) { *res = 0; }

    return res_sz - left;
}

int th_render_cell_tis(struct thcell_t cell,
                       thglyph_t res[], size_t res_sz,
                       int is_decomp_am)
{
    size_t left = res_sz;

    if (left > 0) {
      *res++ = cell.base ? cell.base : TH_BLANK_BASE_GLYPH; --left;
    }
    if (left > 0 && cell.hilo) {
        if (cell.hilo != SARA_AM) { *res++ = cell.hilo; --left; }
	else if (is_decomp_am) { *res++ = NIKHAHIT; --left; }
    }
    if (left > 0 && cell.top) { *res++ = cell.top; --left; }
    if (left > 0 && cell.hilo == SARA_AM) {
        *res++ = (is_decomp_am) ? SARA_AA : SARA_AM; --left;
    }
    if (left > 0) { *res = 0; }

    return res_sz - left;
}

int th_render_cell_win(struct thcell_t cell,
                       thglyph_t res[], size_t res_sz,
                       int is_decomp_am)
{
    return th_render_cell_(cell, res, res_sz, is_decomp_am, &Win_shape_table_);
}

int th_render_cell_mac(struct thcell_t cell,
                       thglyph_t res[], size_t res_sz,
                       int is_decomp_am)
{
    return th_render_cell_(cell, res, res_sz, is_decomp_am, &Mac_shape_table_);
}

static
int th_render_text(const thchar_t *s,
                   thglyph_t res[], size_t res_sz,
                   int is_decomp_am,
                   int (*cell_rend_fn)(struct thcell_t, thglyph_t[], size_t, int))
{
    size_t left = res_sz;
    int len = strlen((const char*)s);

    while (left > 0 && len > 0) {
        struct thcell_t cell;
        size_t nchars = 0;
        int    nglyphs = 0;

        nchars = th_next_cell(s, len, &cell, is_decomp_am);
        s += nchars; len -= nchars;
        nglyphs = (*cell_rend_fn)(cell, res, left, is_decomp_am);
        res += nglyphs; left -= nglyphs;
    }

    return res_sz - left;
}

int th_render_text_tis(const thchar_t *s,
                       thglyph_t res[], size_t res_sz,
                       int is_decomp_am)
{
    return th_render_text(s, res, res_sz, is_decomp_am, th_render_cell_tis);
}

int th_render_text_win(const thchar_t *s,
                       thglyph_t res[], size_t res_sz,
                       int is_decomp_am)
{
    return th_render_text(s, res, res_sz, is_decomp_am, th_render_cell_win);
}

int th_render_text_mac(const thchar_t *s,
                       thglyph_t res[], size_t res_sz,
                       int is_decomp_am)
{
    return th_render_text(s, res, res_sz, is_decomp_am, th_render_cell_mac);
}

