/*
 * $Id: thinp.c,v 1.1 2001-08-04 13:04:49 thep Exp $
 * thinp.c - Thai string input sequence filtering
 * Created: 2001-08-04
 */

#include <thai/thinp.h>
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

int th_validate(thchar_t *c1, thchar_t *c2, thstrict_t s)
{
    /* FIXME: implement it! */
    return 0;
}

