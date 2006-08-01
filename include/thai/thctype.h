/*
 * $Id: thctype.h,v 1.11 2006-08-01 06:26:32 thep Exp $
 * thctype.h - Thai character classifications
 * Created: 2001-05-17
 * Author:  Theppitak Karoonboonyanan <thep@links.nectec.or.th>
 */

#ifndef THAI_THCTYPE_H
#define THAI_THCTYPE_H

#include <thai/thailib.h>

BEGIN_CDECL

/**
 * @file   thctype.h
 * @brief  Thai character classifications
 *
 * The Thai Standard Industrial Standards Institute (TIS) defined the Thai 
 * character set for using with computer named TIS-620. This character set is 
 * 8-bit encoded including both English and Thai characters. Aliases of 
 * TIS-620 are TIS620, TIS620-0, TIS620.2529-1, TIS620.2533-0 and ISO-IR-166.
 *
 * The followings are the enconding values in hexadecimal, unicode values and 
 * their names.
 *
 * <pre>
 * 0x00   <U0000> NULL (NUL)                                       
 * 0x01   <U0001> START OF HEADING (SOH)                           
 * 0x02   <U0002> START OF TEXT (STX)                              
 * 0x03   <U0003> END OF TEXT (ETX)                                
 * 0x04   <U0004> END OF TRANSMISSION (EOT)                        
 * 0x05   <U0005> ENQUIRY (ENQ)                                    
 * 0x06   <U0006> ACKNOWLEDGE (ACK)                                
 * 0x07   <U0007> BELL (BEL)                                       
 * 0x08   <U0008> BACKSPACE (BS)                                   
 * 0x09   <U0009> CHARACTER TABULATION (HT)                        
 * 0x0A   <U000A> LINE FEED (LF)                                   
 * 0x0B   <U000B> LINE TABULATION (VT)                             
 * 0x0C   <U000C> FORM FEED (FF)                                   
 * 0x0D   <U000D> CARRIAGE RETURN (CR)                             
 * 0x0E   <U000E> SHIFT OUT (SO)                                   
 * 0x0F   <U000F> SHIFT IN (SI)                                    
 * 0x10   <U0010> DATALINK ESCAPE (DLE)                            
 * 0x11   <U0011> DEVICE CONTROL ONE (DC1)                         
 * 0x12   <U0012> DEVICE CONTROL TWO (DC2)                         
 * 0x13   <U0013> DEVICE CONTROL THREE (DC3)                       
 * 0x14   <U0014> DEVICE CONTROL FOUR (DC4)                        
 * 0x15   <U0015> NEGATIVE ACKNOWLEDGE (NAK)                       
 * 0x16   <U0016> SYNCHRONOUS IDLE (SYN)                           
 * 0x17   <U0017> END OF TRANSMISSION BLOCK (ETB)                  
 * 0x18   <U0018> CANCEL (CAN)                                     
 * 0x19   <U0019> END OF MEDIUM (EM)                               
 * 0x1A   <U001A> SUBSTITUTE (SUB)                                 
 * 0x1B   <U001B> ESCAPE (ESC)                                     
 * 0x1C   <U001C> FILE SEPARATOR (IS4)                             
 * 0x1D   <U001D> GROUP SEPARATOR (IS3)                            
 * 0x1E   <U001E> RECORD SEPARATOR (IS2)                           
 * 0x1F   <U001F> UNIT SEPARATOR (IS1)                             
 * 0x20   <U0020> SPACE                                            
 * 0x21   <U0021> EXCLAMATION MARK                                 
 * 0x22   <U0022> QUOTATION MARK                                   
 * 0x23   <U0023> NUMBER SIGN                                      
 * 0x24   <U0024> DOLLAR SIGN                                      
 * 0x25   <U0025> PERCENT SIGN                                     
 * 0x26   <U0026> AMPERSAND                                        
 * 0x27   <U0027> APOSTROPHE                                       
 * 0x28   <U0028> LEFT PARENTHESIS                                 
 * 0x29   <U0029> RIGHT PARENTHESIS                                
 * 0x2A   <U002A> ASTERISK                                         
 * 0x2B   <U002B> PLUS SIGN                                        
 * 0x2C   <U002C> COMMA                                            
 * 0x2D   <U002D> HYPHEN-MINUS                                     
 * 0x2E   <U002E> FULL STOP                                        
 * 0x2F   <U002F> SOLIDUS                                          
 * 0x30   <U0030> DIGIT ZERO                                       
 * 0x31   <U0031> DIGIT ONE                                        
 * 0x32   <U0032> DIGIT TWO                                        
 * 0x33   <U0033> DIGIT THREE                                      
 * 0x34   <U0034> DIGIT FOUR                                       
 * 0x35   <U0035> DIGIT FIVE                                       
 * 0x36   <U0036> DIGIT SIX                                        
 * 0x37   <U0037> DIGIT SEVEN                                      
 * 0x38   <U0038> DIGIT EIGHT                                      
 * 0x39   <U0039> DIGIT NINE                                       
 * 0x3A   <U003A> COLON                                            
 * 0x3B   <U003B> SEMICOLON                                        
 * 0x3C   <U003C> LESS-THAN SIGN                                   
 * 0x3D   <U003D> EQUALS SIGN                                      
 * 0x3E   <U003E> GREATER-THAN SIGN                                
 * 0x3F   <U003F> QUESTION MARK                                    
 * 0x40   <U0040> COMMERCIAL AT                                    
 * 0x41   <U0041> LATIN CAPITAL LETTER A                           
 * 0x42   <U0042> LATIN CAPITAL LETTER B                           
 * 0x43   <U0043> LATIN CAPITAL LETTER C                           
 * 0x44   <U0044> LATIN CAPITAL LETTER D                           
 * 0x45   <U0045> LATIN CAPITAL LETTER E                           
 * 0x46   <U0046> LATIN CAPITAL LETTER F                           
 * 0x47   <U0047> LATIN CAPITAL LETTER G                           
 * 0x48   <U0048> LATIN CAPITAL LETTER H                           
 * 0x49   <U0049> LATIN CAPITAL LETTER I                           
 * 0x4A   <U004A> LATIN CAPITAL LETTER J                           
 * 0x4B   <U004B> LATIN CAPITAL LETTER K                           
 * 0x4C   <U004C> LATIN CAPITAL LETTER L                           
 * 0x4D   <U004D> LATIN CAPITAL LETTER M                           
 * 0x4E   <U004E> LATIN CAPITAL LETTER N                           
 * 0x4F   <U004F> LATIN CAPITAL LETTER O                           
 * 0x50   <U0050> LATIN CAPITAL LETTER P                           
 * 0x51   <U0051> LATIN CAPITAL LETTER Q                           
 * 0x52   <U0052> LATIN CAPITAL LETTER R                           
 * 0x53   <U0053> LATIN CAPITAL LETTER S                           
 * 0x54   <U0054> LATIN CAPITAL LETTER T                           
 * 0x55   <U0055> LATIN CAPITAL LETTER U                           
 * 0x56   <U0056> LATIN CAPITAL LETTER V                           
 * 0x57   <U0057> LATIN CAPITAL LETTER W                           
 * 0x58   <U0058> LATIN CAPITAL LETTER X                           
 * 0x59   <U0059> LATIN CAPITAL LETTER Y                           
 * 0x5A   <U005A> LATIN CAPITAL LETTER Z                           
 * 0x5B   <U005B> LEFT SQUARE BRACKET                              
 * 0x5C   <U005C> REVERSE SOLIDUS                                  
 * 0x5D   <U005D> RIGHT SQUARE BRACKET                             
 * 0x5E   <U005E> CIRCUMFLEX ACCENT                                
 * 0x5F   <U005F> LOW LINE                                         
 * 0x60   <U0060> GRAVE ACCENT                                     
 * 0x61   <U0061> LATIN SMALL LETTER A                             
 * 0x62   <U0062> LATIN SMALL LETTER B                             
 * 0x63   <U0063> LATIN SMALL LETTER C                             
 * 0x64   <U0064> LATIN SMALL LETTER D                             
 * 0x65   <U0065> LATIN SMALL LETTER E                             
 * 0x66   <U0066> LATIN SMALL LETTER F                             
 * 0x67   <U0067> LATIN SMALL LETTER G                             
 * 0x68   <U0068> LATIN SMALL LETTER H                             
 * 0x69   <U0069> LATIN SMALL LETTER I                             
 * 0x6A   <U006A> LATIN SMALL LETTER J                             
 * 0x6B   <U006B> LATIN SMALL LETTER K                             
 * 0x6C   <U006C> LATIN SMALL LETTER L                             
 * 0x6D   <U006D> LATIN SMALL LETTER M                             
 * 0x6E   <U006E> LATIN SMALL LETTER N                             
 * 0x6F   <U006F> LATIN SMALL LETTER O                             
 * 0x70   <U0070> LATIN SMALL LETTER P                             
 * 0x71   <U0071> LATIN SMALL LETTER Q                             
 * 0x72   <U0072> LATIN SMALL LETTER R                             
 * 0x73   <U0073> LATIN SMALL LETTER S                             
 * 0x74   <U0074> LATIN SMALL LETTER T                             
 * 0x75   <U0075> LATIN SMALL LETTER U                             
 * 0x76   <U0076> LATIN SMALL LETTER V                             
 * 0x77   <U0077> LATIN SMALL LETTER W                             
 * 0x78   <U0078> LATIN SMALL LETTER X                             
 * 0x79   <U0079> LATIN SMALL LETTER Y                             
 * 0x7A   <U007A> LATIN SMALL LETTER Z                             
 * 0x7B   <U007B> LEFT CURLY BRACKET                               
 * 0x7C   <U007C> VERTICAL LINE                                    
 * 0x7D   <U007D> RIGHT CURLY BRACKET                              
 * 0x7E   <U007E> TILDE                                            
 * 0x7F   <U007F> DELETE (DEL)                                     
 * 0xA1   <U0E01> THAI CHARACTER KO KAI                            
 * 0xA2   <U0E02> THAI CHARACTER KHO KHAI                          
 * 0xA3   <U0E03> THAI CHARACTER KHO KHUAT                         
 * 0xA4   <U0E04> THAI CHARACTER KHO KHWAI                         
 * 0xA5   <U0E05> THAI CHARACTER KHO KHON                          
 * 0xA6   <U0E06> THAI CHARACTER KHO RAKHANG                       
 * 0xA7   <U0E07> THAI CHARACTER NGO NGU                           
 * 0xA8   <U0E08> THAI CHARACTER CHO CHAN                          
 * 0xA9   <U0E09> THAI CHARACTER CHO CHING                         
 * 0xAA   <U0E0A> THAI CHARACTER CHO CHANG                         
 * 0xAB   <U0E0B> THAI CHARACTER SO SO                             
 * 0xAC   <U0E0C> THAI CHARACTER CHO CHOE                          
 * 0xAD   <U0E0D> THAI CHARACTER YO YING                           
 * 0xAE   <U0E0E> THAI CHARACTER DO CHADA                          
 * 0xAF   <U0E0F> THAI CHARACTER TO PATAK                          
 * 0xB0   <U0E10> THAI CHARACTER THO THAN                          
 * 0xB1   <U0E11> THAI CHARACTER THO NANGMONTHO                    
 * 0xB2   <U0E12> THAI CHARACTER THO PHUTHAO                       
 * 0xB3   <U0E13> THAI CHARACTER NO NEN                            
 * 0xB4   <U0E14> THAI CHARACTER DO DEK                            
 * 0xB5   <U0E15> THAI CHARACTER TO TAO                            
 * 0xB6   <U0E16> THAI CHARACTER THO THUNG                         
 * 0xB7   <U0E17> THAI CHARACTER THO THAHAN                        
 * 0xB8   <U0E18> THAI CHARACTER THO THONG                         
 * 0xB9   <U0E19> THAI CHARACTER NO NU                             
 * 0xBA   <U0E1A> THAI CHARACTER BO BAIMAI                         
 * 0xBB   <U0E1B> THAI CHARACTER PO PLA                            
 * 0xBC   <U0E1C> THAI CHARACTER PHO PHUNG                         
 * 0xBD   <U0E1D> THAI CHARACTER FO FA                             
 * 0xBE   <U0E1E> THAI CHARACTER PHO PHAN                          
 * 0xBF   <U0E1F> THAI CHARACTER FO FAN                            
 * 0xC0   <U0E20> THAI CHARACTER PHO SAMPHAO                       
 * 0xC1   <U0E21> THAI CHARACTER MO MA                             
 * 0xC2   <U0E22> THAI CHARACTER YO YAK                            
 * 0xC3   <U0E23> THAI CHARACTER RO RUA                            
 * 0xC4   <U0E24> THAI CHARACTER RU                                
 * 0xC5   <U0E25> THAI CHARACTER LO LING                           
 * 0xC6   <U0E26> THAI CHARACTER LU                                
 * 0xC7   <U0E27> THAI CHARACTER WO WAEN                           
 * 0xC8   <U0E28> THAI CHARACTER SO SALA                           
 * 0xC9   <U0E29> THAI CHARACTER SO RUSI                           
 * 0xCA   <U0E2A> THAI CHARACTER SO SUA                            
 * 0xCB   <U0E2B> THAI CHARACTER HO HIP                            
 * 0xCC   <U0E2C> THAI CHARACTER LO CHULA                          
 * 0xCD   <U0E2D> THAI CHARACTER O ANG                             
 * 0xCE   <U0E2E> THAI CHARACTER HO NOKHUK                         
 * 0xCF   <U0E2F> THAI CHARACTER PAIYANNOI                         
 * 0xD0   <U0E30> THAI CHARACTER SARA A                            
 * 0xD1   <U0E31> THAI CHARACTER MAI HAN-AKAT                      
 * 0xD2   <U0E32> THAI CHARACTER SARA AA                           
 * 0xD3   <U0E33> THAI CHARACTER SARA AM                           
 * 0xD4   <U0E34> THAI CHARACTER SARA I                            
 * 0xD5   <U0E35> THAI CHARACTER SARA II                           
 * 0xD6   <U0E36> THAI CHARACTER SARA UE                           
 * 0xD7   <U0E37> THAI CHARACTER SARA UEE                          
 * 0xD8   <U0E38> THAI CHARACTER SARA U                            
 * 0xD9   <U0E39> THAI CHARACTER SARA UU                           
 * 0xDA   <U0E3A> THAI CHARACTER PHINTHU                           
 * 0xDF   <U0E3F> THAI CHARACTER SYMBOL BAHT                       
 * 0xE0   <U0E40> THAI CHARACTER SARA E                            
 * 0xE1   <U0E41> THAI CHARACTER SARA AE                           
 * 0xE2   <U0E42> THAI CHARACTER SARA O                            
 * 0xE3   <U0E43> THAI CHARACTER SARA AI MAIMUAN                   
 * 0xE4   <U0E44> THAI CHARACTER SARA AI MAIMALAI                  
 * 0xE5   <U0E45> THAI CHARACTER LAKKHANGYAO                       
 * 0xE6   <U0E46> THAI CHARACTER MAIYAMOK                          
 * 0xE7   <U0E47> THAI CHARACTER MAITAIKHU                         
 * 0xE8   <U0E48> THAI CHARACTER MAI EK                            
 * 0xE9   <U0E49> THAI CHARACTER MAI THO                           
 * 0xEA   <U0E4A> THAI CHARACTER MAI TRI                           
 * 0xEB   <U0E4B> THAI CHARACTER MAI CHATTAWA                      
 * 0xEC   <U0E4C> THAI CHARACTER THANTHAKHAT                       
 * 0xED   <U0E4D> THAI CHARACTER NIKHAHIT                          
 * 0xEE   <U0E4E> THAI CHARACTER YAMAKKAN                          
 * 0xEF   <U0E4F> THAI CHARACTER FONGMAN                           
 * 0xF0   <U0E50> THAI DIGIT ZERO                                  
 * 0xF1   <U0E51> THAI DIGIT ONE                                   
 * 0xF2   <U0E52> THAI DIGIT TWO                                   
 * 0xF3   <U0E53> THAI DIGIT THREE                                 
 * 0xF4   <U0E54> THAI DIGIT FOUR                                  
 * 0xF5   <U0E55> THAI DIGIT FIVE                                  
 * 0xF6   <U0E56> THAI DIGIT SIX                                   
 * 0xF7   <U0E57> THAI DIGIT SEVEN                                 
 * 0xF8   <U0E58> THAI DIGIT EIGHT                                 
 * 0xF9   <U0E59> THAI DIGIT NINE                                  
 * 0xFA   <U0E5A> THAI CHARACTER ANGKHANKHU                        
 * 0xFB   <U0E5B> THAI CHARACTER KHOMUT
 * </pre>
 *
 * Thai characters consist of 44 consonants, vowels, tonemarks, diacritics and 
 * Thai digits. Thai vowels are divided into 4 groups, Leading Vowels (LV), 
 * Following Vowels (FV), Below Vowels (BV) and Above Vowels (AV). There are 4 
 * tonemarks whose position is above a consonant. Diacritics are divided into 
 * 2 groups, Above Diacritics (AD) and Below Diacritics (BD).
 *
 * @subsection CharLevel Character Level
 *
 * Libthai has defined 4 levels for the posotion of a character.
 *
 *   @li  Below level: a character is placed below the consonant. 
 *        th_chlevel() will return the value -1 for these characters. 
 *
 *   @li  Base level: this includes consonants, FV and LV. A character is 
 *        placed on baseline. 
 *        th_chlevel() will return the value 0 for these characters.
 *
 *   @li  Above level: a character is placed just above the consonant.
 *        th_chlevel() will return the value 1 for these characters.
 *
 *   @li  Top level: this includes tonemarks and diacritics. Sometimes, a 
 *        character in top level can be placed in above level if no character 
 *        is there, for better looking.
 *        th_chlevel() will return the value 2 for these characters.
 *
 * The following figure illustrates a Thai word and characters' level.
 *
 * <pre>
 * --------------------------- Top(2) 
 * ------*-------------------- Top(2) 
 * ------*-------------------- Top(2) 
 * <b>---------------------------</b>
 * --------------------------- Above(1)
 * ------*---------------*---- Above(1)
 * ---****---------------*---- Above(1)
 * --------------------------- Above(1)
 * <b>---------------------------</b>
 * --------------------------- Base(0) 
 * --*---*----***-----*--*---- Base(0) 
 * -*-*-*-*--*---*---*-*-*---- Base(0) 
 * --**-*-*------*---**--*---- Base(0) 
 * ---**--*---*--*---*---*---- Base(0) 
 * ---**--*--*-*-*----*--*---- Base(0) 
 * ---*---*--**--*---*---*---- Base(0) 
 * ---*---*--*---*---*---*---- Base(0) 
 * ---*---*--*****---*****---- Base(0) 
 * <b>--------------------------- Baseline</b>
 * --------------------------- Below(-1)
 * -------------------**-*---- Below(-1)
 * --------------------***---- Below(-1)
 * --------------------------- Below(-1)
 * </pre>
 *
 * A character placed at below, above or top level is also called dead 
 * character. It is usually combined with a consonant, after a dead character 
 * is typed, the cursor will not be advanced to the next display cell. BV, BD, 
 * TONE, AD and AV are classified as dead character.
 */

