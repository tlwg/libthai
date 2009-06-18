/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * brk-ctype.h - Character classification for line break purpose
 * Created: 2007-06-10
 * Author:  Theppitak Karoonboonyanan <thep@linux.thai.net>
 */

#ifndef __BRK_CTYPE_H
#define __BRK_CTYPE_H

#include <thai/thailib.h>

typedef enum {
    BRK_CLASS_THAI,     /* Thai Character */
    BRK_CLASS_ALPHA,    /* Non-Thai Alphabet */
    BRK_CLASS_NUM,      /* Number */
    BRK_CLASS_NBB,      /* No Break Before */
    BRK_CLASS_NBA,      /* No Break After */
    BRK_CLASS_NB,       /* No Break */
    BRK_CLASS_MB,       /* Mandatory Break */
    BRK_CLASS_SPACE,    /* White Space */
    BRK_CLASS_QUOTE,    /* Ambiguous Quotation */
    BRK_CLASS_HYPHEN,   /* Minus-Hyphen */
    BRK_CLASS_NUM_NBB,  /* No Break Before in Numerical Mode */
    BRK_CLASS_NUM_CUR,  /* Currency, No Break Before/After in Numerical Mode */
    BRK_CLASS_NUM_NB,   /* No Break in Numerical Mode, NBB Otherwise */
    BRK_CLASS_TERM,     /* Terminator (Non-starter) */
    BRK_CLASS_TOTAL     /* Total classes */
} brk_class_t;

typedef enum {
    BRK_OP_PROHIBITED,  /* no break, even with space in between */
    BRK_OP_ALLOWED,     /* direct break, break immediately */
    BRK_OP_INDIRECT,    /* indirect break, break if with space in between */
} brk_op_t;

brk_class_t
brk_class (thchar_t c);

brk_op_t
brk_op (brk_class_t prev, brk_class_t next);

#endif /* __BRK_CTYPE_H */

/*
vi:ts=4:ai:expandtab
*/
