/* Test driver for thbrk 
 *
 * $Id: test_thbrk.c,v 1.12 2007-06-11 05:13:55 thep Exp $
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
      fgets ((char *)str, MAXLINELENGTH-1, stdin);
      if (!feof (stdin)) {
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
    strcpy ((char *)str, "���ʴդ�Ѻ ����繡�÷��ͺ����ͧ");
    printf ("Testing with string: %s\n", str);
    numCut = th_brk (str, pos, MAXLINELENGTH);
    printf ("Total %d cut points.", numCut);
    if (numCut != 8) { 
      printf("Error! should be 8.. test th_brk() failed...\n");
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
    if (outputLength != 72) {
      printf ("Error! should be 72.. test th_brk_line() failed...\n");
      exit (-1);
    }
    printf ("*** End of thbrk self test ******\n");
  }
  return 0;
}