/**
 * @brief  Is the character a valid TIS-620 code?
 *
 * TIS-620 here means US-ASCII plus TIS-620 extension. Character codes
 * in CR area (0x80-0x9f), non-breaking space (0xa0), code gap range
 * (0xdb-0xde and 0xfc-0xff) are excluded.
 */
extern int th_istis(thchar_t c);

/**
 * @brief  Is the character a Thai character?
 */
extern int th_isthai(thchar_t c);
/**
 * @brief  Is the character an English character?
 */
extern int th_iseng(thchar_t c);

/* Thai letter classification */
/**
 * @brief  Is the character a Thai consonant?
 */
extern int th_isthcons(thchar_t c);
/**
 * @brief  Is the character a Thai vowel?
 */
extern int th_isthvowel(thchar_t c);
/**
 * @brief  Is the character a Thai tone mark?
 */
extern int th_isthtone(thchar_t c);
/**
 * @brief  Is the character a Thai diacritic?
 */
extern int th_isthdiac(thchar_t c);
/**
 * @brief  Is the character a Thai digit?
 */
extern int th_isthdigit(thchar_t c);
/**
 * @brief  Is the character a Thai punctuation?
 */
extern int th_isthpunct(thchar_t c);

/* Thai consonant shapes classification */
/**
 * @brief  Is the character a Thai consonant that fits the x-height?
 */
