/* Thai Word Break Library
 * based on cttex by Vuthichai A. (vuthi@[crtl.titech.ac.jp|linux.thai.net])

 * Created 2001-07-15
 * $Id: thbrk.c,v 1.7 2001-08-04 14:45:50 ott Exp $ 
 */

/* Maximum length of input line */
#define                 MAXLINELENGTH           1000

/* Characters to be skipped */
#define                 SKIPWORD(x)             \
                        (((x)<128) || (((x)<=0xF9)&&((x)>=0xF0)))

/* HIGH Chars */
#define                 HIGHWORD(x)             \
                        ((x)>=128)

/* Check level of a character */
#define                 NOTMIDDLE(x)            \
                        (th_chlevel(x)!=0)

#define                 GETLENGTH(x)            \
                        ((x)<-100?-(x)-100:((x)<0?-(x):(x)))

/* Never change this value. If you do, make sure it's below 255. */
#define			CUTCODE			254

/* Set this one will reduce output size with new TeX */
#define                 HIGHBIT                 1 

#define                 LISTSTACKDEPTH          100
#define                 CUTLISTSIZE             100
#define                 DIFLISTSIZE             100

#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <stdlib.h>

/* Load Dictionary : wordptr & numword */
#include "map.h"

#include <thai/thailib.h>
#include <thai/thctype.h>
#include <thai/thstr.h>


int dooneline2(unsigned char *,unsigned char *);
int dooneline2sub(unsigned char *in, int *cutlist, int cutpoint, int,int);
int docut(unsigned char *in,unsigned char *out, int *);
void adj(unsigned char *);
#if 0
void fixline(unsigned char *);
#endif
int findword(unsigned char *, int *);
int moveleft(int);

void push_stack(int *,int,int);
void show_stack(unsigned char *);
void clear_stack();
void check_dif(int *base, int *list, unsigned char *str);
void clear_dif();
void show_dif(unsigned char *);
void insert_dif(int, int);

void th_brk_init();

/* Table Look-Up for level of a character */
/* only those in the range D0-FF */
#if 0
int levtable[]={
                0,2,0,0,2,2,2,2,1,1,1,0,0,0,0,0,
                0,0,0,0,0,0,0,2,3,3,3,3,3,2,3,0,
                0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0 };
#endif

/* Global variable, hmmmm :-p */

int cutcode;
int bShowAll,debugmode,reportmode,firstmode;
int bIndexMode,bMinWords;
unsigned char *mystr;
int minerr,minword;
int *bestcutlist;
int bStopNow;
int iLineNumber;
int ListStack[LISTSTACKDEPTH][CUTLISTSIZE];
int iListStackPointer;
int piDifList[2*DIFLISTSIZE];
int iDifPtr;

void th_brk_init() {
  /* Constructor */

  /* Init global Variables...Yikes!! */
  cutcode = CUTCODE;
  bShowAll = 0;  
  bIndexMode = 0;
  debugmode = 0;
  reportmode = 0;
  firstmode = 0;  
}

int th_brk(const thchar_t *_s, int pos[], size_t n) {
  unsigned char *out;
  int *myPos;
  unsigned int inputLength, outputLength, numFound;
  unsigned int i, minValue;
  unsigned char* s;


  /* Call the constructor */
  th_brk_init();

  /* Init Variables */
  numFound = 0;

  /* get the input line length */
  inputLength=strlen(_s);

  /* Make local s */
  s = malloc(inputLength+1);
  th_normalize(s, _s, inputLength+1);
#if 0
  strcpy(s,_s);
#endif

  /* Memeory allocation */
  out = (unsigned char*) malloc(2*inputLength+1);
  myPos = (int *) malloc(sizeof(int)*inputLength);

#if 0
  /* fix the order of characters */
  fixline(s);
#endif

  /* do cut! */
  dooneline2(s, out);

  /* get the output line length */
  outputLength=strlen(out);

  /* find the position of cutcode */
  for ( i = 0 ; i < outputLength ; i++) {
    if ( out[i] == cutcode ) { /* ok now we found the cut point */
      /* save the position (related to the input string, not this out [so "- numFound"] is added */
      myPos[numFound] = i - numFound;
      /* Increase the number of cut code found */
      numFound++;
    }
  };
  
  /* now copy value to pos[] */
  if ( n < numFound ) {
    minValue = n ;
  } else {
    minValue = numFound;
  };
  for ( i = 0; i < minValue ; i++ ) {
    pos[i] = myPos[i];
  }

  /* Memory deallocation */
  free(myPos);
  free(out);
  free(s);

  /* return numFound */
  return numFound;

}

