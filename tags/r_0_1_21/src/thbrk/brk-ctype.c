/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * libthai - Thai Language Support Library
 * Copyright (C) 2001  Theppitak Karoonboonyanan <thep@linux.thai.net>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

/*
 * brk-ctype.c - Character classification for line break purpose
 * Created: 2007-06-10
 * Author:  Theppitak Karoonboonyanan <thep@linux.thai.net>
 */

#include "brk-ctype.h"

static brk_class_t _char_class[] = {
/*0x00*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x01*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x02*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x03*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x04*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x05*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x06*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x07*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x08*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x09*/ BRK_CLASS_SPACE,    /* Unicode: BA */  /* <control> */
/*0x0A*/ BRK_CLASS_MB,       /* Unicode: LF */  /* <control> */
/*0x0B*/ BRK_CLASS_MB,       /* Unicode: BK */  /* <control> */
/*0x0C*/ BRK_CLASS_MB,       /* Unicode: BK */  /* <control> */
/*0x0D*/ BRK_CLASS_MB,       /* Unicode: CR */  /* <control> */
/*0x0E*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x0F*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x10*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x11*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x12*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x13*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x14*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x15*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x16*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x17*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x18*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x19*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x1A*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x1B*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x1C*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x1D*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x1E*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x1F*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x20*/ BRK_CLASS_SPACE,    /* Unicode: SP */  /* SPACE */
/*0x21*/ BRK_CLASS_NBB,      /* Unicode: EX */  /* EXCLAMATION MARK */
/*0x22*/ BRK_CLASS_QUOTE,    /* Unicode: QU */  /* QUOTATION MARK */
/*0x23*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* NUMBER SIGN */
/*0x24*/ BRK_CLASS_NUM_CUR,  /* Unicode: PR */  /* DOLLAR SIGN */
/*0x25*/ BRK_CLASS_NUM_NBB,  /* Unicode: PO */  /* PERCENT SIGN */
/*0x26*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* AMPERSAND */
/*0x27*/ BRK_CLASS_QUOTE,    /* Unicode: QU */  /* APOSTROPHE */
/*0x28*/ BRK_CLASS_NBA,      /* Unicode: OP */  /* LEFT PARENTHESIS */
/*0x29*/ BRK_CLASS_NBB,      /* Unicode: CL */  /* RIGHT PARENTHESIS */
/*0x2A*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* ASTERISK */
/*0x2B*/ BRK_CLASS_NUM_CUR,  /* Unicode: PR */  /* PLUS SIGN */
/*0x2C*/ BRK_CLASS_NUM_NB,   /* Unicode: IS */  /* COMMA */
/*0x2D*/ BRK_CLASS_HYPHEN,   /* Unicode: HY */  /* HYPHEN-MINUS */
/*0x2E*/ BRK_CLASS_NUM_NB,   /* Unicode: IS */  /* FULL STOP */
/*0x2F*/ BRK_CLASS_NBB,      /* Unicode: SY */  /* SOLIDUS */
/*0x30*/ BRK_CLASS_NUM,      /* Unicode: NU */  /* DIGIT ZERO */
/*0x31*/ BRK_CLASS_NUM,      /* Unicode: NU */  /* DIGIT ONE */
/*0x32*/ BRK_CLASS_NUM,      /* Unicode: NU */  /* DIGIT TWO */
/*0x33*/ BRK_CLASS_NUM,      /* Unicode: NU */  /* DIGIT THREE */
/*0x34*/ BRK_CLASS_NUM,      /* Unicode: NU */  /* DIGIT FOUR */
/*0x35*/ BRK_CLASS_NUM,      /* Unicode: NU */  /* DIGIT FIVE */
/*0x36*/ BRK_CLASS_NUM,      /* Unicode: NU */  /* DIGIT SIX */
/*0x37*/ BRK_CLASS_NUM,      /* Unicode: NU */  /* DIGIT SEVEN */
/*0x38*/ BRK_CLASS_NUM,      /* Unicode: NU */  /* DIGIT EIGHT */
/*0x39*/ BRK_CLASS_NUM,      /* Unicode: NU */  /* DIGIT NINE */
/*0x3A*/ BRK_CLASS_NUM_NB,   /* Unicode: IS */  /* COLON */
/*0x3B*/ BRK_CLASS_NUM_NB,   /* Unicode: IS */  /* SEMICOLON */
/*0x3C*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* LESS-THAN SIGN */
/*0x3D*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* EQUALS SIGN */
/*0x3E*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* GREATER-THAN SIGN */
/*0x3F*/ BRK_CLASS_NBB,      /* Unicode: EX */  /* QUESTION MARK */
/*0x40*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* COMMERCIAL AT */
/*0x41*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* LATIN CAPITAL LETTER A */
/*0x42*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* LATIN CAPITAL LETTER B */
/*0x43*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* LATIN CAPITAL LETTER C */
/*0x44*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* LATIN CAPITAL LETTER D */
/*0x45*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* LATIN CAPITAL LETTER E */
/*0x46*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* LATIN CAPITAL LETTER F */
/*0x47*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* LATIN CAPITAL LETTER G */
/*0x48*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* LATIN CAPITAL LETTER H */
/*0x49*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* LATIN CAPITAL LETTER I */
/*0x4A*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* LATIN CAPITAL LETTER J */
/*0x4B*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* LATIN CAPITAL LETTER K */
/*0x4C*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* LATIN CAPITAL LETTER L */
/*0x4D*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* LATIN CAPITAL LETTER M */
/*0x4E*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* LATIN CAPITAL LETTER N */
/*0x4F*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* LATIN CAPITAL LETTER O */
/*0x50*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* LATIN CAPITAL LETTER P */
/*0x51*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* LATIN CAPITAL LETTER Q */
/*0x52*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* LATIN CAPITAL LETTER R */
/*0x53*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* LATIN CAPITAL LETTER S */
/*0x54*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* LATIN CAPITAL LETTER T */
/*0x55*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* LATIN CAPITAL LETTER U */
/*0x56*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* LATIN CAPITAL LETTER V */
/*0x57*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* LATIN CAPITAL LETTER W */
/*0x58*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* LATIN CAPITAL LETTER X */
/*0x59*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* LATIN CAPITAL LETTER Y */
/*0x5A*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* LATIN CAPITAL LETTER Z */
/*0x5B*/ BRK_CLASS_NBA,      /* Unicode: OP */  /* LEFT SQUARE BRACKET */
/*0x5C*/ BRK_CLASS_NUM_CUR,  /* Unicode: PR */  /* REVERSE SOLIDUS */
/*0x5D*/ BRK_CLASS_NBB,      /* Unicode: CL */  /* RIGHT SQUARE BRACKET */
/*0x5E*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* CIRCUMFLEX ACCENT */
/*0x5F*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* LOW LINE */
/*0x60*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* GRAVE ACCENT */
/*0x61*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* LATIN SMALL LETTER A */
/*0x62*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* LATIN SMALL LETTER B */
/*0x63*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* LATIN SMALL LETTER C */
/*0x64*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* LATIN SMALL LETTER D */
/*0x65*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* LATIN SMALL LETTER E */
/*0x66*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* LATIN SMALL LETTER F */
/*0x67*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* LATIN SMALL LETTER G */
/*0x68*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* LATIN SMALL LETTER H */
/*0x69*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* LATIN SMALL LETTER I */
/*0x6A*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* LATIN SMALL LETTER J */
/*0x6B*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* LATIN SMALL LETTER K */
/*0x6C*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* LATIN SMALL LETTER L */
/*0x6D*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* LATIN SMALL LETTER M */
/*0x6E*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* LATIN SMALL LETTER N */
/*0x6F*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* LATIN SMALL LETTER O */
/*0x70*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* LATIN SMALL LETTER P */
/*0x71*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* LATIN SMALL LETTER Q */
/*0x72*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* LATIN SMALL LETTER R */
/*0x73*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* LATIN SMALL LETTER S */
/*0x74*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* LATIN SMALL LETTER T */
/*0x75*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* LATIN SMALL LETTER U */
/*0x76*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* LATIN SMALL LETTER V */
/*0x77*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* LATIN SMALL LETTER W */
/*0x78*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* LATIN SMALL LETTER X */
/*0x79*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* LATIN SMALL LETTER Y */
/*0x7A*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* LATIN SMALL LETTER Z */
/*0x7B*/ BRK_CLASS_NBA,      /* Unicode: OP */  /* LEFT CURLY BRACKET */
/*0x7C*/ BRK_CLASS_SPACE,    /* Unicode: BA */  /* VERTICAL LINE */
/*0x7D*/ BRK_CLASS_NBB,      /* Unicode: CL */  /* RIGHT CURLY BRACKET */
/*0x7E*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* TILDE */
/*0x7F*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x80*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x81*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x82*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x83*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x84*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x85*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x86*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x87*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x88*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x89*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x8A*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x8B*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x8C*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x8D*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x8E*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x8F*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x90*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x91*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x92*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x93*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x94*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x95*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x96*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x97*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x98*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x99*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x9A*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x9B*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x9C*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x9D*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x9E*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0x9F*/ BRK_CLASS_NBB,      /* Unicode: CM */  /* <control> */
/*0xA0*/ BRK_CLASS_NB,       /* Unicode: GL */  /* NO-BREAK SPACE */
/*0xA1*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER KO KAI */
/*0xA2*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER KHO KHAI */
/*0xA3*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER KHO KHUAT */
/*0xA4*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER KHO KHWAI */
/*0xA5*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER KHO KHON */
/*0xA6*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER KHO RAKHANG */
/*0xA7*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER NGO NGU */
/*0xA8*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER CHO CHAN */
/*0xA9*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER CHO CHING */
/*0xAA*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER CHO CHANG */
/*0xAB*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER SO SO */
/*0xAC*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER CHO CHOE */
/*0xAD*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER YO YING */
/*0xAE*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER DO CHADA */
/*0xAF*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER TO PATAK */
/*0xB0*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER THO THAN */
/*0xB1*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER THO NANGMONTHO */
/*0xB2*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER THO PHUTHAO */
/*0xB3*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER NO NEN */
/*0xB4*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER DO DEK */
/*0xB5*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER TO TAO */
/*0xB6*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER THO THUNG */
/*0xB7*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER THO THAHAN */
/*0xB8*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER THO THONG */
/*0xB9*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER NO NU */
/*0xBA*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER BO BAIMAI */
/*0xBB*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER PO PLA */
/*0xBC*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER PHO PHUNG */
/*0xBD*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER FO FA */
/*0xBE*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER PHO PHAN */
/*0xBF*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER FO FAN */
/*0xC0*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER PHO SAMPHAO */
/*0xC1*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER MO MA */
/*0xC2*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER YO YAK */
/*0xC3*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER RO RUA */
/*0xC4*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER RU */
/*0xC5*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER LO LING */
/*0xC6*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER LU */
/*0xC7*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER WO WAEN */
/*0xC8*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER SO SALA */
/*0xC9*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER SO RUSI */
/*0xCA*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER SO SUA */
/*0xCB*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER HO HIP */
/*0xCC*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER LO CHULA */
/*0xCD*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER O ANG */
/*0xCE*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER HO NOKHUK */
/*0xCF*/ BRK_CLASS_NBB,      /* Unicode: SA */  /* THAI CHARACTER PAIYANNOI */
/*0xD0*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER SARA A */
/*0xD1*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER MAI HAN-AKAT */
/*0xD2*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER SARA AA */
/*0xD3*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER SARA AM */
/*0xD4*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER SARA I */
/*0xD5*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER SARA II */
/*0xD6*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER SARA UE */
/*0xD7*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER SARA UEE */
/*0xD8*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER SARA U */
/*0xD9*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER SARA UU */
/*0xDA*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER PHINTHU */
/*0xDB*/ BRK_CLASS_NBB,      /* Unicode: -  */  /* -- Unencoded -- */
/*0xDC*/ BRK_CLASS_NBB,      /* Unicode: -  */  /* -- Unencoded -- */
/*0xDD*/ BRK_CLASS_NBB,      /* Unicode: -  */  /* -- Unencoded -- */
/*0xDE*/ BRK_CLASS_NBB,      /* Unicode: -  */  /* -- Unencoded -- */
/*0xDF*/ BRK_CLASS_NUM_CUR,  /* Unicode: PR */  /* THAI CURRENCY SYMBOL BAHT */
/*0xE0*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER SARA E */
/*0xE1*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER SARA AE */
/*0xE2*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER SARA O */
/*0xE3*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER SARA AI MAIMUAN */
/*0xE4*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER SARA AI MAIMALAI */
/*0xE5*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER LAKKHANGYAO */
/*0xE6*/ BRK_CLASS_NBB,      /* Unicode: SA */  /* THAI CHARACTER MAIYAMOK */
/*0xE7*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER MAITAIKHU */
/*0xE8*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER MAI EK */
/*0xE9*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER MAI THO */
/*0xEA*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER MAI TRI */
/*0xEB*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER MAI CHATTAWA */
/*0xEC*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER THANTHAKHAT */
/*0xED*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER NIKHAHIT */
/*0xEE*/ BRK_CLASS_THAI,     /* Unicode: SA */  /* THAI CHARACTER YAMAKKAN */
/*0xEF*/ BRK_CLASS_ALPHA,    /* Unicode: AL */  /* THAI CHARACTER FONGMAN */
/*0xF0*/ BRK_CLASS_NUM,      /* Unicode: NU */  /* THAI DIGIT ZERO */
/*0xF1*/ BRK_CLASS_NUM,      /* Unicode: NU */  /* THAI DIGIT ONE */
/*0xF2*/ BRK_CLASS_NUM,      /* Unicode: NU */  /* THAI DIGIT TWO */
/*0xF3*/ BRK_CLASS_NUM,      /* Unicode: NU */  /* THAI DIGIT THREE */
/*0xF4*/ BRK_CLASS_NUM,      /* Unicode: NU */  /* THAI DIGIT FOUR */
/*0xF5*/ BRK_CLASS_NUM,      /* Unicode: NU */  /* THAI DIGIT FIVE */
/*0xF6*/ BRK_CLASS_NUM,      /* Unicode: NU */  /* THAI DIGIT SIX */
/*0xF7*/ BRK_CLASS_NUM,      /* Unicode: NU */  /* THAI DIGIT SEVEN */
/*0xF8*/ BRK_CLASS_NUM,      /* Unicode: NU */  /* THAI DIGIT EIGHT */
/*0xF9*/ BRK_CLASS_NUM,      /* Unicode: NU */  /* THAI DIGIT NINE */
/*0xFA*/ BRK_CLASS_TERM,     /* Unicode: BA */  /* THAI CHARACTER ANGKHANKHU */
/*0xFB*/ BRK_CLASS_TERM,     /* Unicode: BA */  /* THAI CHARACTER KHOMUT */
/*0xFC*/ BRK_CLASS_NBB,      /* Unicode: -  */  /* -- Unencoded -- */
/*0xFD*/ BRK_CLASS_NBB,      /* Unicode: -  */  /* -- Unencoded -- */
/*0xFE*/ BRK_CLASS_NBB,      /* Unicode: -  */  /* -- Unencoded -- */
/*0xFF*/ BRK_CLASS_NBB,      /* Unicode: -  */  /* -- Unencoded -- */
};

