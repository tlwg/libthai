/*
 * $Id: thwchar.c,v 1.7 2001-09-14 14:05:09 thep Exp $
 * thwchar.c - wide char support for Thai
 * Created: 2001-07-27
 * Author:  Pattara Kiatisevi <ott@linux.thai.net>,
 *          Theppitak Karoonboonyanan <thep@links.nectec.or.th>
 */

#include <thai/thwchar.h>

#define WC_ERR THWCHAR_ERR
#define TH_ERR THCHAR_ERR

static thwchar_t tis620_0_uni_map_[128] = {
    WC_ERR, WC_ERR, WC_ERR, WC_ERR, WC_ERR, WC_ERR, WC_ERR, WC_ERR, 
    WC_ERR, WC_ERR, WC_ERR, WC_ERR, WC_ERR, WC_ERR, WC_ERR, WC_ERR, 
    WC_ERR, WC_ERR, WC_ERR, WC_ERR, WC_ERR, WC_ERR, WC_ERR, WC_ERR, 
    WC_ERR, WC_ERR, WC_ERR, WC_ERR, WC_ERR, WC_ERR, WC_ERR, WC_ERR, 
    WC_ERR, 0x0e01, 0x0e02, 0x0e03, 0x0e04, 0x0e05, 0x0e06, 0x0e07,
    0x0e08, 0x0e09, 0x0e0a, 0x0e0b, 0x0e0c, 0x0e0d, 0x0e0e, 0x0e0f,
    0x0e10, 0x0e11, 0x0e12, 0x0e13, 0x0e14, 0x0e15, 0x0e16, 0x0e17,
    0x0e18, 0x0e19, 0x0e1a, 0x0e1b, 0x0e1c, 0x0e1d, 0x0e1e, 0x0e1f,
    0x0e20, 0x0e21, 0x0e22, 0x0e23, 0x0e24, 0x0e25, 0x0e26, 0x0e27,
    0x0e28, 0x0e29, 0x0e2a, 0x0e2b, 0x0e2c, 0x0e2d, 0x0e2e, 0x0e2f,
    0x0e30, 0x0e31, 0x0e32, 0x0e33, 0x0e34, 0x0e35, 0x0e36, 0x0e37,
    0x0e38, 0x0e39, 0x0e3a, WC_ERR, WC_ERR, WC_ERR, WC_ERR, 0x0e3f,
    0x0e40, 0x0e41, 0x0e42, 0x0e43, 0x0e44, 0x0e45, 0x0e46, 0x0e47,
    0x0e48, 0x0e49, 0x0e4a, 0x0e4b, 0x0e4c, 0x0e4d, 0x0e4e, 0x0e4f,
    0x0e50, 0x0e51, 0x0e52, 0x0e53, 0x0e54, 0x0e55, 0x0e56, 0x0e57,
    0x0e58, 0x0e59, 0x0e5a, 0x0e5b, WC_ERR, WC_ERR, WC_ERR, WC_ERR
};

static thchar_t uni_tis620_0_map_[96] = {
  TH_ERR,    0xa1,   0xa2,   0xa3,   0xa4,   0xa5,   0xa6,   0xa7,
    0xa8,    0xa9,   0xaa,   0xab,   0xac,   0xad,   0xae,   0xaf,
    0xb0,    0xb1,   0xb2,   0xb3,   0xb4,   0xb5,   0xb6,   0xb7,
    0xb8,    0xb9,   0xba,   0xbb,   0xbc,   0xbd,   0xbe,   0xbf,
    0xc0,    0xc1,   0xc2,   0xc3,   0xc4,   0xc5,   0xc6,   0xc7,
    0xc8,    0xc9,   0xca,   0xcb,   0xcc,   0xcd,   0xce,   0xcf,
    0xd0,    0xd1,   0xd2,   0xd3,   0xd4,   0xd5,   0xd6,   0xd7,
    0xd8,    0xd9,   0xda, TH_ERR, TH_ERR, TH_ERR, TH_ERR,   0xdf,
    0xe0,    0xe1,   0xe2,   0xe3,   0xe4,   0xe5,   0xe6,   0xe7,
    0xe8,    0xe9,   0xea,   0xeb,   0xec,   0xed,   0xee,   0xef,
    0xf0,    0xf1,   0xf2,   0xf3,   0xf4,   0xf5,   0xf6,   0xf7,
    0xf8,    0xf9,   0xfa,   0xfb, TH_ERR, TH_ERR, TH_ERR, TH_ERR
};

static thwchar_t tis620_1_uni_map_[128] = {
    0x00ab, 0x00bb, 0x2026, 0xf88c, 0xf88f, 0xf892, 0xf895, 0xf898,
    0xf88b, 0xf88e, 0xf891, 0xf894, 0xf897, 0x201c, 0x201d, 0xf899,
    WC_ERR, 0x2022, 0xf884, 0xf889, 0xf885, 0xf886, 0xf887, 0xf888,
    0xf88a, 0xf88d, 0xf890, 0xf893, 0xf896, 0x2018, 0x2019, WC_ERR,
    0x00a0, 0x0e01, 0x0e02, 0x0e03, 0x0e04, 0x0e05, 0x0e06, 0x0e07,
    0x0e08, 0x0e09, 0x0e0a, 0x0e0b, 0x0e0c, 0x0e0d, 0x0e0e, 0x0e0f,
    0x0e10, 0x0e11, 0x0e12, 0x0e13, 0x0e14, 0x0e15, 0x0e16, 0x0e17,
    0x0e18, 0x0e19, 0x0e1a, 0x0e1b, 0x0e1c, 0x0e1d, 0x0e1e, 0x0e1f,
    0x0e20, 0x0e21, 0x0e22, 0x0e23, 0x0e24, 0x0e25, 0x0e26, 0x0e27,
    0x0e28, 0x0e29, 0x0e2a, 0x0e2b, 0x0e2c, 0x0e2d, 0x0e2e, 0x0e2f,
    0x0e30, 0x0e31, 0x0e32, 0x0e33, 0x0e34, 0x0e35, 0x0e36, 0x0e37,
    0x0e38, 0x0e39, 0x0e3a, 0xfeff, 0x200b, 0x2013, 0x2014, 0x0e3f,
    0x0e40, 0x0e41, 0x0e42, 0x0e43, 0x0e44, 0x0e45, 0x0e46, 0x0e47,
    0x0e48, 0x0e49, 0x0e4a, 0x0e4b, 0x0e4c, 0x0e4d, 0x2122, 0x0e4f,
    0x0e50, 0x0e51, 0x0e52, 0x0e53, 0x0e54, 0x0e55, 0x0e56, 0x0e57,
    0x0e58, 0x0e59, 0x00ae, 0x00a9, WC_ERR, WC_ERR, WC_ERR, WC_ERR
};

