/*
 * $Id: thwinp.h,v 1.3 2001-05-18 04:51:02 thep Exp $
 * thwinp.h - Thai wide-char string input sequence filtering
 * Created: 2001-05-17
 */

#ifndef THAI_THWCINP_H
#define THAI_THWCINP_H

#include <thai/thailib.h>
#include <thai/thinp.h>

BEGIN_CDECL

extern int th_wciscompose(thwchar_t c1, thwchar_t c2, thstrict_t s);
extern int th_wcvalidate(thwchar_t *c1, thwchar_t *c2, thstrict_t s);

END_CDECL

#endif  /* THAI_THWCINP_H */