int th_brk_line(const thchar_t *_in, thchar_t* _out, size_t n, const char* _cutCode) {
  unsigned char *in, *out, *outFromCttex;
  unsigned int inputLength, outputLength, outputFromCttexLength, cutCodeLength;
  unsigned int i, minValue;


  /* call the constructor */
  th_brk_init();

  /* check the length of cutCode */
  cutCodeLength=strlen (_cutCode);

  /* get the input line length */
  inputLength=strlen(_in);

  /* Make local in */
  in = malloc(inputLength+1); 
  th_normalize(in, _in, inputLength+1);
#if 0
  strcpy(in, _in);
#endif

  /* memeory allocation (worst case) */
  out = (unsigned char*) malloc( ( 1 + cutCodeLength ) * inputLength+1);
  outFromCttex = (unsigned char*) malloc( 2 * inputLength+1);

  /* init value */
  strcpy (out, "\x00");
  strcpy (outFromCttex, "\x00");
  
#if 0
  /* fix the order of characters */
  fixline(in);
#endif

  /* do cut! */
  dooneline2(in, outFromCttex);

  /* get the output line length */
  outputFromCttexLength=strlen(outFromCttex);

  /* create the real output  */
  for ( i = 0 ; i < outputFromCttexLength; i++) {
    if ( outFromCttex[i] == cutcode ) { /* ok now we found the cut point */
      /* change to user supplied cutcode */
      strcat( out, _cutCode);
    } else {
      /* copy to output */
      strncat( out, outFromCttex + i, 1 );
    }
  };
  /* now copy to the real _out that will be returned to caller */

  /* get the output line length */
  outputLength=strlen(out);

  /* choose the less value */
  if (  n < outputLength ) {
    minValue = n;
  } else {
    minValue = outputLength;
  };

  strncpy(_out, out, minValue);

  /* Memory deallocation */
  free(outFromCttex);
  free(out);
  free(in);

  /* return the size of output string */
  return outputLength;
} 

/* Private part begins -- original from cttex with few small  */
/* code beautifying/compiler warning suppression */

/********************************************************/
/* Find list of words which match  head of given string */
/********************************************************/

int findword(unsigned char *str, int *matchlist)
{
  int curstate,i,c,j,ns;

  curstate=i=j=0;
  while( (c=str[i]) ) {
    if(c>=state_min[curstate] && c<=state_max[curstate]) {
      if((ns=map[state_offset[curstate]+c-state_min[curstate]])>0) {
	curstate = ns;
	if(state[curstate])
	  matchlist[j++] = i+1;
      }
      else
	break;
    }
    else 
      break;
    i++;
  }
  ns = j;
  j = 0;

  /* Remove words which are not followed by a middle alphabet.
     This can reduce the number of recursive calls in dooneline2sub()
     by half. */
  for(i=0;i<ns;i++)
    if(!NOTMIDDLE(str[matchlist[i]]))
      matchlist[j++]=matchlist[i];
  return j;
}

/************************************************************/
/* Fix alphabet/vowel order, remove redundant vowels/toners */
/************************************************************/

#if 0
void fixline(line)
unsigned char *line;
{
  unsigned char top,up,middle,low;
  unsigned char *out;
  int i,j,c;

  i=j=0;

  out = line; /* Overwrite itself */
  top=up=middle=low=0;
  while( (c=out[i++]) ) {
    switch((c>0xD0)?levtable[c-0xD0]:0) {
    case 0 : 
      if(middle) {
	line[j++]=middle;
	if(low) line[j++]=low;
	if(up)  line[j++]=up;
	if(top) line[j++]=top;
      }
      top=up=middle=low=0;
     middle=c; break;
    case 1 : 
      low=c; break;
    case 2 : 
      up=c; break;
    case 3 : 
      top=c; break;
    }
  }
  if(middle) {
    line[j++]=middle;
    if(low) line[j++]=low;
    if(up)  line[j++]=up;
    if(top) line[j++]=top;
  }
  line[j]=0;
}
#endif

