/* NECTEC THAI SOFTWARE STANDARD PROJECT 1989-1991
   FILE TIS.H
   This include file defines the names and character codes of
   (1) Standard ASCII control codes,
   (2) Thai Industrial Standard characters (ASCII TIS 620-2533),
   (3) Dot Matrix Printer Code Extension (TIS 988-2533),
   (4) WTT2.0 standard internal code extension for Hilo Byte 
       encoding
    The names are written as defined in the future announcement
    of ISO-/ECMA 8859-?? for Thailand.

    WRITTEN BY: THAWEESAK KOANANTAKOOL
    IPIED, THAMMASAT UNIVERSITY
    LAST UPDATE: 18 FEBRUARY 1991
*/

/* PART 1 - STANDARD ASCII CODES (ISO-646) */

#ifndef NULL
# define NULL                 0
#endif
#define NUL                  0
#define SOH                  1      /* 0x01 START OF HEADING */
#define STX                  2      /* 0x02 START OF TEXT */
#define ETX                  3      /* 0x03 END OF TEXT */
#define EOT                  4      /* 0x04 END OF TRANSMISSION */
#define ENQ                  5      /* 0x05 ENQUIRE */
#define ACK                  6      /* 0x06 ACKNOWLEDGE */
#define BEL                  7      /* 0x07 BELL */
#define BS                   8      /* 0x08 BACKSPACE */
#define HT                   9      /* 0x09 HORIZONTAL TAB */
#define LF                   10     /* 0x0A LINE FEED */
#define VT                   11     /* 0x0B VERTICAL TAB */
#define FF                   12     /* 0x0C FORM FEED */
#define CR                   13     /* 0x0D CARRIAGE RETURN */
#define SO                   14     /* 0x0E SHIFT OUT */
#define SI                   15     /* 0x0F SHIFT IN */
#define DLE                  16     /* 0x10 DATA LINK ESCAPE */
#define DC1                  17     /* 0x11 DEVICE CONTROL 1 */
#define XON                  DC1    /* 0x11 X-ON */
#define DC2                  18     /* 0x12 DEVICE CONTROL 2 */
#define DC3                  19     /* 0x13 DEVICE CONTROL 3 */
#define XOFF                 DC3    /* 0x13 X-OFF */
#define DC4                  20     /* 0x14 DEVICE CONTROL 4 */
#define NAK                  21     /* 0x15 NEGATIVE ACKNOWLEDGE */
#define SYN                  22     /* 0x16 SYNCHRONOUS IDLE */
#define ETB                  23     /* 0x17 END OF TRANSMISSION BLOCK */
#define CAN                  24     /* 0x18 CANCEL */
#define EM                   25     /* 0x19 END OF MEDIUM */
#define SUB                  26     /* 0x1A SUBSTITUTE CHARACTER */
#define ESC                  27     /* 0x1B ESCAPE */
#define FS                   28     /* 0x1C FILE SEPARATOR */
#define GS                   29     /* 0x1D GROUP SEPARATOR */
#define RS                   30     /* 0x1E RECORD SEPARATOR */
#define US                   31     /* 0x1F UNIT SEPARATOR */
#define IS4                  28     /* 0x1C INFORMATION SEPARATOR 4 */
#define IS3                  29     /* 0x1D INFORMATION SEPARATOR 3 */
#define IS2                  30     /* 0x1E INFORMATION SEPARATOR 2 */
#define IS1                  31     /* 0x1F INFORMATION SEPARATOR 1 */
#define SP                   32     /* 0x20 SPACE */
#define DEL                  127    /* 0x7F DELETE */

/* PART 2 - THAI INDUSTRIAL STANDARD -- TIS 620-2529(1986)
NAMING CONVENTION AS TISO PROPOSED TO ISO/ECMA FOR
DRAFT ISO-8859-xx FOR THAILAND.
UPDATED 18 FEB 91 ACCORDING TO TC536 RESOLUTION
*/

