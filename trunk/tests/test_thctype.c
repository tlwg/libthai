/*
 * test_thctype.c : Test bed for <thai/thctype.h> functions
 * Created: 2001-07-31
 * Author:  Theppitak Karoonboonyanan
 */

#include <thai/thctype.h>
#include <stdio.h>

struct char_range {
    thchar_t begin;
    thchar_t end;
};

const struct char_range tis_ranges[] = {
    { 0x00, 0x7f }, { 0xa1, 0xda }, { 0xdf, 0xfb }, { 0, 0 }
};

const struct char_range thai_ranges[] = {
    { 0xa1, 0xda }, { 0xdf, 0xfb }, { 0, 0 }
};

const struct char_range eng_ranges[] = {
    { 0x00, 0x7f }, { 0, 0 }
};

const struct char_range thcons_ranges[] = {
    { 0xa1, 0xc3 }, { 0xc5, 0xc5 }, { 0xc7, 0xce }, { 0, 0 }
};

const struct char_range tlcons_ranges[] = {
    { 0xa1, 0xac }, { 0xb1, 0xba }, { 0xbc, 0xbc }, { 0xbe, 0xbe },
    { 0xc0, 0xc3 }, { 0xc5, 0xc5 }, { 0xc7, 0xcb }, { 0xcd, 0xce },
    { 0, 0 }
};

const struct char_range oscons_ranges[] = {
    { 0xbb, 0xbb }, { 0xbd, 0xbd }, { 0xbf, 0xbf }, { 0xcc, 0xcc },
    { 0, 0 }
};

const struct char_range uscons_ranges[] = {
    { 0xae, 0xaf }, { 0, 0 }
};

const struct char_range spcons_ranges[] = {
    { 0xad, 0xad }, { 0xb0, 0xb0 }, { 0, 0 }
};

const struct char_range thvowel_ranges[] = {
    { 0xc4, 0xc4 }, { 0xc6, 0xc6 }, { 0xd0, 0xd9 }, { 0xe0, 0xe5 }, { 0, 0 }
};

const struct char_range ldvowel_ranges[] = {
    { 0xe0, 0xe4 }, { 0, 0 }
};

const struct char_range flvowel_ranges[] = {
    { 0xc4, 0xc4 }, { 0xc6, 0xc6 }, { 0xd0, 0xd0 }, { 0xd2, 0xd3 },
    { 0xe5, 0xe5 }, { 0, 0 }
};

const struct char_range upvowel_ranges[] = {
    { 0xd1, 0xd1 }, { 0xd4, 0xd7 }, { 0, 0 }
};

const struct char_range blvowel_ranges[] = {
    { 0xd8, 0xd9 }, { 0, 0 }
};

const struct char_range thtone_ranges[] = {
    { 0xe8, 0xeb }, { 0, 0 }
};

const struct char_range thdiac_ranges[] = {
    { 0xda, 0xda }, { 0xe7, 0xe7 }, { 0xec, 0xee }, { 0, 0 }
};

const struct char_range thdigit_ranges[] = {
    { 0x30, 0x39 }, { 0xf0, 0xf9 }, { 0, 0 }
};

const struct char_range thpunct_ranges[] = {
    { 0x21, 0x2f }, { 0x3a, 0x40 }, { 0x5b, 0x60 }, { 0x7b, 0x7e },
    { 0xcf, 0xcf }, { 0xdf, 0xdf }, { 0xe6, 0xe6 }, { 0xef, 0xef },
    { 0xfa, 0xfb }, { 0, 0 }
};

int test_bool_funcs(const struct char_range ranges[], int (*fn)(thchar_t))
{
    const struct char_range *pRange = ranges;
    int      err_code = 0;
    thchar_t c = 0;

    while (pRange->end) {
        /* out-of-range check */
        while (c < pRange->begin) {
            if ((*fn)(c)) {
                fprintf(stderr, "+%02x ", c);
                err_code = 1;
            }
            ++c;
        }
        /* in-range check */
        while (c <= pRange->end) {
            if (!(*fn)(c)) {
                fprintf(stderr, "-%02x ", c);
                err_code = 1;
            }
            ++c;
        }
        ++pRange;
    }
    /* out-of-range check */
    while (c < 0xff) {
        if ((*fn)(c)) {
            fprintf(stderr, "+%02x ", c);
            err_code = 1;
        }
        ++c;
    }
    /* 0xff itself */
    if ((*fn)(c)) {
        fprintf(stderr, "+%02x ", c);
        err_code = 1;
    }
    fprintf(stderr, "\n");

    return err_code;
}

int main()
{
    int err_code = 0;

    err_code += test_bool_funcs(tis_ranges, th_istis);
    err_code += test_bool_funcs(thai_ranges, th_isthai);
    err_code += test_bool_funcs(eng_ranges, th_iseng);
    err_code += test_bool_funcs(thcons_ranges, th_isthcons);
    err_code += test_bool_funcs(thvowel_ranges, th_isthvowel);
    err_code += test_bool_funcs(thtone_ranges, th_isthtone);
    err_code += test_bool_funcs(thdiac_ranges, th_isthdiac);
    err_code += test_bool_funcs(thdigit_ranges, th_isthdigit);
    err_code += test_bool_funcs(thpunct_ranges, th_isthpunct);
    err_code += test_bool_funcs(tlcons_ranges, th_istaillesscons);
    err_code += test_bool_funcs(oscons_ranges, th_isovershootcons);
    err_code += test_bool_funcs(uscons_ranges, th_isundershootcons);
    err_code += test_bool_funcs(spcons_ranges, th_isundersplitcons);
    err_code += test_bool_funcs(ldvowel_ranges, th_isldvowel);
    err_code += test_bool_funcs(flvowel_ranges, th_isflvowel);
    err_code += test_bool_funcs(upvowel_ranges, th_isupvowel);
    err_code += test_bool_funcs(blvowel_ranges, th_isblvowel);

    return err_code;
}

