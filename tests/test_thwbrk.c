/* Test driver for thwbrk 
 *
 * $Id: test_thwbrk.c,v 1.2 2001-07-31 15:03:06 thep Exp $
 */

#define MAXLINELENGTH 1000

#include <stdio.h>
#include <stdlib.h>
#include <thai/thbrk.h>
#include <thai/thwchar.h>
#include <thai/thwbrk.h>
#include <wchar.h>

int main (int argc, char* argv[]) {
  

  thchar_t _retval[MAXLINELENGTH], _str[MAXLINELENGTH];
  thwchar_t _ustr[MAXLINELENGTH], uout[MAXLINELENGTH], unicodeCutCode[6];
  thchar_t *str, *retval;
  thwchar_t *ustr;

  unsigned char out1[MAXLINELENGTH];
  unsigned char out2[MAXLINELENGTH];
  int pos[MAXLINELENGTH];
  int outputLength, unicodeCutCodeLength;
  int numCut, i;
  
  str = _str;
  ustr = _ustr;
  retval = _retval;

  strcpy(str,"สวัสดีครับ นี่เป็นการทดสอบตัวเอง");
  printf ("Testing with input string: %s\n",str);

  printf ("Converting to Unicode...\n");
  th_tis2uni_line(str, ustr,MAXLINELENGTH);

  printf ("Calling th_wbrk()...\n");
  numCut = th_wbrk(ustr,pos,MAXLINELENGTH);

  printf ("Total %d cut points.", numCut);
  if ( numCut > 0 ) { 
    printf("Cut points list: %d", pos[0]);
    for ( i = 1 ; i < numCut ; i++ ) {
      printf(", %d", pos[i]);
    }
  }
  printf("\n");
  if ( numCut != 7 ) { 
    printf("Error! Should have 7 cut points.\n Test th_wbrk() failed...\n");
    exit (-1);
  }
	
  unicodeCutCodeLength = th_tis2uni_line("<WBR>", (thwchar_t*) unicodeCutCode, 6);

  printf("Calling th_wbrk_line() ....\n");
  outputLength = th_wbrk_line(ustr, (thwchar_t*) uout,MAXLINELENGTH, unicodeCutCode);

  printf("Return value from th_wbrk_line is %d\n", outputLength);
  printf("Output string length is %d\n", wcslen(uout));
  if ( outputLength != 67 ) {
    printf("Error! Output string length != 67. Test th_wbrk_line() failed...\n");
    exit (-1);
  }

  printf("Compare with result from th_brk_line()..\n");
  th_brk_line(str, out1, MAXLINELENGTH, "<WBR>");
  th_uni2tis_line(uout, out2, MAXLINELENGTH);

  if ( strcmp(out1,out2) == 0 ) {
    printf("Correct! .. test th_wbrk_line() passed...\n");
  } else {
    printf("Error! Comparison of results from th_brk_line() and th_wbrk_line() failed.\n");
    printf("Test th_wbrk_line() failed...\n");
    exit (-1);
  }
  
  exit(0);
}