extern int th_istaillesscons(thchar_t c);
/**
 * @brief  Is the character a Thai consonant with stem above ascender?
 */
extern int th_isovershootcons(thchar_t c);
/**
 * @brief  Is the character a Thai consonant with stem below baseline?
 */
extern int th_isundershootcons(thchar_t c);
/**
 * @brief  Is the character a Thai consonant with split part below baseline?
 */
extern int th_isundersplitcons(thchar_t c);

/* Thai vowel classification */
/**
 * @brief  Is the character a Thai leading vowel?
 */
extern int th_isldvowel(thchar_t c);
/**
 * @brief  Is the character a Thai following vowel?
 */
extern int th_isflvowel(thchar_t c);
/**
 * @brief  Is the character a Thai upper vowel?
 */
extern int th_isupvowel(thchar_t c);
/**
 * @brief  Is the character a Thai below vowel?
 */
extern int th_isblvowel(thchar_t c);

/**
 * @brief  Position for rendering:
 *   @li   3 = above/top
 *   @li   2 = top
 *   @li   1 = above
 *   @li   0 = base
 *   @li  -1 = below
 */
extern int th_chlevel(thchar_t c);

/**
 * @brief  Is the character a combining character?
 */
extern int th_iscombchar(thchar_t c);

/*
 * implementation parts
 */
