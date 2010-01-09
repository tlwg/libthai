/*
 * $Id: thcell.h,v 1.7 2006-07-31 11:07:46 thep Exp $
 * thcell.h - Thai string cell custering
 * Created: 2001-08-08 (split from thrend.h)
 */

#ifndef THAI_THCELL_H
#define THAI_THCELL_H

#include <thai/thailib.h>

BEGIN_CDECL

/**
 * @file   thcell.h
 * @brief  Thai string cell custering
 */

/**
 * @brief  Thai char cell representation
 */
struct thcell_t {
    thchar_t base;      /**< base character */
    thchar_t hilo;      /**< upper/lower vowel/diacritic */
    thchar_t top;       /**< top-level mark */
};

extern void th_init_cell(struct thcell_t *cell);

extern size_t th_next_cell(const thchar_t *s, size_t len,
                           struct thcell_t *cell, int is_decomp_am);

extern size_t th_prev_cell(const thchar_t *s, size_t pos,
                           struct thcell_t *cell, int is_decomp_am);
extern size_t th_make_cells(const thchar_t *s, size_t len,
                            struct thcell_t cells[], size_t *ncells,
                            int is_decomp_am);

END_CDECL

#endif  /* THAI_THCELL_H */

