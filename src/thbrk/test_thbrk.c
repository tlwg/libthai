/* Test driver for thbrk 
 *
 * $Id: test_thbrk.c,v 1.1 2001-07-15 16:31:54 ott Exp $
 */

#define MAXLINELENGTH 1000

#include <stdio.h>
#include <stdlib.h>
#include <thai/thbrk.h>

int main (int argc, char* argv[]) {
  
  FILE *fp;
  unsigned char _retval[MAXLINELENGTH], _str[MAXLINELENGTH];
  unsigned char *str, *retval;
  unsigned char out[MAXLINELENGTH*2+1];
  int pos[MAXLINELENGTH];
  int outputLength;
  int numCut, i;
  
  str = _str;
  retval = _retval;
  fp = stdin;

  while(!feof(fp)) {
    printf("Please enter thai words/sentences: ");
    retval = "";
    retval=(unsigned char *) fgets((char *)str, MAXLINELENGTH-1,fp);
    if(!feof(fp)) {
      numCut = th_brk(str,pos,MAXLINELENGTH);
      printf ("Total %d cut points.", numCut);
      if ( numCut > 0 ) { 
	printf("Cut points list: %d", pos[0]);
	for ( i = 1 ; i < numCut ; i++ ) {
	  printf(", %d", pos[i]);
	}
      }
      printf("\n");
      outputLength = th_brk_line(str,out,MAXLINELENGTH*2+1,254);
      printf("Output string length is %d\n",outputLength);
      printf("Output string is %s",out);
      printf("**********************************************************\n");
    }
  };
  return 0;
}
