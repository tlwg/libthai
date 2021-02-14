/* Test driver for thbrk 
 */

#define MAXLINELENGTH 1000

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <thai/thbrk.h>

int main (int argc, char* argv[])
{
  thchar_t str[MAXLINELENGTH];
  thchar_t out[MAXLINELENGTH*6+1];
  int pos[MAXLINELENGTH];
  int outputLength;
  int numCut, i;
  ThBrk *brk;
  int success = 1;
  
  brk = th_brk_new (NULL);
  if (!brk) {
    printf ("Unable to create word breaker!\n");
    exit (-1);
  }

  strcpy ((char *)str, "สวัสดีครับ กอ.รมน. นี่เป็นการทดสอบตัวเอง");
  printf ("Testing with string: %s\n", str);
  numCut = th_brk_find_breaks (brk, str, pos, MAXLINELENGTH);
  printf ("Total %d cut points.\n", numCut);
  if (numCut != 7) {
    printf("Error! should be 7.. test th_brk_find_breaks() failed...\n");
    success = 0;
  }

  printf("Cut points list: %d", pos[0]);
  for (i = 1; i < numCut; i++) {
    printf(", %d", pos[i]);
  }
  printf("\n");

  outputLength = th_brk_insert_breaks (brk, str, out, sizeof out, "<WBR>");
  printf ("Output string is %s\n", out);
  printf ("Output string length is %d\n", outputLength);
  if (outputLength != 75) {
    printf ("Error! should be 75.. test th_brk_insert_breaks() failed...\n");
    success = 0;
  }

  th_brk_delete (brk);

  return success ? 0 : -1;
}