#include <ctype.h>
#define _th_ISbit(bit)  (1 << (bit))
#define _th_bitfld(base, val)  ((val) << (base))
#define _th_bitmsk(base, bits) (~((~(unsigned short)0) << (bits)) << (base))

enum {
  _th_IStis   = _th_ISbit(0),        /* TIS-620 char */

  _th_IScons  = _th_ISbit(1),        /* Thai consonant */
  _th_CClassMsk = _th_bitmsk(1, 3),  /*   Thai consonant shape masks */
  _th_CCtailless   = _th_bitfld(2, 0)|_th_IScons,   /* tailless cons */
  _th_CCovershoot  = _th_bitfld(2, 1)|_th_IScons,   /* overshoot cons */
  _th_CCundershoot = _th_bitfld(2, 2)|_th_IScons,   /* undershoot cons */
  _th_CCundersplit = _th_bitfld(2, 3)|_th_IScons,   /* undersplit cons */
  _th_ISvowel = _th_ISbit(4),        /* Thai vowel */
  _th_VClassMsk = _th_bitmsk(4, 3),  /*   Thai vowel class masks */
  _th_VCflvowel = _th_bitfld(5, 0)|_th_ISvowel,  /*   Thai following vowel */
  _th_VCldvowel = _th_bitfld(5, 1)|_th_ISvowel,  /*   Thai leading vowel */
  _th_VCupvowel = _th_bitfld(5, 2)|_th_ISvowel,  /*   Thai upper vowel */
  _th_VCblvowel = _th_bitfld(5, 3)|_th_ISvowel,  /*   Thai below vowel */
  _th_IStone  = _th_ISbit(7),        /* Thai tone mark */
  _th_ISdiac  = _th_ISbit(8),        /* Thai diacritic */
  _th_ISdigit = _th_ISbit(9),        /* digit */
  _th_ISpunct = _th_ISbit(10)        /* punctuation */
};

