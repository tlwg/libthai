/* Test driver for thbrk 
 *
 * $Id: test_thbrk.c,v 1.4 2001-07-24 21:31:14 ott Exp $
 */

#define MAXLINELENGTH 1000

#include <stdio.h>
#include <stdlib.h>
#include <thai/thbrk.h>

// run with "-i" argument to get the interactive version
// otherwise it will run the self test and exit

int main (int argc, char* argv[]) {
  
  FILE *fp;
  unsigned char _retval[MAXLINELENGTH], _str[MAXLINELENGTH];
  unsigned char *str, *retval;
  unsigned char out[MAXLINELENGTH*2+1];
  int pos[MAXLINELENGTH];
  int outputLength;
  int numCut, i;
  int interactive = 0;
  int cutCode;
  
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
	outputLength = th_brk_line(str,out,MAXLINELENGTH*2+1,"<WBR>");
	printf("Output string length is %d\n",outputLength-1) ; // the penultimate is \n
	printf("Output string is %s",out);
	printf("***********************************************************************\n");
      }; // if
    }; //while
  } else {
    strcpy(str,"สวัสดีครับ นี่เป็นการทดสอบตัวเอง");
    printf ("Testing with string: %s\n",str);
    numCut = th_brk(str,pos,MAXLINELENGTH);
    printf ("Total %d cut points.", numCut);
    if ( numCut == 7 ) { 
      printf("Correct! .. test th_brk() passed...\n");
    } else {
      printf("Error! .. test th_brk() failed...\n");
      exit (-1);
    }
	
    printf("Cut points list: %d", pos[0]);
    for ( i = 1 ; i < numCut ; i++ ) {
      printf(", %d", pos[i]);
    }
    printf("\n");
    outputLength = th_brk_line(str,out,MAXLINELENGTH*2+1, "<WBR>");
    printf("Output string length is %d\n",outputLength);
    if ( outputLength == 67 ) {
      printf("Correct! .. test th_brk_line() passed...\n");
    } else {
      printf("Error! .. test th_brk_line() failed...\n");
      exit (-1);
    }
    printf("Output string is %s\n",out);
    printf("*** End of thbrk self test ******\n");
  }
  return 0;
}