static thwchar_t tis620_2_uni_map_[128] = {
    0xf700, 0xf701, 0xf702, 0xf703, 0xf704, 0x2026, 0xf705, 0xf706,
    0xf707, 0xf708, 0xf709, 0xf70a, 0xf70b, 0xf70c, 0xf70d, 0xf70e,
    0xf70f, 0x2018, 0x2019, 0x201c, 0x201d, 0x2022, 0x2013, 0x2014,
    0xf710, 0xf711, 0xf712, 0xf713, 0xf714, 0xf715, 0xf716, 0xf717,
    0x00a0, 0x0e01, 0x0e02, 0x0e03, 0x0e04, 0x0e05, 0x0e06, 0x0e07,
    0x0e08, 0x0e09, 0x0e0a, 0x0e0b, 0x0e0c, 0x0e0d, 0x0e0e, 0x0e0f,
    0x0e10, 0x0e11, 0x0e12, 0x0e13, 0x0e14, 0x0e15, 0x0e16, 0x0e17,
    0x0e18, 0x0e19, 0x0e1a, 0x0e1b, 0x0e1c, 0x0e1d, 0x0e1e, 0x0e1f,
    0x0e20, 0x0e21, 0x0e22, 0x0e23, 0x0e24, 0x0e25, 0x0e26, 0x0e27,
    0x0e28, 0x0e29, 0x0e2a, 0x0e2b, 0x0e2c, 0x0e2d, 0x0e2e, 0x0e2f,
    0x0e30, 0x0e31, 0x0e32, 0x0e33, 0x0e34, 0x0e35, 0x0e36, 0x0e37,
    0x0e38, 0x0e39, 0x0e3a, WC_ERR, WC_ERR, WC_ERR, WC_ERR, 0x0e3f,
    0x0e40, 0x0e41, 0x0e42, 0x0e43, 0x0e44, 0x0e45, 0x0e46, 0x0e47,
    0x0e48, 0x0e49, 0x0e4a, 0x0e4b, 0x0e4c, 0x0e4d, 0x0e4e, 0x0e4f,
    0x0e50, 0x0e51, 0x0e52, 0x0e53, 0x0e54, 0x0e55, 0x0e56, 0x0e57,
    0x0e58, 0x0e59, 0x0e5a, 0x0e5b, 0xf718, 0xf719, 0xf71a, WC_ERR
};

thwchar_t th_tis2uni(thchar_t c)
{
    return (c < 0x80) ? (thwchar_t)c : tis620_0_uni_map_[c-0x80];
}

int th_tis2uni_line(const thchar_t *s, thwchar_t result[], size_t n)
{
    int left = n;
    while (*s && left > 1) {
        *result++ = th_tis2uni(*s++);
        --left;
    }
    *result = 0;
    return n - left;
}

thwchar_t th_winthai2uni(thchar_t c)
{
    return (c < 0x80) ? (thwchar_t)c : tis620_2_uni_map_[c-0x80];
}

thwchar_t th_macthai2uni(thchar_t c)
{
    return (c < 0x80) ? (thwchar_t)c : tis620_1_uni_map_[c-0x80];
}


thchar_t th_uni2tis(thwchar_t c)
{
    if (c < 0x0080) { 
        /* BASIC_LATIN range */
        return (thchar_t) c ;
    } else if (0x0e00 <= c && c <= 0x0e5f) {
        /* THAI range */
        return uni_tis620_0_map_[c-0x0e00];
    } else {
        /* out of range */
        return TH_ERR;
    }
}

int th_uni2tis_line(const thwchar_t *s, thchar_t result[], size_t n)
{
    int left = n;
    while (*s && left > 1) {
        *result++ = th_uni2tis(*s++);
        --left;
    }
    *result = 0;
    return n - left;
}


static thchar_t uni2thai_ext_(thwchar_t wc, const thwchar_t rev_map[])
{
    /* wc assumed out of TIS range */
    thchar_t c = 0x80;
    do {
        if (rev_map[c-0x80] == wc) return c;
    } while (c++ <= 0xff);
    return TH_ERR;
}

thchar_t th_uni2winthai(thwchar_t wc)
{
    thchar_t c = th_uni2tis(wc);
    return (c == TH_ERR) ? uni2thai_ext_(wc, tis620_2_uni_map_) : c;
}

thchar_t th_uni2macthai(thwchar_t wc)
{
    thchar_t c = th_uni2tis(wc);
    return (c == TH_ERR) ? uni2thai_ext_(wc, tis620_1_uni_map_) : c;
}

