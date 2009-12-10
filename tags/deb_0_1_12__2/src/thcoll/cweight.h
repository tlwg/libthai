/*
   Copyright (C) 1998 National Electronics and Computer Technology Center

   This file is part of ThColl, a Thai string collation library.

   ThColl is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of
   the License, or (at your option) any later version.

   ThColl is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with ThColl; see the file COPYING.  If not, write to the
   Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA  02111-1307, USA.

   Any licensing or usage questions should be directed to Theppitak
   Karoonboonyanan <thep@linux.thai.net>.

*/


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

