/*
 * $Id: thinp.h,v 1.9 2006-07-31 11:07:46 thep Exp $
 * thinp.h - Thai string input sequence filtering
 * Created: 2001-05-17
 */

#ifndef THAI_THINP_H
#define THAI_THINP_H

#include <thai/thailib.h>
#include <thai/thcell.h>

BEGIN_CDECL

/**
 * @file   thinp.h
 * @brief  Thai string input sequence filtering
 */

/**
 * @brief  Strictness of input sequence checking, according to WTT 2.0
 */
typedef enum {
    ISC_PASSTHROUGH = 0,        /**< No check */
    ISC_BASICCHECK  = 1,        /**< Basic check */
    ISC_STRICT      = 2         /**< Strict check */
} thstrict_t;

extern int th_isaccept(thchar_t c1, thchar_t c2, thstrict_t s);

/**
 * @brief  Input sequence correction info
 */
struct thinpconv_t {
    thchar_t conv[4];  /**< (null-terminated) string to put into input buffer */
    int      offset;   /**< offset (<=0) from cur pos where the conv begin */
};

extern int th_validate(struct thcell_t context, thchar_t c,
                       struct thinpconv_t *conv);

END_CDECL

#endif  /* THAI_THINP_H */

