/*
 * thinp.h - Thai string input sequence filtering
 * Created: 2001-05-17
 */

#ifndef THAI_THINP_H
#define THAI_THINP_H

#include <thai/thailib.h>

BEGIN_CDECL

typedef enum {
    ISC_PASSTHROUGH = 0,
    ISC_BASICCHECK  = 1,
    ISC_STRICT      = 2
} strict_t;

extern int th_iscompose(thchar_t c1, thchar_t c2, strict_t s);
extern int th_validate(thchar_t *c1, thchar_t *c2, strict_t s);

END_CDECL

#endif  /* THAI_THINP_H */