int docut(unsigned char *in,unsigned char *out, int *cutlist)
{
  int i,j,k,l;

  /*
  printf("%s\n", in);
  for(i=0;i<4;i++)
    printf("cut at %d\n", cutlist[i]);
    */
  if(reportmode) {  /* Print Unknown Words */
    i=k=0;
    while(in[i]) {
      l=cutlist[k];
      if(l<0) {
	if(k && (j=cutlist[k-1])>0) {
	  fprintf(stderr,"%d: ",iLineNumber);
	  while(j) {
	    fputc(in[i-j],stderr);
	    j--;
	  }
	}
	if(l<-100) l=-l-100; else l=-l;
	while(l--)
	  fputc(in[i++],stderr);
      }
      else {
	i+=l;
	if(k && (j=cutlist[k-1])<0)
	  fputc('\n',stderr);
      }
      k++;
    } /* while */
    if(cutlist[k-1]<0)
      fputc('\n',stderr);
  }

  i=j=k=0;
  while(in[i]) {
    l=cutlist[k];
    if(l<0) {
      if(k)     /* Remove prev break */
	j--;
      if(l<-100) l=-l-100; else l=-l;
    }

    if(in[i]==230 && j) {  /* Must not break before Mai-Ya-Mok */
      j--;
    }
    while(l--)
      out[j++]=in[i++];
    if(in[i])
      out[j++]=cutcode;
    k++;
  }
  out[j]=0;
  /* printf("%s\n", out); */
  return j;
}

/* Old one by Fong (Completely Removed)
   New one by Hui */

#if 0
void adj(unsigned char *line)
{
  unsigned char top[MAXLINELENGTH];
  unsigned char up[MAXLINELENGTH];
  unsigned char middle[MAXLINELENGTH];
  unsigned char low[MAXLINELENGTH];

  int i, k, c;

  /* Split string into 4 levels */
  /* Clear Buffer */
  for(i=0;i<MAXLINELENGTH;i++)
    top[i]=up[i]=middle[i]=low[i]=0;

  i=0; k=-1;
  while((c=line[i++])!=0) {
    switch((c>0xD0)?levtable[c-0xD0]:0){
    case 0 : /*Middle*/
      /* Special Case for Sara-Am */
      if(c==0xD3) {
	if(k>=0) {
	  up[k]=0xED;
	}
	k++;
	middle[k]=0xD2;      /* Put Sara-Ar */
      }
      else {
	k++;
	middle[k]=c; 
      }
      break;
    case 1 : /*Low*/
      low[k]=c; break;
    case 2 : /*Up*/
      up[k]=c; break;
    case 3 : /*Top*/
      top[k]=c; break;
    }
  }

  /* Beauty Part Begins */

  for(i=0; i<=k; i++) {
    /* Move down from Top -> Up */
    if((top[i]) && (up[i]==0)) {
      up[i] = top[i] - 96;
      top[i] = 0;
    }

    /* Avoid characters with long tail */
    if( middle[i] == 0xBB ||           /* Por Pla */
	middle[i] == 0xBD ||           /* For Far */
	middle[i] == 0xBF ) {          /* For Fun */
      if(up[i]) 
	up[i] = moveleft(up[i]);
      if(top[i]) 
	top[i] = moveleft(top[i]);
    }

    /* Remove lower part of TorSanTan and YorPhuYing
       if necessary */
    if(middle[i] == 0xB0 && low[i])    /* TorSanTan */
      middle[i] = 0x9F;
    if(middle[i] == 0xAD && low[i])    /* YorPhuYing */
      middle[i] = 0x90;

    /* Move lower sara down , for DorChaDa, TorPaTak */
    if(middle[i] == 0xAE ||
       middle[i] == 0xAF ) {
      if(low[i]) 
	low[i] = low[i] + 36;
    }
  }
    
  /* Pack Back To A Line */
  i=0; k=0;
  while(middle[i]){
    line[k++]=middle[i];
    if(low[i]) line[k++]=low[i];
    if(up[i])  line[k++]=up[i];
    if(top[i]) line[k++]=top[i];
    i++;
  }

  /* Numbef of Bytes might change */
  line[k]=0;
}
#endif

int lefttab[]={   136, 131,        /* Meaning : change 136 to 131, ... */
		  137, 132,        /* Up Level Mai Ek, To, Ti ... */
		  138, 133,
		  139, 134,
		  140, 135,
		 0xED, 0x8F,       /* Circle */
                 0xE8, 0x98,       /* Top Level Mai Ek, To, Ti, ... */
                 0xE9, 0x99,
                 0xEA, 0x9A,
                 0xEB, 0x9B,
                 0xEC, 0x9C,
                 0xD4, 0x94,       /* Sara I, EE, ... */
                 0xD5, 0x95, 
                 0xD6, 0x96, 
                 0xD7, 0x97, 
                 0xD1, 0x92,
                 0xE7, 0x93 };

