/*
 * $Id: thinp.c,v 1.5 2001-08-08 17:52:10 thep Exp $
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
            return 1;
        }
    }
    return 0;
}

int th_validate(struct thcell context, thchar_t c, struct thinpconv_t *conv)
{
    thchar_t prev_c = context.top ?
                          context.top :
                          (context.hilo ? context.hilo : context.base);
    int ret;

    if (context.hilo == SARA_AM) prev_c = SARA_AM;

    /* try predefined corrections */
    ret = correct(prev_c, c, conv->conv);
    if (ret) {
        conv->offset = -1;
        return 1;
    }

    /* normal cases */
    if (th_isaccept(prev_c, c, ISC_STRICT)) {
        conv->conv[0] = c; conv->conv[1] = 0;
        conv->offset = 0;
        return 1;
    }

    /* try correction by conversion */
    switch (th_chlevel(c)) {
    case -1:
    case 1:
        if (th_isaccept(context.base, c, ISC_STRICT)) {
            /* replace from hilo on; use new hilo + old top if OK */
            int i = 0;
            conv->offset = 0;
            conv->conv[i++] = c;
            if (context.hilo) --conv->offset;
            if (context.top) {
                --conv->offset;
                if (th_isaccept(c, context.top, ISC_STRICT))
                    conv->conv[i++] = context.top;
            }
            conv->conv[i] = 0;
            return 1;
        }
        break;

    case 2:
        if (context.hilo && th_isaccept(context.hilo, c, ISC_STRICT)) {
            /* hilo OK, replace top only */
            conv->offset = 0;
            conv->conv[0] = c; conv->conv[1] = 0;
            if (context.top) --conv->offset;
            return 1;
        }
        if (th_isaccept(context.base, c, ISC_STRICT) &&
            (context.hilo != SARA_AM || th_isaccept(c, SARA_AM, ISC_STRICT)))
        {
            /* replace from hilo on, using new top */
            int i = 0;
            conv->offset = 0;
            conv->conv[i++] = c;
            if (context.hilo) {
                --conv->offset;
                if (context.hilo == SARA_AM)
                    conv->conv[i++] = SARA_AM;
            }
            if (context.top) --conv->offset;
            conv->conv[i] = 0;
            return 1;
        }
    }

    return 0;
}

