/*
 * $Id: thcell.h,v 1.4 2001-08-09 11:52:54 thep Exp $
 * thcell.h - Thai string cell custering
 * Created: 2001-08-08 (split from thrend.h)
 */

#ifndef THAI_THCELL_H
#define THAI_THCELL_H

#include <thai/thailib.h>

BEGIN_CDECL

/* Thai char cell representation */
struct thcell_t {
    thchar_t base;
    thchar_t hilo;
    thchar_t top;
};

/*
 * get first cell from the string bounded by s and len
 * Paramater:
 *   - is_decomp_am determines if SARA_AM is to be decomposed into
 *     NIKHAHIT and SARA_AA
 * On return: *cell = the cell
 * Returns: total chars consumed by the cell
 */
extern size_t th_next_cell(const thchar_t *s, size_t len,
                           struct thcell_t *cell, int is_decomp_am);

/*
 * get last cell from the string bounded by s and pos
 * Paramater:
 *   - is_decomp_am determines if SARA_AM is to be decomposed into
 *     NIKHAHIT and SARA_AA
 * On return: *cell = the cell
 * Returns: total chars consumed by the cell
 */
extern size_t th_prev_cell(const thchar_t *s, size_t pos,
                           struct thcell_t *cell, int is_decomp_am);
/*
 * tokenizes the string bounded by s and len into cells
 * No more than ncells will be stored in (*cells)[]
 * Paramater:
 *   - is_decomp_am determines if SARA_AM is to be decomposed into
 *     NIKHAHIT and SARA_AA
 * On return: cells[] = the cells; *ncells = total cells stored in (*cells)[]
 * Returns: total characters consumed
 */
extern size_t th_make_cells(const thchar_t *s, size_t len,
                            struct thcell_t cells[], size_t *ncells,
                            int is_decomp_am);

END_CDECL

#endif  /* THAI_THCELL_H */