int moveleft(int c)
{
  int i;

  for(i=0;i<34; i+=2) {
    if(lefttab[i] == c)
      return lefttab[i+1];
  }
  return c;
}

/* New Recursive Version */
int dooneline2(unsigned char *in, unsigned char *out)
{
  int l,i,j,jt,freetemp;
  int *cutlist;
  unsigned char *temp;
  unsigned char stemp[MAXLINELENGTH];
  int scutlist[MAXLINELENGTH];
  int sbestcutlist[MAXLINELENGTH];

  i=j=freetemp=0;
  temp = stemp;
  cutlist = scutlist;
  bestcutlist = sbestcutlist;
  l = strlen((char *)in);
  /* Allocate from Heap if the line is too long */
  if(l>MAXLINELENGTH) {
    temp = malloc(l+1);
    cutlist = malloc(sizeof(int)*l);
    bestcutlist = malloc(sizeof(int)*l);
    freetemp=1;
  }

  jt=0;
  while(in[i]) {
    if(SKIPWORD(in[i])) {
      if(jt) {
	temp[jt]=0;
	if(debugmode)
	  printf("->%s\n",temp);
	mystr=temp;
	minerr=minword=9999;
	bStopNow=0;
	dooneline2sub(temp,cutlist,0,0,0);
	if(bShowAll || bIndexMode) 
	  show_stack(temp);
	j+=docut(temp,out+j,bestcutlist);
	jt=0;
      }
      out[j++] = in[i++];
    }
    else {
      temp[jt++] = in[i++];
    }
  }
  if(jt) {
    temp[jt]=0;
    if(debugmode)
      printf("->%s\n",temp);
    mystr=temp;
    minerr=minword=9999;
    bStopNow=0;
    dooneline2sub(temp,cutlist,0,0,0);
    if(bShowAll || bIndexMode) 
      show_stack(temp);
    j+=docut(temp,out+j,bestcutlist);
  }
  out[j]=0;
  if(freetemp) {
    free(temp);
    free(cutlist);
    free(bestcutlist);
  }
  return 0;
}

/****************************************************/
/* Cut a string which contains only Thai characters */
/****************************************************/

int dooneline2sub(unsigned char *in, int *cutlist, int cutpoint, int curerr,
		  int flags)
{
  int i,j,k,ii;
  int matchoff;
  int l, count;
  int matchlist[MAXLINELENGTH];

  matchoff = 0;

  /* 
     printf("> %s\n", in); 
  */
  i=j=0;
  if(in[0]) {
    if((k=findword(in,matchlist))!=0) { /* Found in dict */
      while(k--) {
	matchoff = matchlist[k];
	/* Record Match Length */
	cutlist[cutpoint] = matchoff;
	dooneline2sub(in+matchoff,cutlist,cutpoint+1,curerr,0);
	if(bStopNow)
	  return 0;
      }
      if(!flags) {
	i=1;
	ii=0;
	while(i<matchoff) {
	  if(!NOTMIDDLE(in[i])) {
	    ii++;
	    if(curerr+ii <= minerr) {
	      cutlist[cutpoint] = -i;
	      dooneline2sub(in+i,cutlist,cutpoint+1,curerr+ii,1);
	      if(bStopNow)
		return 0;
	    }
	  }
	  i++;
	}
      }
    }
    else { /* Not in dict */
      if(!flags)
	if(curerr < minerr) {
	  i=1;
	  while(in[i] && NOTMIDDLE(in[i]))
	    i++;
	  cutlist[cutpoint] = -100-i;  /* Negative indicates unknown word */
	  dooneline2sub(in+i,cutlist,cutpoint+1,curerr+1,0);
	  if(bStopNow)
	    return 0;
	}
    }
    return curerr;
  }
  else { /* Got a NULL string */
    k=0;
    if(curerr<minerr) { 
      minword = 9999;
      minerr=curerr;
      clear_stack();
    }
    count=cutpoint;

    if(debugmode) { /* Debug Mode */
      putchar('=');
      for(i=0;i<cutpoint;i++) {
	l=cutlist[i];
	if(l<-100) { 
	  putchar('*');
	  l=-l-100; count--;
	}
	if(l<0) {
	  putchar('#');
	  l=-l; count--;
	}
	for(j=0;j<l;j++)
	  putchar(mystr[k++]);
	putchar(' ');
      }
    } /* Debug Mode */
    else { /* Not Debug Mode */
      for(i=0;i<cutpoint;i++) {
	if(cutlist[i]<0) 
	  count--;
      }
    } /* Not Debug Mode */


    if(bShowAll || bIndexMode) {
      if(bMinWords) { 
	if(count < minword)
	  clear_stack();
	if(count <= minword)
	  push_stack(cutlist, cutpoint, count);
      }
      else
	push_stack(cutlist, cutpoint, count);
    }

    if(count <= minword) {
      minword = count;
      for(i=0;i<cutpoint;i++) 
	bestcutlist[i]=cutlist[i];
    }

    if(debugmode)
      printf("Err(%d) Word(%d)\n",minerr,count);

    /* Stop at first perfect match */
    if(curerr==0 && firstmode)
      bStopNow = 1;
    return 0;
  }
}

