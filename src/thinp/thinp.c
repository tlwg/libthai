/*
 * $Id: thinp.c,v 1.3 2001-08-06 14:08:05 thep Exp $
 * thinp.c - Thai string input sequence filtering
 * Created: 2001-08-04
 */

#include <thai/thinp.h>
#include <thai/tis.h>
#include <thai/wtt.h>


int th_isaccept(thchar_t c1, thchar_t c2, thstrict_t s)
{
    int op = TACio_op(c1, c2);
    switch (s) {
    case ISC_PASSTHROUGH:
        return 1;

    case ISC_BASICCHECK:
        return TACio_op(c1, c2) != RJ;

    case ISC_STRICT:
        {
            int op = TACio_op(c1, c2);
            return op != RJ && op != SR;
        }

    default:
        return 0;
    }
}

static const struct correction_t {
    char c1, c2, to[3];
} corrections[] = {
    { SARA_E, SARA_E, "á" },
    { RU, SARA_AA, "Äå" },
    { LU, SARA_AA, "Æå" },
    { NIKHAHIT, SARA_AA, "Ó" },
    { 0, 0, 0 }
};

static int correct(thchar_t c_1, thchar_t c, thchar_t conv[3])
{
    const struct correction_t *p;
    for (p = corrections; p->c1; ++p) {
        if (c_1 == (thchar_t)p->c1 && c == (thchar_t)p->c2) {
            strcpy((char *)conv, p->to);
            return 2;
        }
    }
    return 0;
}

int th_validate(thchar_t c_2, thchar_t c_1, thchar_t c,
                thchar_t conv[3], thstrict_t s)
{
    /* try predefined corrections */
    int ret = correct(c_1, c, conv);
    if (ret) return ret;

    if (th_isaccept(c_1, c, s)) return 1;  /* no conversion needed */

    /* try correction by conversion */
    if (th_isaccept(c_2, c, s)) {
        *conv++ = c;
        if (th_isaccept(c, c_1, s)) {
            *conv++ = c_1;
        }
        *conv = '\0';
        return 2;
    }

    return 0;
}