#define _P BRK_OP_PROHIBITED
#define _A BRK_OP_ALLOWED
#define _I BRK_OP_INDIRECT

static brk_op_t _break_table[BRK_CLASS_TOTAL][BRK_CLASS_TOTAL] = {
           /* THA ALP NUM NBB NBA NB  MB  SPA QUO HYP NUM NUM NUM TER */
           /* I   HA                      CE  TE  HEN NBB CUR NB  M   */
/*THAI*/    { _I, _A, _A, _P, _A, _I, _P, _P, _I, _I, _A, _A, _P, _I, },
/*ALPHA*/   { _A, _I, _A, _P, _A, _I, _P, _P, _I, _I, _A, _A, _P, _I, },
/*NUM*/     { _A, _A, _I, _P, _A, _I, _P, _P, _I, _I, _I, _P, _P, _I, },
/*NBB*/     { _A, _A, _A, _P, _A, _I, _P, _P, _I, _I, _A, _A, _P, _I, },
/*NBA*/     { _P, _P, _P, _P, _P, _P, _P, _P, _P, _P, _P, _P, _P, _P, },
/*NB*/      { _I, _I, _I, _P, _I, _I, _P, _P, _I, _I, _I, _I, _P, _I, },
/*MB*/      { _A, _A, _A, _A, _A, _A, _A, _A, _A, _A, _A, _A, _A, _A, },
/*SPACE*/   { _A, _A, _A, _P, _A, _A, _P, _P, _A, _A, _A, _A, _P, _A, },
/*QUOTE*/   { _I, _I, _I, _P, _I, _I, _P, _P, _I, _I, _I, _I, _P, _I, },
/*HYPHEN*/  { _A, _A, _I, _P, _A, _I, _P, _P, _I, _I, _A, _A, _P, _I, },
/*NUM_NBB*/ { _A, _A, _A, _P, _A, _I, _P, _P, _I, _A, _A, _A, _P, _I, },
/*NUM_CUR*/ { _A, _A, _P, _P, _A, _I, _P, _P, _I, _P, _A, _A, _P, _I, },
/*NUM_NB*/  { _A, _A, _I, _P, _A, _I, _P, _P, _I, _I, _A, _A, _P, _I, },
/*TERM*/    { _A, _A, _A, _P, _A, _I, _P, _P, _I, _I, _A, _A, _P, _I, },
};

#define _BRK_CHARCLASS(c)  (_char_class[c])

brk_class_t
brk_class (thchar_t c)
{
  return _BRK_CHARCLASS (c);
}

brk_op_t
brk_op (brk_class_t prev, brk_class_t next)
{
  return _break_table[prev][next];
}

/*
vi:ts=4:ai:expandtab
*/