void push_stack(int *cutlist, int cutcount, int wordcount)
{
  int i;

  if(iListStackPointer<LISTSTACKDEPTH) {
    for(i=0;i<cutcount;i++) {
      ListStack[iListStackPointer][i]=cutlist[i];
    }
    ListStack[iListStackPointer][CUTLISTSIZE-1] = wordcount;
    iListStackPointer++;
  }
  else { /* Stack Full */
    fprintf(stderr,"Warning: Cutlist Stack Full\n");
  }
}

void show_stack(unsigned char *str)
{
  int i,j;
  unsigned char *temp;

  temp=malloc(strlen((char *)str)*2);
  if(bIndexMode)
    clear_dif();
  for(i=0;i<iListStackPointer;i++) {
    docut(str,temp,ListStack[i]);
    j=0;
    while(temp[j]) {
      if(temp[j]==cutcode)
	temp[j]=32;
      j++;
    }
    if(bShowAll)
      printf("%d[%d]: %s\n",i,
	     ListStack[i][CUTLISTSIZE-1],temp);
    if(bIndexMode)
      check_dif(bestcutlist,ListStack[i],str);
  }
  if(bIndexMode)
    show_dif(str);
  free(temp);
}

/* Display only part of 'list' which does not match 'base' */
void check_dif(int *base, int *list, unsigned char *str)
{
  int iBaseItem, iListItem;
  int iBasePtr, iBaseLength;
  int iListPtr, iListLength;
  int start;

  iBaseItem = iListItem = 0;
  iBasePtr = iListPtr = 0;

  while(str[iBasePtr]) {
    iBaseLength = base[iBaseItem];
    iBaseLength = GETLENGTH(iBaseLength);

    iListLength = list[iListItem];
    iListLength = GETLENGTH(iListLength);

    if(iListLength != iBaseLength) { /* Found ! */
      start = iBasePtr;
      iBasePtr += iBaseLength;
      iListPtr += iListLength;
      insert_dif(start,iListPtr);
      start = iListPtr;
      while(iBasePtr != iListPtr) {
	if(iBasePtr > iListPtr) {
	  iListItem++;
	  iListPtr += GETLENGTH(list[iListItem]);
	  insert_dif(start,iListPtr);
	  start = iListPtr;
	}
	else if(iBasePtr < iListPtr) {
	  iBaseItem++;
	  iBasePtr += GETLENGTH(base[iBaseItem]);
	}
      }
    }
    else {
      iBasePtr += iBaseLength;
      iListPtr += iListLength;
    }
    iBaseItem++;
    iListItem++;
  }
}

void clear_dif()
{
  iDifPtr=0;
}

void show_dif(unsigned char *str)
{
  int i, start;
  i=0;
  while(i<iDifPtr) {
    start = piDifList[i];
    while(start < piDifList[i+1])
      fputc(str[start++], stdout);
    fputc(':',stdout);
    i+=2;
  }
  /*
  if(iDifPtr)
    fputc('\n',stdout);
  */
}

/* Never insert a pair already exists */
void insert_dif(int start, int stop)
{
  int i;
  i=0;
  while(i<iDifPtr) {
    if(start == piDifList[i] &&
       stop  == piDifList[i+1])
      return;
    i+=2;
  }
  piDifList[i] = start;
  piDifList[i+1] = stop;
  iDifPtr+=2;
  if(iDifPtr >= DIFLISTSIZE) {
    fprintf(stderr,"Not Enough DifList\n");
    exit(1);
  }
}

