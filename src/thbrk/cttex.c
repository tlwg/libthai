/* cttex.c - Cttex front end
 * 
 * extracted from old cttex code (by Vuthichai A. vuthi@[ctrl.titech.ac.jp|linux.thai.net])
 *
 * Created: 2001-7-15
 * $Id: cttex.c,v 1.3 2001-08-03 11:20:45 thep Exp $
 */

#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <stdlib.h>

#include <thai/thbrk.h>

/* Hmm... :) */
#include "thbrk.c"

int main(argc, argv)
int argc;
char *argv[];
{
  FILE *fp, *fopen();
  unsigned char str[MAXLINELENGTH], out[MAXLINELENGTH];
  unsigned char *retval;
  int i, j, thaimode, c, cr;
  int testmode=0;
  int r_cutcode;
  
  cutcode = CUTCODE;
  bShowAll = 0;  
  bIndexMode = 0;
  debugmode = 0;
  reportmode = 0;
  firstmode = 0;
  r_cutcode = cutcode;

  fprintf(stderr,"C-TTeX $Revision: 1.3 $\n");
  fprintf(stderr,"cttex -h for help usage.\n");
  fprintf(stderr,"Built-in dictionary size: %d words\n", numword);
  
  for(i=1;i<argc;i++) {
    if((argv[i][0] >= '0') && (argv[i][0] <= '9')) {
      sscanf(argv[i],"%d",&cutcode);
      if((cutcode>=1) && (cutcode<=253)) {	/* Test with given code */
	testmode = 1;
	fprintf(stderr, "Filter mode, cut code = %d\n", cutcode);
	r_cutcode = cutcode;

	/* Always use 254 to avoid problem with cutcode+1 */
	cutcode = CUTCODE;
      }
      else {
	fprintf(stderr, "Invalid cutcode\n");
	exit(1);
      }
    }
    else if(argv[i][0]=='-') {
      switch(argv[i][1]) {
      case 'h' : /* Help */
	printf("Usage : cttex [options] < infile > outfile\n");
	printf("Be default, cttex operates in LaTeX mode.\n");
	printf("CTTEX Options are\n"); 
	printf(" 1-253 : Run in filter mode, words are separated\n"); 
	printf("         with the given code.\n");
	printf(" -a    : Show all possible separation patterns\n");
	printf(" -i    : Index Mode. Similar to -a with minimal output\n");
	printf(" -m    : Show only minimal number of words for -a and -i\n");
	printf(" -W    : Separate words by \\wbr (for babel thai latex)\n");
	printf(" -w    : Separate words by <WBR>\n");
	printf(" -r    : Report unknown words to STDERR\n");
	printf(" -d    : Show debug messages\n");
	printf(" -f    : Stop at first pattern with no unknown (a bit faster)\n");
	printf(" -h    : Display this message.\n");
	exit(0);
	break;
      case 'W' :
	cutcode = CUTCODE;
	testmode = 3;
	fprintf(stderr, "babel thai latex mode\n");
	break;
      case 'w' :
	cutcode = CUTCODE;
	testmode = 2;
	fprintf(stderr, "HTML mode\n");
	break;
      case 'a' :
	bShowAll=1;
	fprintf(stderr, "ShowAll Mode\n");
	break;
      case 'i' :
	bIndexMode=1;
	fprintf(stderr, "IndexMode Mode\n");
	break;
      case 'm' :
	if(bShowAll || bIndexMode) {
	  bMinWords=1;
	  fprintf(stderr, "Show only Minimal Words\n");
	}
	else {
	  fprintf(stderr, "-m must be after -a or -i\n");
	  exit(1);
	}
	break;
      case 'd' :
	debugmode=1;
	fprintf(stderr, "Debug ON\n");
	break;
      case 'r' :
	reportmode=1;
	fprintf(stderr, "Report ON\n");
	break;
      case 'f' :
	firstmode=1;
	fprintf(stderr, "Stop at first match\n");
	break;
      }
    }
  }
  
  iLineNumber=0;
  fp = stdin;
  thaimode = cr = 0;
  while(!feof(fp)) {
    retval=(unsigned char *) fgets((char *)str,
				   MAXLINELENGTH-1,fp);
    if(!feof(fp)) {
      iLineNumber++;
      th_normalize(str, str, sizeof str);
      /*fixline(str); */
      if(testmode) {               /* Non-TeX mode */
        switch (testmode) {
        case 1 :                   /* Break with given code */
	  dooneline2(str,out);
	  /* Change cutcode to r_cutcode */
	  j=strlen((char *)out);
	  while(j>=0) {
	    if(out[j]==cutcode)
	      out[j]=r_cutcode;
	    j--;
	  }
	  printf("%s",out);
          break;
        case 2 :                   /* Break with <WBR> tag */
	  dooneline2(str,out);
	  j=0;
	  while( (c=out[j]) ) {
	    if(c==cutcode) {
	      putchar('<');
	      putchar('W');
	      putchar('B');
	      putchar('R');
	      putchar('>');
	    }
	    else {
              if(HIGHWORD(c) && !thaimode) {
		/* putchar('<');
		putchar('N');
		putchar('O');
		putchar('B');
		putchar('R'); 
		putchar('>');*/
		thaimode = 1;
	      }
              if(!HIGHWORD(c) && thaimode) {
		/* putchar('<');
		putchar('/');
		putchar('N');
		putchar('O');
		putchar('B');
		putchar('R');
		putchar('>');*/
		thaimode = 0;
	      }
	      putchar(c);
            }
	    j++;
          }
	  break;
        case 3 : 
	  dooneline2(str,out);
	  j=0;
	  while( (c=out[j]) ) {
	    if(c==cutcode) {
	      putchar('\\');
	      putchar('w');
	      putchar('b');
	      putchar('r');
	      putchar(' ');
	    }
	    else {
              if(HIGHWORD(c) && !thaimode) {
		thaimode = 1;
	      }
              if(!HIGHWORD(c) && thaimode) {
		thaimode = 0;
	      }
	      putchar(c);
            }
	    j++;
          }
	  break;
        default:
          break;
        }
      }
      else {                   /* TeX Mode */ 
	dooneline2(str,out);
	th_normalize(out, out, sizeof out);
	/*adj(out);*/		/* Choose appropriate WANNAYUK */
	j = 0;
	while((c = (int)out[j])!=0) {
	  if(cr && thaimode) {
	    if(j!=0) {
	      fprintf(stderr, "\nLine %d doesn't end with NL\n", iLineNumber);
	      fprintf(stderr, "%d found after NL\n", c);
	      fprintf(stderr, "BUG !! : Please report\n");
	      fprintf(stderr, "%sXXXXX\n",out);
	    }
	    if(HIGHWORD(c)) {
	      /* Add a % before newline in Thai Mode */
	      putchar('%');
	      putchar('\n');
	    }
	    else {
	      putchar('}');
	      putchar('\n');
	      thaimode = 0;
	    }
	    cr = 0;
	  }

	  /* Thai Mode */
	  if(thaimode) {              /* We got a CR in Thai mode */
	    if(c=='\n') {
	      cr = 1;		      /* Mark Flag */
	    }
	    else if(!HIGHWORD(c)) {   /* Leave ThaiMode */
	      putchar('}');
	      putchar(c);
	      thaimode = 0;
	    }
	    else {                    /* Remain in ThaiMode */
	      if(c==CUTCODE) 
		printf("\\tb ");
	      else {
		if(HIGHBIT)
		  putchar(c);
		else
		  printf("\\c%03d", c);
	      }
	    }
	  }

	  /* Not ThaiMode */
	  else {                      
	    if(!HIGHWORD(c))          /* Just print it out */
	      putchar(c);
	    else {                    /* A Thai Char detected */
	      if(c==CUTCODE) {        /* Just in case */
		fprintf(stderr, "\nCutCode found before Thai Characters\n");
		fprintf(stderr, "Line %d : BUG !! : Please report\n", 
			iLineNumber);
		printf("\\tb ");
	      }
	      else {
		if(HIGHBIT)
		  printf("{\\thai %c",c);
		else
		  printf("{\\thai\\c%03d",c);
	      }
	      thaimode = 1;
	    }
	  }
	  j++;
	}
      }
      if((testmode!=1) && (i%10==0))
        fprintf(stderr,"\r%4d",i);
    }
  } 
  if(testmode!=1)
    fprintf(stderr,"\r%4d\n",i);
  if(cr && thaimode) {
    putchar('}');
    putchar('\n');
  }
  fprintf(stderr,"Done\n");

  return 0;
}