#define KOKAI                161    /* ¡  0xA1 */
#define KHOKHAI              162    /* ¢  0xA2 */
#define KHOKHUAT             163    /* £  0xA3 */
#define KHOKHWAI             164    /* ¤  0xA4 */
#define KHOKHON              165    /* ¥  0xA5 */
#define KHORAKHANG           166    /* ¦  0xA6 */
#define NGONGU               167    /* §  0xA7 */
#define CHOCHAN              168    /* ¨  0xA8 */
#define CHOCHING             169    /* ©  0xA9 */
#define CHOCHANG             170    /* ª  0xAA */
#define SOSO                 171    /* «  0xAB */
#define CHOCHOE              172    /* ¬  0xAC */
#define YOYING               173    /* ­  0xAD */
#define DOCHADA              174    /* ®  0xAE */
#define TOPATAK              175    /* ¯  0xAF */
#define THOTHAN              176    /* °  0xB0 */
#define THONANGMONTHO        177    /* ±  0xB1 */
#define THOPHUTHAO           178    /* ²  0xB2 */
#define NONEN                179    /* ³  0xB3 */
#define DODEK                180    /* ´  0xB4 */
#define TOTAO                181    /* µ  0xB5 */
#define THOTHUNG             182    /* ¶  0xB6 */
#define THOTHAHAN            183    /* ·  0xB7 */
#define THOTHONG             184    /* ¸  0xB8 */
#define NONU                 185    /* ¹  0xB9 */
#define BOBAIMAI             186    /* º  0xBA */
#define POPLA                187    /* »  0xBB */
#define PHOPUENG             188    /* ¼  0xBC */
#define FOFA                 189    /* ½  0xBD */
#define PHOPHAN              190    /* ¾  0xBE */
#define FOFAN                191    /* ¿  0xBF */
#define PHOSAMPHAO           192    /* À  0xC0 */
#define MOMA                 193    /* Á  0xC1 */
#define YOYAK                194    /* Â  0xC2 */
#define RORUA                195    /* Ã  0xC3 */
#define RU                   196    /* Ä  0xC4 */
#define LOLING               197    /* Å  0xC5 */
#define LU                   198    /* Æ  0xC6 */
#define WOWAEN               199    /* Ç  0xC7 */
#define SOSALA               200    /* È  0xC8 */
#define SORUSI               201    /* É  0xC9 */
#define SOSUA                202    /* Ê  0xCA */
#define HOHIP                203    /* Ë  0xCB */
#define LOCHULA              204    /* Ì  0xCC */
#define OANG                 205    /* Í  0xCD */
#define HONOKHUK             206    /* Î  0xCE */
#define PAIYANNOI            207    /* Ï  0xCF */
#define SARA_A               208    /* Ð  0xD0 */
#define MAIHUNAKAT           209    /* Ñ  0xD1 */
#define SARA_AA              210    /* Ò  0xD2 */
#define SARA_AM              211    /* Ó  0xD3 */
#define SARA_I               212    /* Ô  0xD4 */
#define SARA_II              213    /* Õ  0xD5 */
#define SARA_UE              214    /* Ö  0xD6 */
#define SARA_UEE             215    /* ×  0xD7 */
#define SARA_U               216    /* Ø  0xD8 */
#define SARA_UU              217    /* Ù  0xD9 */
#define PHINTHU              218    /* Ú  0xDA */
#define BAHT                 223    /* ß  0xDF */
#define SARA_E               224    /* à  0xE0 */
#define SARA_AE              225    /* á  0xE1 */
#define SARA_O               226    /* â  0xE2 */
#define MAIMUAN              227    /* ã  0xE3 */
#define MAIMALAI             228    /* ä  0xE4 */
#define LAKKHANGYAO          229    /* å  0xE5 */
#define MAIYAMOK             230    /* æ  0xE6 */
#define MAITAIKHU            231    /* ç  0xE7 */
#define MAIEK                232    /* è  0xE8 */
#define MAITHO               233    /* é  0xE9 */
#define MAITRI               234    /* ê  0xEA */
#define MAICHATTAWA          235    /* ë  0xEB */
#define THANTHAKHAT          236    /* ì  0xEC */
#define NIKHAHIT             237    /* í  0xED */
#define YAMAKKAN             238    /* î  0xEE */
#define FONGMAN              239    /* ï  0xEF */
#define THAIZERO             240    /* ð  0xF0 */
#define THAIONE              241    /* ñ  0xF1 */
#define THAITWO              242    /* ò  0xF2 */
#define THAITHREE            243    /* ó  0xF3 */
#define THAIFOUR             244    /* ô  0xF4 */
#define THAIFIVE             245    /* õ  0xF5 */
#define THAISIX              246    /* ö  0xF6 */
#define THAISEVEN            247    /* ÷  0xF7 */
#define THAIEIGHT            248    /* ø  0xF8 */
#define THAININE             249    /* ù  0xF9 */
#define ANGKHANKHU           250    /* ú  0xFA */
#define KHOMUT               251    /* û  0xFB */