void clear_stack()
{
  iListStackPointer = 0;
}

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.6  2001/08/03 11:20:45  thep
 * Make thbrk and cttex use thstr instead of fixline() and adj().
 * Fix a memory leak.
 *
 * Revision 1.5  2001/07/31 22:20:59  ott
 * -fix const casting problem
 *
 * Revision 1.4  2001/07/24 21:31:14  ott
 * -modified the th_brk_line to accept cutCode as char* instead of int.
 * -modified according to the changed interface the test program.
 *
 * Revision 1.3  2001/07/22 21:32:07  ott
 * -fix the segfault in char* stuff
 *
 * Revision 1.2  2001/07/16 10:54:05  thep
 * Add automake files for building thbrk.
 *
 * Revision 1.1  2001/07/15 16:31:54  ott
 * -first version.
 * -wrapper for P'Hui's cttex.
 *
 * Revision 1.22  2001/02/28 12:48:16  chanop
 * Import cttex.c (GPL version) into new cvs tree.
 * Add -W option for babel thailatex pacakge.
 *
 * Revision 1.21  1999/05/19 13:23:13  vuthi
 * Add -i and -m
 * use unsigned short for map[]
 *
 * Revision 1.20  1999/05/13 13:33:44  vuthi
 * New findword() algorithm using DFA.
 * Code cleanup.
 * See README.th for more info.
 *
 * Revision 1.19  1999/03/16 12:04:05  vuthi
 * >> - Add "fixline()" to correct the typos
 * >> - New "dooneline2()" recursive algorithm capable of finding
 * >>   all possible cut patterns
 * >> - Command line options
 *
 * Revision 1.18  1997/12/09 19:17:34  vuthi
 * Add highlight mode (cutcode = 1)
 * highlight mode = to be used with Thai-L spell check
 *
 * Revision 1.17  1997/01/04 15:15:08  vuthi
 * - Always uses cutcode = 254 in the real word-sep routine
 *   Given cutcode is applied after that.
 *   This is to avoid cutcode+1 falls into other character
 * - In test mode (cutcode <> 0), also report unknown words
 *   on stderr. -> Simple spelling checker
 *
 * Revision 1.16  1996/09/01 13:34:49  vuthi
 * In HTML mode :
 *   Surround Thai Text with <NOBR> tags, to allow use of <WBR>
 *   in Microsoft Internet Explorer 3.0
 *   Without <NOBR>, <WBR> has no meaning in IE 3.0
 *
 * Revision 1.15  1995/10/06  13:09:52  vuthi
 * BUG FIXED : HTML mode worked only on the first line.
 *
 * Revision 1.14  1995/08/07  15:26:36  vuthi
 * HTML mode added
 *
 * Revision 1.13  1995/08/03  06:05:11  vuthi
 * Change "TEST MODE" to "FILTER MODE"
 *
 * Revision 1.12  1995/08/03  05:37:00  vuthi
 * Built-In dictionary (via .h file)
 * Perl script created
 * remove readdictfile()
 * remove -d option
 * dooneline() can be used alone (as a word-sep library).
 *
 * Revision 1.11  1995/08/03  04:47:22  vuthi
 * Fix bug in filter().. add if(SKIPWORD(c)) to reset 'a'
 *
 * Revision 1.10  1995/08/02  11:23:20  vuthi
 * Little bug fixed
 *
 * Revision 1.9  1995/08/02  11:19:21  vuthi
 * Add filter() to prevent word break before unknown words
 * Always break after unknown words
 *
 * Revision 1.8  1995/08/02  09:44:05  vuthi
 * New ADJ() algorithm.. Sara Am problem fixed.
 * moveleft() added.
 *
 * Revision 1.7  1995/07/22  17:43:50  vuthi
 * No breaking char at end of Thai word
 *
 * Revision 1.6  1995/04/25  12:11:28  vuthi
 * Use memcmp instead of strcmp to fix bug on some Japanized machine
 *
 * Revision 1.52  1995/4/24  23:26:00
 * 8-Bit version and use \tb instead of #254
 *
 * Revision 1.5  1994/12/23  08:45:06  vuthi
 * Bug of newline disappear at the end of Thai line
 *
 * Revision 1.4  1994/12/14  10:50:18  vuthi
 * Command Line Option, use "%" to terminate Thai lines
 *
 * Revision 1.3  1994/12/14  10:12:22  vuthi
 * Add Header Revision and Log
 *
 */

/* Limit # of Error
   No double #
   */
