/*
 * thwchar.h - wide char support for Thai
 * Created: 2001-05-17
 */

#ifndef THAI_THWCHAR_H
#define THAI_THWCHAR_H

#include <thai/thailib.h>
#include <wchar.h>

BEGIN_CDECL

#define THWCHAR_ERR  (~(thwchar_t)0)
typedef wchar_t thwchar_t;

extern thwchar_t th_tis2uni(thchar_t c);
extern thwchar_t th_winthai2uni(thchar_t c);
extern thwchar_t th_macthai2uni(thchar_t c);

extern thwchar_t th_uni2tis(thchar_t c);
extern thwchar_t th_uni2winthai(thchar_t c);
extern thwchar_t th_uni2macthai(thchar_t c);

END_CDECL

#endif  /* THAI_THWCHAR_H */