/* PART 3 -THAI INDUSTRIAL STANDARD EXTENDED FOR PRINTER */
/* TIS 988-2533 */

#define MAIHUNAKAT_EK       0x80    /* TIS 988-2533 */
#define SARA_I_EK           0x84    /* TIS 988-2533 */
#define SARA_I_THANTHAKHAT  0x88    /* TIS 988-2533 */
#define SARA_II_EK          0x89    /* TIS 988-2533 */
#define SARA_UE_EK          0x8D    /* TIS 988-2533 */
#define SARA_UEE_EK         0x91    /* TIS 988-2533 */

#define PR_UM_EK            0x95    /* TIS 988-2533 */
#define PR_BOTTOM_O         0xDB    /* TIS 988-2533 */
#define PR_TOP_O            0xDC    /* TIS 988-2533 */
#define PR_TOP_MAIMUAN      0xDD    /* TIS 988-2533 */
#define PR_TOP_MAIMALAI     0xDE    /* TIS 988-2533 */


/* PART 4 - WTT 2.0 Hilo Byte Encoding */
/* Revision 3 Certified by TAPIC on March 27 1991 */

enum HiloByte {
  HSPLCE=0xB0,HEK,HTHO,HTRI,HCHATTAWA,HTHANTHAKHAT,HNIKHAHIT,HTAIKHU,
  HU=0xB8,HU_EK,HU_THO,HU_TRI,HU_CHATTAWA,HU_THANTHAKHAT,HU_NUKHAHIT,
  HUU=0xC0, HUU_EK, HUU_THO, HUU_TRI, HUU_CHATTAWA,
  HPHINTHU=0xC8,
  HHUNAKAT=0xD0,HHUNAKAT_EK, HHUNAKAT_THO, HHUNAKAT_TRI,
    HHUNAKAT_CHATTAWA,
  HI=0xD8,HI_EK,HI_THO,HI_TRI,HI_CHATTAWA,
    HI_THANTHAKHAT,HI_NIKHAHIT,
  HII=0xE0, HII_EK,HII_THO,HII_TRI,HII_CHATTAWA,
  HII_TAIKHU=0xE7,
  HUE=0xE8, HUE_EK,HUE_THO,HUE_TRI,HUE_CHATTAWA,
  HUEE=0xF0, HUEE_EK,HUEE_THO,HUEE_TRI,HUEE_CHATTAWA,
  HUEE_TAIKHU=0xF7,
  HYAMAKKAN=0xF8
};

/* Allow use of the symbol KARAN in place of THANTHAKHAT */
#define KARAN                THANTHAKHAT
#define HKARAN               HTHAKANTHAKHAT
#define HU_KARAN             HU_THAKANTHAKHAT
#define HI_KARAN             HI_THAKANTHAKHAT

/*------------- END OF TIS.H -------------*/

