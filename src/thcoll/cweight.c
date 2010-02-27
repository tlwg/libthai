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
 * cweight.c - Thai Character Weight Table for TIS-620/2533 Collating
 * Created: 9 Nov 1998
 * Author:  Theppitak Karoonboonyanan <thep@linux.thai.net>
 */

/*
 * The ordering algorithm is in accordance
 * with the Thai Royal Institute Dictionary
 * 2525 B.E. Edition
 */

#include <assert.h>
#include "cweight.h"

#define TOT_CHARS   256

/* level 1 symbols & order */
enum l1_symbols {
    L1_08 = TOT_LEVELS,
    L1_18,
    L1_28,
    L1_38,
    L1_48,
    L1_58,
    L1_68,
    L1_78,
    L1_88,
    L1_98,
    L1_A8,
    L1_B8,
    L1_C8,
    L1_D8,
    L1_E8,
    L1_F8,
    L1_G8,
    L1_H8,
    L1_I8,
    L1_J8,
    L1_K8,
    L1_L8,
    L1_M8,
    L1_N8,
    L1_O8,
    L1_P8,
    L1_Q8,
    L1_R8,
    L1_S8,
    L1_T8,
    L1_U8,
    L1_V8,
    L1_W8,
    L1_X8,
    L1_Y8,
    L1_Z8,
    L1_KO_KAI,
    L1_KHO_KHAI,
    L1_KHO_KHUAT,
    L1_KHO_KHWAI,
    L1_KHO_KHON,
    L1_KHO_RAKHANG,
    L1_NGO_NGU,
    L1_CHO_CHAN,
    L1_CHO_CHING,
    L1_CHO_CHANG,
    L1_SO_SO,
    L1_CHO_CHOE,
    L1_YO_YING,
    L1_DO_CHADA,
    L1_TO_PATAK,
    L1_THO_THAN,
    L1_THO_NANGMONTHO,
    L1_THO_PHUTHAO,
    L1_NO_NEN,
    L1_DO_DEK,
    L1_TO_TAO,
    L1_THO_THUNG,
    L1_THO_THAHAN,
    L1_THO_THONG,
    L1_NO_NU,
    L1_BO_BAIMAI,
    L1_PO_PLA,
    L1_PHO_PHUNG,
    L1_FO_FA,
    L1_PHO_PHAN,
    L1_FO_FAN,
    L1_PHO_SAMPHAO,
    L1_MO_MA,
    L1_YO_YAK,
    L1_RO_RUA,
    L1_RU,
    L1_LO_LING,
    L1_LU,
    L1_WO_WAEN,
    L1_SO_SALA,
    L1_SO_RUSI,
    L1_SO_SUA,
    L1_HO_HIP,
    L1_LO_CHULA,
    L1_O_ANG,
    L1_HO_NOKHUK,
    L1_NKHIT,
    L1_SARA_A,
    L1_MAI_HAN_AKAT,
    L1_SARA_AA,
    L1_SARA_AM,
    L1_SARA_I,
    L1_SARA_II,
    L1_SARA_UE,
    L1_SARA_UEE,
    L1_SARA_U,
    L1_SARA_UU,
    L1_SARA_E,
    L1_SARA_AE,
    L1_SARA_O,
    L1_SARA_AI_MAIMUAN,
    L1_SARA_AI_MAIMALAI
};
  
/* level 2 symbols & order */
enum l2_symbols {
    L2_BLANK = TOT_LEVELS,
    L2_THAII,
    L2_YAMAK,
    L2_PINTU,
    L2_GARAN,
    L2_TYKHU,
    L2_TONE1,
    L2_TONE2,
    L2_TONE3,
    L2_TONE4
};
  
