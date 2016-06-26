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
  ThBrk *brk;

  brk = th_brk_new (NULL);
  if (!brk) {
    printf ("Unable to create word breaker!\n");
    exit (-1);
  }

  strcpy ((char *)str, "สวัสดีครับ กอ.รมน. นี่เป็นการทดสอบตัวเอง");
  printf ("Testing with input string: %s\n", str);

  printf ("Converting to Unicode...\n");
  th_tis2uni_line (str, ustr, MAXLINELENGTH);

  printf ("Calling th_brk_wc_find_breaks()...\n");
  numCut = th_brk_wc_find_breaks (brk, ustr, pos, MAXLINELENGTH);

  printf ("Total %d cut points.", numCut);
  if (numCut > 0) {
    printf ("Cut points list: %d", pos[0]);
    for (i = 1; i < numCut; i++) {
      printf (", %d", pos[i]);
    }
  }
  printf ("\n");
  if (numCut != 7) {
    printf ("Error! Should have 7 cut points.\n"
            "Test th_brk_wc_find_breaks() failed...\n");
    exit (-1);
  }

  unicodeCutCodeLength = th_tis2uni_line ((const thchar_t *) "<WBR>",
                                          (thwchar_t*) unicodeCutCode, 6);
  if (unicodeCutCodeLength != strlen ("<WBR>")) {
    printf ("Warning! Expect th_tis2uni_line() returned length %ld, got %d\n",
            (long)strlen ("<WBR>"), unicodeCutCodeLength);
  }

  printf ("Calling th_brk_wc_insert_breaks() ....\n");
  outputLength = th_brk_wc_insert_breaks (brk, ustr,
                                          (thwchar_t*) uout, MAXLINELENGTH,
                                          unicodeCutCode);

  printf ("Return value from th_brk_wc_insert_breaks is %d\n", outputLength);
  printf ("Output string length is %ld\n", (long)wcslen(uout));
  if (outputLength != 75) {
    printf ("Error! Output string length != 75. "
            "Test th_brk_wc_insert_breaks() failed...\n");
    exit (-1);
  }

  printf ("Compare with result from th_brk_insert_breaks()..\n");
  th_brk_insert_breaks (brk, str, out1, MAXLINELENGTH*2+1, "<WBR>");
  th_uni2tis_line(uout, out2, MAXLINELENGTH);

  if (strcmp ((const char *)out1, (const char *)out2) == 0) {
    printf ("Correct! .. test th_brk_wc_insert_breaks() passed...\n");
  } else {
    printf ("Error! Comparison of results from th_brk_insert_breaks() "
            "and th_brk_wc_insert_breaks() failed.\n");
    printf ("th_brk_insert_breaks :\"%s\"\n", out1);
    printf ("th_brk_wc_insert_breaks:\"%s\"\n", out2);
    printf ("Test th_brk_wc_insert_breaks() failed...\n");
    exit (-1);
  }

  th_brk_delete (brk);

  return 0;
}
