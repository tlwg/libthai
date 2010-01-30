/*
 * $Id: cweight.h,v 1.4 2007-10-18 14:52:29 thep Exp $
 * cweight.h - Thai Character Weight table for TIS-620/2533 Collating
 * Created: 6 Nov 1998
 * Author:  Theppitak Karoonboonyanan <thep@linux.thai.net>
 */

/*
 * The ordering algorithm is in accordance
 * with the Thai Royal Institute Dictionary
 * 2525 B.E. Edition
 */

#ifndef CWEIGHT_H
#define CWEIGHT_H

#include <thai/thailib.h>

BEGIN_CDECL

#define TOT_LEVELS  4
#define IGNORE      0

extern thchar_t th_char_weight_(thchar_t c, int level);
extern thchar_t th_char_weight_delim_(int level);

END_CDECL

#endif  /* CWEIGHT_H */

