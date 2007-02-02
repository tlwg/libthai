/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * thbrk.c - Thai word break routine
 * Created: 2006-08-20
 * Author:  Theppitak Karoonboonyanan <thep@linux.thai.net>
 */

#include <string.h>
#include <stdlib.h>
#include <thai/tis.h>
#include <thai/thctype.h>
#include <thai/thbrk.h>
#include "brk-maximal.h"

static int          is_breakable (thchar_t c1, thchar_t c2);

int
th_brk_line (const thchar_t *in, thchar_t *out, size_t n, const char *delim)
{
    int        *brk_pos;
    int         n_brk_pos, i, j;
    int         delim_len;
    thchar_t   *p_out;

    n_brk_pos = strlen ((const char *) in);
    brk_pos = (int *) malloc (n_brk_pos * sizeof (int));

    n_brk_pos = th_brk (in, brk_pos, n_brk_pos);
    
    delim_len = strlen (delim);
    for (i = j = 0, p_out = out; n > 1 && i < n_brk_pos; i++) {
        while (n > 1 && j < brk_pos[i]) {
            *p_out++ = in [j++];
            --n;
        }
        if (n > delim_len + 1) {
            strcpy ((char *) p_out, delim);
            p_out += delim_len;
            n -= delim_len;
        }
    }
    while (n > 1 && in [j]) {
        *p_out++ = in [j++];
        --n;
    }
    *p_out = '\0';

    free (brk_pos);

    return p_out - out;
}

int
th_brk (const thchar_t *s, int pos[], size_t n)
{
    const thchar_t *chunk;
    int             cur_pos;

    chunk = s;
    cur_pos = 0;

    brk_maximal_init ();

    while (*chunk && cur_pos < n) {
        const thchar_t *str_end;
        int             n_brk, i;

        /* process non-Thai-text chunk */
        while (*chunk &&
               (!th_isthai (*chunk) ||
                th_isthpunct (*chunk) ||
                th_isthdigit (*chunk)))
        {
            thchar_t cur_char, next_char;

            /* peek next char and mark break pos if character type changes 
             * without space in between
             */
            cur_char = *chunk;
            next_char = *(chunk + 1);
            if (next_char && !isspace (next_char) &&
                (isspace (cur_char) ||
                 th_isthpunct (cur_char) ||
                 (!th_isthai (cur_char) && th_isthai (next_char)) ||
                 (th_isthdigit (cur_char) && !th_isthdigit (next_char)) ||
                 (isdigit (cur_char) && !isdigit (next_char))) &&
                is_breakable (cur_char, next_char))
            {
                pos [cur_pos++] = (chunk - s) + 1;
                if (cur_pos >= n)
                    break;
            }

            ++chunk;
        }
        if (!*chunk || cur_pos >= n)
            break;

        str_end = chunk;
        while (*str_end &&
               (th_isthai (*str_end)
                && !th_isthpunct (*str_end)
                && !th_isthdigit (*str_end)))
        {
            ++str_end;
        }

        /* do string break within Thai chunk */
        n_brk = brk_maximal_do (chunk, str_end - chunk,
                                pos + cur_pos, n - cur_pos, 1);
        for (i = 0; i < n_brk; i++)
            pos [cur_pos + i] += chunk - s;
        cur_pos += n_brk;
        chunk = str_end;

        /* if next character is Thai punct (e.g. Mai Yamok, Paiyan Noi),
         * don't break
         */
        if (*chunk && !is_breakable (*(chunk - 1), *chunk) &&
            cur_pos > 0 && pos [cur_pos - 1] == chunk -s)
        {
            --cur_pos;
        }
        /* otherwise, mark break pos at boundary if character type changes
         * without space in between and not currently marked
         */
        else if (cur_pos < n && *chunk && !isspace (*chunk) &&
                 cur_pos > 0 && pos [cur_pos - 1] != chunk - s)
        {
            pos [cur_pos++] = chunk - s;
        }
    }

    brk_maximal_quit ();

    return cur_pos;
}

static int
is_breakable (thchar_t c1, thchar_t c2)
{
    if (strchr ("\"`'~([{<.,;/@ï", c1))
        return 0;
    if (strchr ("\"`'~)]}>.,;/@Ïæúû", c2))
        return 0;
    if (PAIYANNOI == c1)
        return (LOLING != c2 && PHOPHAN != c2);
    if (PAIYANNOI == c2)
        return (LOLING != c1 && NONEN != c1);
    if (' ' == c1 && MAIYAMOK == c2)
        return 0;

    return 1;
}

/*
vi:ts=4:ai:expandtab
*/
