/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * brk-maximal.h - Thai word break with maximal matching scheme
 * Created: 2006-08-20
 * Author:  Theppitak Karoonboonyanan <thep@linux.thai.net>
 */

#ifndef __BRK_MAXIMAL_H
#define __BRK_MAXIMAL_H

#include <thai/thailib.h>

void
brk_maximal_on_unload ();

void
brk_maximal_init ();

void
brk_maximal_quit ();

int
brk_maximal_do (const thchar_t *s, int len, int pos[], size_t n);

#endif /* __BRK_MAXIMAL_H */

/*
vi:ts=4:ai:expandtab
*/
