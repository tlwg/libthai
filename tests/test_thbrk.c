/* Test driver for thbrk 
 *
 * $Id: test_thbrk.c,v 1.8 2005-01-13 09:23:13 ott Exp $
 */

#define MAXLINELENGTH 1000

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <thai/thbrk.h>

/* run with "-i" argument to get the interactive version
   otherwise it will run the self test and exit */

int main (int argc, char* argv[]) {
  
  FILE *fp;
  unsigned char _retval[MAXLINELENGTH], _str[MAXLINELENGTH];
  unsigned char *str, *retval;
  unsigned char out[MAXLINELENGTH*2+1];
  int pos[MAXLINELENGTH];
  int outputLength;
  int numCut, i;
  int interactive = 0;
  
  str = _str;
  retval = _retval;
  fp = stdin;


  if ( argc >= 2 ) {
    if ( argv[1][0] == '-' && argv[1][1] == 'i' ) {
      interactive = 1;
    }
  };
  if ( interactive == 1) {
    while(!feof(fp)) {
      printf("Please enter thai words/sentences: ");
      strcpy(retval,"");
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
	outputLength = th_brk_line(str,out,MAXLINELENGTH*2+1,"<WBR>");
	printf("Output string length is %d\n",outputLength-1) ; /* the penultimate is \n */
	printf("Output string is %s",out);
	printf("***********************************************************************\n");
      }; /* if */
    }; /* while */
  } else {
    strcpy(str,"สวัสดีครับ นี่เป็นการทดสอบตัวเอง");
    printf ("Testing with string: %s\n",str);
    numCut = th_brk(str,pos,MAXLINELENGTH);
    printf ("Total %d cut points.", numCut);
    if ( numCut != 8 ) { 
      printf("Error! should be 8.. test th_brk() failed...\n");
      exit (-1);
    }
	
    printf("Cut points list: %d", pos[0]);
    for ( i = 1 ; i < numCut ; i++ ) {
      printf(", %d", pos[i]);
    }
    printf("\n");
    outputLength = th_brk_line(str,out,MAXLINELENGTH*2+1, "<WBR>");
    printf("Output string is %s\n",out);
    printf("Output string length is %d\n",outputLength);
    if ( outputLength != 71 ) {
      printf("Error! should be 71.. test th_brk_line() failed...\n");
      exit (-1);
    }
    printf("*** End of thbrk self test ******\n");
  }
  return 0;
}