/* level 3 symbols & order */
enum l3_symbols {
    L3_BLANK = TOT_LEVELS,
    L3_SPACE,
    L3_NB_SACE,
    L3_LOW_LINE,
    L3_HYPHEN,
    L3_COMMA,
    L3_SEMICOLON,
    L3_COLON,
    L3_EXCLAMATION,
    L3_QUESTION,
    L3_SOLIDUS,
    L3_FULL_STOP,
    L3_PAIYAN_NOI,
    L3_MAI_YAMOK,
    L3_GRAVE,
    L3_CIRCUMFLEX,
    L3_TILDE,
    L3_APOSTROPHE,
    L3_QUOTATION,
    L3_L_PARANTHESIS,
    L3_L_BRACKET,
    L3_L_BRACE,
    L3_R_BRACE,
    L3_R_BRACKET,
    L3_R_PARENTHESIS,
    L3_AT,
    L3_BAHT,
    L3_DOLLAR,
    L3_FONGMAN,
    L3_ANGKHANKHU,
    L3_KHOMUT,
    L3_ASTERISK,
    L3_BK_SOLIDUS,
    L3_AMPERSAND,
    L3_NUMBER,
    L3_PERCENT,
    L3_PLUS,
    L3_LESS_THAN,
    L3_EQUAL,
    L3_GREATER_THAN,
    L3_V_LINE
};

/* level 4 symbols & order */
enum l4_symbols {
    L4_BLK = TOT_LEVELS,
    L4_MIN,
    L4_CAP,
    L4_EXT
};


