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

/**
 * @brief  Initialize a Thai cell
 *
 * @param  cell : pointer to the cell to initialize
 *
 * Initializes values in the Thai cell struct.
 */
extern void th_init_cell(struct thcell_t *cell);

/**
 * @brief  Get first cell from string
 *
 * @param  s    : the string
 * @param  len  : the length of string
 * @param  cell : the output buffer
 * @param  is_decomp_am : whether SARA AM is to be decomposed into 
 *                        NIKHANIT and SARA AA and to be in separate cells
 *
 * @returns  total chars consumed by the cell
 *
 * Gets first cell from the string bounded by @a s and @a len, and, if @a cell
 * is not null, stores the cell data in it.
 */
extern size_t th_next_cell(const thchar_t *s, size_t len,
                           struct thcell_t *cell, int is_decomp_am);

/**
 * @brief  Get previous cell from string
 *
 * @param  s    : the string
 * @param  pos  : the position in string to get cell previous to
 * @param  cell : the output buffer
 * @param  is_decomp_am : whether SARA AM is to be decomposed into 
 *                        NIKHANIT and SARA AA and to be in separate cells
 *
 * @returns  total chars consumed by the cell
 *
 * Gets last cell from the string bounded by @a s and @a pos, and if @a cell
 * is not null, stores the cell data in it.
 */
extern size_t th_prev_cell(const thchar_t *s, size_t pos,
                           struct thcell_t *cell, int is_decomp_am);
/**
 * @brief  Tokenize string into cells
 *
 * @param  s      : the string
 * @param  len    : the length of string
 * @param  cells  : the array of output cells buffer
 * @param  ncells : the address of integer storing the number of cells 
 *                  provided by the buffer, and to keep the number of resulting 
 *                  cells on return
 * @param  is_decomp_am : whether SARA AM is to be decomposed into 
 *                        NIKHANIT and SARA AA and to be in separate cells
 *
 * @returns  total characters consumed
 *
 * Tokenizes the string bounded by @a s and @a len into cells, and stores
 * at most @a *ncells resulting cells in the @a cells buffer. On return,
 * @a *ncells is also set to the total cells stored in @a cells[].
 */
extern size_t th_make_cells(const thchar_t *s, size_t len,
                            struct thcell_t cells[], size_t *ncells,
                            int is_decomp_am);

END_CDECL

#endif  /* THAI_THCELL_H */

