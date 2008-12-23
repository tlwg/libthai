/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * libthai.c - main source for libthai
 * Created: 2008-12-23
 * Author:  Theppitak Karoonboonyanan <thep@linux.thai.net>
 */

#include "thbrk/thbrk-private.h"

__attribute__ ((destructor)) void
_libthai_on_unload ()
{
    thbrk_on_unload ();
}

/*
vi:ts=4:ai:expandtab
*/