static thchar_t char_weight_tbl_[TOT_CHARS][TOT_LEVELS] = {
    /*0x00*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x01*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x02*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x03*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x04*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x05*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x06*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x07*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x08*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x09*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x0A*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x0B*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x0C*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x0D*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x0E*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x0F*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x10*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x11*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x12*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x13*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x14*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x15*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x16*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x17*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x18*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x19*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x1A*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x1B*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x1C*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x1D*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x1E*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x1F*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x20*/ { IGNORE, IGNORE, L3_SPACE, IGNORE          }, /*   */
    /*0x21*/ { IGNORE, IGNORE, L3_EXCLAMATION, IGNORE    }, /* ! */
    /*0x22*/ { IGNORE, IGNORE, L3_QUOTATION, IGNORE      }, /* " */
    /*0x23*/ { IGNORE, IGNORE, L3_NUMBER, IGNORE         }, /* # */
    /*0x24*/ { IGNORE, IGNORE, L3_DOLLAR, IGNORE         }, /* $ */
    /*0x25*/ { IGNORE, IGNORE, L3_PERCENT, IGNORE        }, /* % */
    /*0x26*/ { IGNORE, IGNORE, L3_AMPERSAND, IGNORE      }, /* & */
    /*0x27*/ { IGNORE, IGNORE, L3_APOSTROPHE, IGNORE     }, /* ' */
    /*0x28*/ { IGNORE, IGNORE, L3_L_PARANTHESIS, IGNORE  }, /* ( */
    /*0x29*/ { IGNORE, IGNORE, L3_R_PARENTHESIS, IGNORE  }, /* ) */
    /*0x2A*/ { IGNORE, IGNORE, L3_ASTERISK, IGNORE       }, /* * */
    /*0x2B*/ { IGNORE, IGNORE, L3_PLUS, IGNORE           }, /* + */
    /*0x2C*/ { IGNORE, IGNORE, L3_COMMA, IGNORE          }, /* , */
    /*0x2D*/ { IGNORE, IGNORE, L3_HYPHEN, IGNORE         }, /* _ */
    /*0x2E*/ { IGNORE, IGNORE, L3_FULL_STOP, IGNORE      }, /* . */
    /*0x2F*/ { IGNORE, IGNORE, L3_SOLIDUS, IGNORE        }, /* / */
    /*0x30*/ { L1_08, L2_BLANK, L3_BLANK, L4_BLK  }, /* 0 */
    /*0x31*/ { L1_18, L2_BLANK, L3_BLANK, L4_BLK  }, /* 1 */
    /*0x32*/ { L1_28, L2_BLANK, L3_BLANK, L4_BLK  }, /* 2 */
    /*0x33*/ { L1_38, L2_BLANK, L3_BLANK, L4_BLK  }, /* 3 */
    /*0x34*/ { L1_48, L2_BLANK, L3_BLANK, L4_BLK  }, /* 4 */
    /*0x35*/ { L1_58, L2_BLANK, L3_BLANK, L4_BLK  }, /* 5 */
    /*0x36*/ { L1_68, L2_BLANK, L3_BLANK, L4_BLK  }, /* 6 */
    /*0x37*/ { L1_78, L2_BLANK, L3_BLANK, L4_BLK  }, /* 7 */
    /*0x38*/ { L1_88, L2_BLANK, L3_BLANK, L4_BLK  }, /* 8 */
    /*0x39*/ { L1_98, L2_BLANK, L3_BLANK, L4_BLK  }, /* 9 */
    /*0x3A*/ { IGNORE, IGNORE, L3_COLON, IGNORE          }, /* : */
    /*0x3B*/ { IGNORE, IGNORE, L3_SEMICOLON, IGNORE      }, /* ; */
    /*0x3C*/ { IGNORE, IGNORE, L3_LESS_THAN, IGNORE      }, /* < */
    /*0x3D*/ { IGNORE, IGNORE, L3_EQUAL, IGNORE          }, /* = */
    /*0x3E*/ { IGNORE, IGNORE, L3_GREATER_THAN, IGNORE   }, /* > */
    /*0x3F*/ { IGNORE, IGNORE, L3_QUESTION, IGNORE       }, /* ? */
    /*0x40*/ { IGNORE, IGNORE, L3_AT, IGNORE             }, /* @ */
    /*0x41*/ { L1_A8, L2_BLANK, L3_BLANK, L4_CAP  }, /* A */
    /*0x42*/ { L1_B8, L2_BLANK, L3_BLANK, L4_CAP  }, /* B */
    /*0x43*/ { L1_C8, L2_BLANK, L3_BLANK, L4_CAP  }, /* C */
    /*0x44*/ { L1_D8, L2_BLANK, L3_BLANK, L4_CAP  }, /* D */
    /*0x45*/ { L1_E8, L2_BLANK, L3_BLANK, L4_CAP  }, /* E */
    /*0x46*/ { L1_F8, L2_BLANK, L3_BLANK, L4_CAP  }, /* F */
    /*0x47*/ { L1_G8, L2_BLANK, L3_BLANK, L4_CAP  }, /* G */
    /*0x48*/ { L1_H8, L2_BLANK, L3_BLANK, L4_CAP  }, /* H */
    /*0x49*/ { L1_I8, L2_BLANK, L3_BLANK, L4_CAP  }, /* I */
    /*0x4A*/ { L1_J8, L2_BLANK, L3_BLANK, L4_CAP  }, /* J */
    /*0x4B*/ { L1_K8, L2_BLANK, L3_BLANK, L4_CAP  }, /* K */
    /*0x4C*/ { L1_L8, L2_BLANK, L3_BLANK, L4_CAP  }, /* L */
    /*0x4D*/ { L1_M8, L2_BLANK, L3_BLANK, L4_CAP  }, /* M */
    /*0x4E*/ { L1_N8, L2_BLANK, L3_BLANK, L4_CAP  }, /* N */
    /*0x4F*/ { L1_O8, L2_BLANK, L3_BLANK, L4_CAP  }, /* O */
    /*0x50*/ { L1_P8, L2_BLANK, L3_BLANK, L4_CAP  }, /* P */
    /*0x51*/ { L1_Q8, L2_BLANK, L3_BLANK, L4_CAP  }, /* Q */
    /*0x52*/ { L1_R8, L2_BLANK, L3_BLANK, L4_CAP  }, /* R */
    /*0x53*/ { L1_S8, L2_BLANK, L3_BLANK, L4_CAP  }, /* S */
    /*0x54*/ { L1_T8, L2_BLANK, L3_BLANK, L4_CAP  }, /* T */
    /*0x55*/ { L1_U8, L2_BLANK, L3_BLANK, L4_CAP  }, /* U */
    /*0x56*/ { L1_V8, L2_BLANK, L3_BLANK, L4_CAP  }, /* V */
    /*0x57*/ { L1_W8, L2_BLANK, L3_BLANK, L4_CAP  }, /* W */
    /*0x58*/ { L1_X8, L2_BLANK, L3_BLANK, L4_CAP  }, /* X */
    /*0x59*/ { L1_Y8, L2_BLANK, L3_BLANK, L4_CAP  }, /* Y */
    /*0x5A*/ { L1_Z8, L2_BLANK, L3_BLANK, L4_CAP  }, /* Z */
    /*0x5B*/ { IGNORE, IGNORE, L3_L_BRACKET, IGNORE      }, /* [ */
    /*0x5C*/ { IGNORE, IGNORE, L3_BK_SOLIDUS, IGNORE     }, /* '\' */
    /*0x5D*/ { IGNORE, IGNORE, L3_R_BRACKET, IGNORE      }, /* ] */
    /*0x5E*/ { IGNORE, IGNORE, L3_CIRCUMFLEX, IGNORE     }, /* ^ */
    /*0x5F*/ { IGNORE, IGNORE, L3_LOW_LINE, IGNORE       }, /* _ */
    /*0x60*/ { IGNORE, IGNORE, L3_GRAVE, IGNORE          }, /* ` */
    /*0x61*/ { L1_A8, L2_BLANK, L3_BLANK, L4_MIN  }, /* a */
    /*0x62*/ { L1_B8, L2_BLANK, L3_BLANK, L4_MIN  }, /* b */
    /*0x63*/ { L1_C8, L2_BLANK, L3_BLANK, L4_MIN  }, /* c */
    /*0x64*/ { L1_D8, L2_BLANK, L3_BLANK, L4_MIN  }, /* d */
    /*0x65*/ { L1_E8, L2_BLANK, L3_BLANK, L4_MIN  }, /* e */
    /*0x66*/ { L1_F8, L2_BLANK, L3_BLANK, L4_MIN  }, /* f */
    /*0x67*/ { L1_G8, L2_BLANK, L3_BLANK, L4_MIN  }, /* g */
    /*0x68*/ { L1_H8, L2_BLANK, L3_BLANK, L4_MIN  }, /* h */
    /*0x69*/ { L1_I8, L2_BLANK, L3_BLANK, L4_MIN  }, /* i */
    /*0x6A*/ { L1_J8, L2_BLANK, L3_BLANK, L4_MIN  }, /* j */
    /*0x6B*/ { L1_K8, L2_BLANK, L3_BLANK, L4_MIN  }, /* k */
    /*0x6C*/ { L1_L8, L2_BLANK, L3_BLANK, L4_MIN  }, /* l */
    /*0x6D*/ { L1_M8, L2_BLANK, L3_BLANK, L4_MIN  }, /* m */
    /*0x6E*/ { L1_N8, L2_BLANK, L3_BLANK, L4_MIN  }, /* n */
    /*0x6F*/ { L1_O8, L2_BLANK, L3_BLANK, L4_MIN  }, /* o */
    /*0x70*/ { L1_P8, L2_BLANK, L3_BLANK, L4_MIN  }, /* p */
    /*0x71*/ { L1_Q8, L2_BLANK, L3_BLANK, L4_MIN  }, /* q */
    /*0x72*/ { L1_R8, L2_BLANK, L3_BLANK, L4_MIN  }, /* r */
    /*0x73*/ { L1_S8, L2_BLANK, L3_BLANK, L4_MIN  }, /* s */
    /*0x74*/ { L1_T8, L2_BLANK, L3_BLANK, L4_MIN  }, /* t */
    /*0x75*/ { L1_U8, L2_BLANK, L3_BLANK, L4_MIN  }, /* u */
    /*0x76*/ { L1_V8, L2_BLANK, L3_BLANK, L4_MIN  }, /* v */
    /*0x77*/ { L1_W8, L2_BLANK, L3_BLANK, L4_MIN  }, /* w */
    /*0x78*/ { L1_X8, L2_BLANK, L3_BLANK, L4_MIN  }, /* x */
    /*0x79*/ { L1_Y8, L2_BLANK, L3_BLANK, L4_MIN  }, /* y */
    /*0x7A*/ { L1_Z8, L2_BLANK, L3_BLANK, L4_MIN  }, /* z */
    /*0x7B*/ { IGNORE, IGNORE, L3_L_BRACE, IGNORE        }, /* { */
    /*0x7C*/ { IGNORE, IGNORE, L3_V_LINE, IGNORE         }, /* | */
    /*0x7D*/ { IGNORE, IGNORE, L3_R_BRACE, IGNORE        }, /* } */
    /*0x7E*/ { IGNORE, IGNORE, L3_TILDE, IGNORE          }, /* ~ */
    /*0x7F*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x80*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x81*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x82*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x83*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x84*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x85*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x86*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x87*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x88*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x89*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x8A*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x8B*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x8C*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x8D*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x8E*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x8F*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x90*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x91*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x92*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x93*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x94*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x95*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x96*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x97*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x98*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x99*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x9A*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x9B*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x9C*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x9D*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x9E*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0x9F*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0xA0*/ { IGNORE, IGNORE, L3_NB_SACE, IGNORE        }, /* NBSP */
    /*0xA1*/ { L1_KO_KAI, L2_BLANK, L3_BLANK, L4_BLK          }, /* KO KAI */
    /*0xA2*/ { L1_KHO_KHAI, L2_BLANK, L3_BLANK, L4_BLK        }, /* KHO KHAI */
    /*0xA3*/ { L1_KHO_KHUAT, L2_BLANK, L3_BLANK, L4_BLK       }, /* KHO KHUAT */
    /*0xA4*/ { L1_KHO_KHWAI, L2_BLANK, L3_BLANK, L4_BLK       }, /* KHO KHWAI */
    /*0xA5*/ { L1_KHO_KHON, L2_BLANK, L3_BLANK, L4_BLK        }, /* KHO KHON */
    /*0xA6*/ { L1_KHO_RAKHANG, L2_BLANK, L3_BLANK, L4_BLK     }, /* KHO RAKHANG */
    /*0xA7*/ { L1_NGO_NGU, L2_BLANK, L3_BLANK, L4_BLK         }, /* NGO NGU */
    /*0xA8*/ { L1_CHO_CHAN, L2_BLANK, L3_BLANK, L4_BLK        }, /* CHO CHAN */
    /*0xA9*/ { L1_CHO_CHING, L2_BLANK, L3_BLANK, L4_BLK       }, /* CHO CHING */
    /*0xAA*/ { L1_CHO_CHANG, L2_BLANK, L3_BLANK, L4_BLK       }, /* CHO CHANG */
    /*0xAB*/ { L1_SO_SO, L2_BLANK, L3_BLANK, L4_BLK           }, /* SO SO  */
    /*0xAC*/ { L1_CHO_CHOE, L2_BLANK, L3_BLANK, L4_BLK        }, /* CHO CHOE */
    /*0xAD*/ { L1_YO_YING, L2_BLANK, L3_BLANK, L4_BLK         }, /* YO YING */
    /*0xAE*/ { L1_DO_CHADA, L2_BLANK, L3_BLANK, L4_BLK        }, /* DO CHADA */
    /*0xAF*/ { L1_TO_PATAK, L2_BLANK, L3_BLANK, L4_BLK        }, /* TO PATAK */
    /*0xB0*/ { L1_THO_THAN, L2_BLANK, L3_BLANK, L4_BLK        }, /* THO THAN */
    /*0xB1*/ { L1_THO_NANGMONTHO, L2_BLANK, L3_BLANK, L4_BLK  }, /* THO NANGMONTHO */
    /*0xB2*/ { L1_THO_PHUTHAO, L2_BLANK, L3_BLANK, L4_BLK     }, /* THO PHUTHAO */
    /*0xB3*/ { L1_NO_NEN, L2_BLANK, L3_BLANK, L4_BLK          }, /* NO NEN */
    /*0xB4*/ { L1_DO_DEK, L2_BLANK, L3_BLANK, L4_BLK          }, /* DO DEK */
    /*0xB5*/ { L1_TO_TAO, L2_BLANK, L3_BLANK, L4_BLK          }, /* TO TAO */
    /*0xB6*/ { L1_THO_THUNG, L2_BLANK, L3_BLANK, L4_BLK       }, /* THO THUNG */
    /*0xB7*/ { L1_THO_THAHAN, L2_BLANK, L3_BLANK, L4_BLK      }, /* THO THAHAN */
    /*0xB8*/ { L1_THO_THONG, L2_BLANK, L3_BLANK, L4_BLK       }, /* THO THONG */
    /*0xB9*/ { L1_NO_NU, L2_BLANK, L3_BLANK, L4_BLK           }, /* NO NU */
    /*0xBA*/ { L1_BO_BAIMAI, L2_BLANK, L3_BLANK, L4_BLK       }, /* BO BAIMAI */
    /*0xBB*/ { L1_PO_PLA, L2_BLANK, L3_BLANK, L4_BLK          }, /* PO PLA */
    /*0xBC*/ { L1_PHO_PHUNG, L2_BLANK, L3_BLANK, L4_BLK       }, /* PHO PHUNG */
    /*0xBD*/ { L1_FO_FA, L2_BLANK, L3_BLANK, L4_BLK           }, /* FO FA */
    /*0xBE*/ { L1_PHO_PHAN, L2_BLANK, L3_BLANK, L4_BLK        }, /* PHO PHAN */
    /*0xBF*/ { L1_FO_FAN, L2_BLANK, L3_BLANK, L4_BLK          }, /* FO FAN */
    /*0xC0*/ { L1_PHO_SAMPHAO, L2_BLANK, L3_BLANK, L4_BLK     }, /* PHO SAMPHAO */
    /*0xC1*/ { L1_MO_MA, L2_BLANK, L3_BLANK, L4_BLK           }, /* MO MA */
    /*0xC2*/ { L1_YO_YAK, L2_BLANK, L3_BLANK, L4_BLK          }, /* YO YAK */
    /*0xC3*/ { L1_RO_RUA, L2_BLANK, L3_BLANK, L4_BLK          }, /* RO RUA */
    /*0xC4*/ { L1_RU, L2_BLANK, L3_BLANK, L4_BLK              }, /* RU */
    /*0xC5*/ { L1_LO_LING, L2_BLANK, L3_BLANK, L4_BLK         }, /* LO LING */
    /*0xC6*/ { L1_LU, L2_BLANK, L3_BLANK, L4_BLK              }, /* LU */
    /*0xC7*/ { L1_WO_WAEN, L2_BLANK, L3_BLANK, L4_BLK         }, /* WO WAEN */
    /*0xC8*/ { L1_SO_SALA, L2_BLANK, L3_BLANK, L4_BLK         }, /* SO SALA */
    /*0xC9*/ { L1_SO_RUSI, L2_BLANK, L3_BLANK, L4_BLK         }, /* SO RUSI */
    /*0xCA*/ { L1_SO_SUA, L2_BLANK, L3_BLANK, L4_BLK          }, /* SO SUA */
    /*0xCB*/ { L1_HO_HIP, L2_BLANK, L3_BLANK, L4_BLK          }, /* HO HIP */
    /*0xCC*/ { L1_LO_CHULA, L2_BLANK, L3_BLANK, L4_BLK        }, /* LO CHULA */
    /*0xCD*/ { L1_O_ANG, L2_BLANK, L3_BLANK, L4_BLK           }, /* O ANG */
    /*0xCE*/ { L1_HO_NOKHUK, L2_BLANK, L3_BLANK, L4_BLK       }, /* HO NOKHUK */
    /*0xCF*/ { IGNORE, IGNORE, L3_PAIYAN_NOI, IGNORE     }, /* PAIYANNOI */
    /*0xD0*/ { L1_SARA_A, L2_BLANK, L3_BLANK, L4_BLK           }, /* SARA A */
    /*0xD1*/ { L1_MAI_HAN_AKAT, L2_BLANK, L3_BLANK, L4_BLK     }, /* MAI HAN-AKAT */
    /*0xD2*/ { L1_SARA_AA, L2_BLANK, L3_BLANK, L4_BLK          }, /* SARA AA */
    /*0xD3*/ { L1_SARA_AM, L2_BLANK, L3_BLANK, L4_BLK          }, /* SARA AM */
    /*0xD4*/ { L1_SARA_I, L2_BLANK, L3_BLANK, L4_BLK           }, /* SARA I */
    /*0xD5*/ { L1_SARA_II, L2_BLANK, L3_BLANK, L4_BLK          }, /* SARA II */
    /*0xD6*/ { L1_SARA_UE, L2_BLANK, L3_BLANK, L4_BLK          }, /* SARA UE */
    /*0xD7*/ { L1_SARA_UEE, L2_BLANK, L3_BLANK, L4_BLK         }, /* SARA UEE */
    /*0xD8*/ { L1_SARA_U, L2_BLANK, L3_BLANK, L4_BLK           }, /* SARA U */
    /*0xD9*/ { L1_SARA_UU, L2_BLANK, L3_BLANK, L4_BLK          }, /* SARA UU */
    /*0xDA*/ { IGNORE, L2_PINTU, L3_BLANK, L4_BLK  }, /* PHINTHU */
    /*0xDB*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0xDC*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0xDD*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0xDE*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0xDF*/ { IGNORE, IGNORE, L3_BAHT, IGNORE           }, /* BAHT */
    /*0xE0*/ { L1_SARA_E, L2_BLANK, L3_BLANK, L4_BLK           }, /* SARA E */
    /*0xE1*/ { L1_SARA_AE, L2_BLANK, L3_BLANK, L4_BLK          }, /* SARA AE */
    /*0xE2*/ { L1_SARA_O, L2_BLANK, L3_BLANK, L4_BLK           }, /* SARA O */
    /*0xE3*/ { L1_SARA_AI_MAIMUAN, L2_BLANK, L3_BLANK, L4_BLK  }, /* SARA AI MAIMUAN */
    /*0xE4*/ { L1_SARA_AI_MAIMALAI, L2_BLANK, L3_BLANK, L4_BLK }, /* SARA AI MAIMALAI */
    /*0xE5*/ { L1_SARA_AA, L2_BLANK, L3_BLANK, L4_EXT          }, /* LAKKHANG YAO */
    /*0xE6*/ { IGNORE, IGNORE, L3_MAI_YAMOK, IGNORE      }, /* MAIYAMOK */
    /*0xE7*/ { IGNORE, L2_TYKHU, L3_BLANK, L4_BLK  }, /* MAITAIKHU */
    /*0xE8*/ { IGNORE, L2_TONE1, L3_BLANK, L4_BLK  }, /* MAI EK */
    /*0xE9*/ { IGNORE, L2_TONE2, L3_BLANK, L4_BLK  }, /* MAI THO */
    /*0xEA*/ { IGNORE, L2_TONE3, L3_BLANK, L4_BLK  }, /* MAI TRI */
    /*0xEB*/ { IGNORE, L2_TONE4, L3_BLANK, L4_BLK  }, /* MAI CHATTAWA */
    /*0xEC*/ { IGNORE, L2_GARAN, L3_BLANK, L4_BLK  }, /* THANTHAKHAT */
    /*0xED*/ { L1_NKHIT, L2_BLANK, L3_BLANK, L4_BLK  }, /* NIKHAHIT */
    /*0xEE*/ { IGNORE, L2_YAMAK, L3_BLANK, L4_BLK  }, /* YAMAKKAN */
    /*0xEF*/ { IGNORE, IGNORE, L3_FONGMAN, IGNORE           }, /* FONGMAN */
    /*0xF0*/ { L1_08, L2_THAII, L3_BLANK, L4_BLK  }, /* THAI DIGIT ZERO */
    /*0xF1*/ { L1_18, L2_THAII, L3_BLANK, L4_BLK  }, /* THAI DIGIT ONE */
    /*0xF2*/ { L1_28, L2_THAII, L3_BLANK, L4_BLK  }, /* THAI DIGIT TWO */
    /*0xF3*/ { L1_38, L2_THAII, L3_BLANK, L4_BLK  }, /* THAI DIGIT THREE */
    /*0xF4*/ { L1_48, L2_THAII, L3_BLANK, L4_BLK  }, /* THAI DIGIT FOUR */
    /*0xF5*/ { L1_58, L2_THAII, L3_BLANK, L4_BLK  }, /* THAI DIGIT FIVE */
    /*0xF6*/ { L1_68, L2_THAII, L3_BLANK, L4_BLK  }, /* THAI DIGIT SIX */
    /*0xF7*/ { L1_78, L2_THAII, L3_BLANK, L4_BLK  }, /* THAI DIGIT SEVEN */
    /*0xF8*/ { L1_88, L2_THAII, L3_BLANK, L4_BLK  }, /* THAI DIGIT EIGHT */
    /*0xF9*/ { L1_98, L2_THAII, L3_BLANK, L4_BLK  }, /* THAI DIGIT NINE */
    /*0xFA*/ { IGNORE, IGNORE, L3_ANGKHANKHU, IGNORE }, /* ANGKHANKHU */
    /*0xFB*/ { IGNORE, IGNORE, L3_KHOMUT, IGNORE }, /* KHOMUT */
    /*0xFC*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0xFD*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0xFE*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
    /*0xFF*/ { IGNORE, IGNORE, IGNORE, IGNORE }, /* ***IGNORED*** */
};


thchar_t
th_char_weight_(thchar_t c, int level)
{
    if (0 <= level && level < TOT_LEVELS)
        return char_weight_tbl_[c][level];
    return IGNORE;
}

thchar_t
th_char_weight_delim_(int level)
{
    assert(0 <= level && level < TOT_LEVELS);
    return (thchar_t)(TOT_LEVELS - level);
}

/*
vi:ts=4:ai:expandtab
*/
