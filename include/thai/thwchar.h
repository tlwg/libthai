/*
 * $Id: thwchar.h,v 1.4 2001-07-27 10:43:07 thep Exp $
 * thwchar.h - wide char support for Thai
 * Created: 2001-05-17
 */

#ifndef THAI_THWCHAR_H
#define THAI_THWCHAR_H

#include <thai/thailib.h>
#include <wchar.h>

BEGIN_CDECL

#define THWCHAR_ERR  (~(thwchar_t)0)
#define THCHAR_ERR   (~(thchar_t)0)
typedef wchar_t thwchar_t;

extern thwchar_t th_tis2uni(thchar_t c);
extern thwchar_t th_winthai2uni(thchar_t c);
extern thwchar_t th_macthai2uni(thchar_t c);

extern thchar_t th_uni2tis(thwchar_t c);
extern thchar_t th_uni2winthai(thwchar_t c);
extern thchar_t th_uni2macthai(thwchar_t c);

END_CDECL

#endif  /* THAI_THWCHAR_H */

