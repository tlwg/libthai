/* Test driver for thwchar
 *
 * $Id: test_thwchar.c,v 1.1 2001-07-30 11:41:43 ott Exp $
 */

#define MAXLINELENGTH 1000

#include <stdio.h>
#include <stdlib.h>
#include <thai/thwchar.h>

int main (int argc, char* argv[]) {

  thchar_t tis_620_0[MAXLINELENGTH];
  thchar_t newtis_620_0[MAXLINELENGTH];
  thwchar_t uni[MAXLINELENGTH];
  int outputLength;

  strcpy(tis_620_0,"สวัสดีครับ นี่เป็นการทดสอบตัวเอง");
  
  printf("Testing thwchar...\n");
  printf("Input:  tis-620-0 string of length %d: %s\n", strlen(tis_620_0), tis_620_0);

  // tis-620-0 to Unicode conversion
  outputLength = th_tis2uni_line(tis_620_0, uni, MAXLINELENGTH);
  printf("Output: Unicode string of length %d:", wcslen(uni));
  wprintf("%ls", uni);

  // Unicode to tis-620-0 conversion
  printf("\nConvert back to tis-620-0 string...\n");
  outputLength = th_uni2tis_line(uni, newtis_620_0, MAXLINELENGTH);
  printf("Output: tis-620-0 string of length %d: %s\n", strlen(newtis_620_0), newtis_620_0);

  if ( strcmp(newtis_620_0, tis_620_0) == 0 ) {
    printf(" Input = output, correct! Test thwchar OK.\n");
  } else {
        printf(" Input != output, incorrect!!\n");
	exit(1);
  }

  return 0;
}
