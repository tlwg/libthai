/* Test driver for thwbrk 
 */

#define MAXLINELENGTH 1000

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <thai/thbrk.h>
#include <thai/thwchar.h>
#include <thai/thwbrk.h>
#include <wchar.h>

int main (int argc, char* argv[])
{
  thchar_t str[MAXLINELENGTH];
  thwchar_t ustr[MAXLINELENGTH], uout[MAXLINELENGTH], unicodeCutCode[6];

  thchar_t out1[MAXLINELENGTH*2+1];
  thchar_t out2[MAXLINELENGTH];
  int pos[MAXLINELENGTH];
  int outputLength, unicodeCutCodeLength;
  int numCut, i;
  
  strcpy ((char *)str, "สวัสดีครับ นี่เป็นการทดสอบตัวเอง");
  printf ("Testing with input string: %s\n", str);

  printf ("Converting to Unicode...\n");
  th_tis2uni_line (str, ustr, MAXLINELENGTH);

  printf ("Calling th_wbrk()...\n");
  numCut = th_wbrk (ustr, pos, MAXLINELENGTH);

  printf ("Total %d cut points.", numCut);
  if (numCut > 0) { 
    printf ("Cut points list: %d", pos[0]);
    for (i = 1; i < numCut; i++) {
      printf (", %d", pos[i]);
    }
  }
  printf ("\n");
  if (numCut != 6) { 
    printf ("Error! Should have 6 cut points.\n Test th_wbrk() failed...\n");
    exit (-1);
  }
	
  unicodeCutCodeLength = th_tis2uni_line ((const thchar_t *) "<WBR>",
                                          (thwchar_t*) unicodeCutCode, 6);

  printf ("Calling th_wbrk_line() ....\n");
  outputLength = th_wbrk_line (ustr, (thwchar_t*) uout, MAXLINELENGTH,
                               unicodeCutCode);

  printf ("Return value from th_wbrk_line is %d\n", outputLength);
  printf ("Output string length is %d\n", wcslen(uout));
  if (outputLength != 62) {
    printf ("Error! Output string length != 62. "
            "Test th_wbrk_line() failed...\n");
    exit (-1);
  }

  printf ("Compare with result from th_brk_line()..\n");
  th_brk_line (str, out1, MAXLINELENGTH*2+1, "<WBR>");
  th_uni2tis_line(uout, out2, MAXLINELENGTH);

  if (strcmp ((const char *)out1, (const char *)out2) == 0) {
    printf ("Correct! .. test th_wbrk_line() passed...\n");
  } else {
    printf ("Error! Comparison of results from th_brk_line() "
            "and th_wbrk_line() failed.\n");
    printf ("th_brk_line :\"%s\"\n", out1);
    printf ("th_wbrk_line:\"%s\"\n", out2);
    printf ("Test th_wbrk_line() failed...\n");
    exit (-1);
  }
  
  return 0;
}
