/* Test driver for thbrk 
 */

#define MAXLINELENGTH 1000

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <thai/thbrk.h>

/* run with "-i" argument to get the interactive version
   otherwise it will run the self test and exit */

int main (int argc, char* argv[])
{
  thchar_t str[MAXLINELENGTH];
  thchar_t out[MAXLINELENGTH*6+1];
  int pos[MAXLINELENGTH];
  int outputLength;
  int numCut, i;
  int interactive = 0;
  
  if (argc >= 2) {
    if (0 == strcmp (argv[1], "-i"))
      interactive = 1;
  }

  if (interactive) {
    while (!feof (stdin)) {
      printf ("Please enter thai words/sentences: ");
      if (!fgets ((char *)str, MAXLINELENGTH-1, stdin)) {
        numCut = th_brk (str, pos, MAXLINELENGTH);
        printf ("Total %d cut points.", numCut);
        if (numCut > 0) { 
          printf ("Cut points list: %d", pos[0]);
          for (i = 1; i < numCut; i++) {
            printf(", %d", pos[i]);
          }
        }
        printf("\n");
        outputLength = th_brk_line (str, out, sizeof out, "<WBR>");
        printf ("Output string length is %d\n", outputLength-1); /* the penultimate is \n */
        printf ("Output string is %s", out);
        printf("***********************************************************************\n");
      }
    }
  } else {
    strcpy ((char *)str, "สวัสดีครับ กอ.รมน. นี่เป็นการทดสอบตัวเอง");
    printf ("Testing with string: %s\n", str);
    numCut = th_brk (str, pos, MAXLINELENGTH);
    printf ("Total %d cut points.", numCut);
    if (numCut != 7) {
      printf("Error! should be 7.. test th_brk() failed...\n");
      exit (-1);
    }
	
    printf("Cut points list: %d", pos[0]);
    for (i = 1; i < numCut; i++) {
      printf(", %d", pos[i]);
    }
    printf("\n");
    outputLength = th_brk_line (str, out, sizeof out, "<WBR>");
    printf ("Output string is %s\n", out);
    printf ("Output string length is %d\n", outputLength);
    if (outputLength != 75) {
      printf ("Error! should be 75.. test th_brk_line() failed...\n");
      exit (-1);
    }
    printf ("*** End of thbrk self test ******\n");
  }
  return 0;
}