extern const unsigned short _th_ctype_tbl[];

#define _th_isctype(c, type)      (_th_ctype_tbl[c] & (type))
#define _th_isbits(c, mask, val)  ((_th_ctype_tbl[c] & (mask)) == (val))

#define th_istis(c)         _th_isctype((c), _th_IStis)

#define th_isthai(c)        (th_istis(c) && ((c) & 0x80))
#define th_iseng(c)         isascii(c)

/* Thai letter classification */
#define th_isthcons(c)      _th_isctype((c), _th_IScons)
#define th_isthvowel(c)     _th_isctype((c), _th_ISvowel)
#define th_isthtone(c)      _th_isctype((c), _th_IStone)
#define th_isthdiac(c)      _th_isctype((c), _th_ISdiac)
#define th_isthdigit(c)     _th_isctype((c), _th_ISdigit)
#define th_isthpunct(c)     _th_isctype((c), _th_ISpunct)

/* Thai consonant shapes classification */
#define th_istaillesscons(c)   _th_isbits((c), _th_CClassMsk, _th_CCtailless)
#define th_isovershootcons(c)  _th_isbits((c), _th_CClassMsk, _th_CCovershoot)
#define th_isundershootcons(c) _th_isbits((c), _th_CClassMsk, _th_CCundershoot)
#define th_isundersplitcons(c) _th_isbits((c), _th_CClassMsk, _th_CCundersplit)

/* Thai vowel classification */
#define th_isldvowel(c)     _th_isbits((c), _th_VClassMsk, _th_VCldvowel)
#define th_isflvowel(c)     _th_isbits((c), _th_VClassMsk, _th_VCflvowel)
#define th_isupvowel(c)     _th_isbits((c), _th_VClassMsk, _th_VCupvowel)
#define th_isblvowel(c)     _th_isbits((c), _th_VClassMsk, _th_VCblvowel)

extern const int            _th_chlevel_tbl[];

#define th_chlevel(c)       (_th_chlevel_tbl[c])
#define th_iscombchar(c)    (th_chlevel(c) != 0)

END_CDECL

#endif  /* THAI_THCTYPE_H */

