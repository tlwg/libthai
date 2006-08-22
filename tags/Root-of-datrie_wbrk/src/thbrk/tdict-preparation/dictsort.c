/*---------------------------------------------------------------------
 * All portions of code are copyright by their respective author/s.
 * Copyright (C) 1996-2001 Vuthichai Ampornaramveth <vuthi@venus.dti.ne.jp>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *---------------------------------------------------------------------*/
/* Thai word-separator by dictionary */
/* By Vuthichai A.                   */

#define                 NONSORTEDDICTFILE       "tdict.nonsorted"
#define                 SORTEDDICTFILE       "tdict.txt"
#define                 MAXWORD                 50000
#define                 MAXWORDLENGTH           30
#define                 MAXLINELENGTH           400

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int levtable[]={
                0,2,0,0,2,2,2,2,1,1,1,0,0,0,0,0,
                0,0,0,0,0,0,0,2,3,3,3,3,3,2,3,0,
                0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0 };

void readfile(unsigned char *);
void fixline(unsigned char *);
void dooneline(unsigned char *,unsigned char *);
int findword(unsigned char *);

unsigned char *wordptr[MAXWORD];
int numword;                    /* Number of words in memory */

main()
{
  FILE *fp, *fopen();
  unsigned char inputfile[80];
  unsigned char str[MAXLINELENGTH], out[MAXLINELENGTH];
  int i;
  
  numword = 0;
  readfile(NONSORTEDDICTFILE);
  printf("Now generating output....\n");

  fp = fopen(SORTEDDICTFILE,"w");
  for(i=0;i<numword;i++) {
    /* Remove duplicate words */
    if(i<numword-1) {
    if(strcmp(wordptr[i]+1, wordptr[i+1]+1)!=0)
      fprintf(fp,"%s\n", wordptr[i]+1);
    }
    else {
      fprintf(fp,"%s\n", wordptr[i]+1);
    }

  }
  fclose(fp);
  printf("Done...\n");
  return 0;
}

void readfile(unsigned char *fname)
{
  FILE *fp, *fopen();
  unsigned char str[MAXWORDLENGTH];
  unsigned char *ostr;
  int l, i;
  
  fp = fopen(fname,"r");

  while(!feof(fp)) {
    fgets(str,MAXWORDLENGTH-1,fp);
    if(!feof(fp)) {
      fixline(str);
      wordptr[numword] = (unsigned char *)malloc((l=strlen(str))+2);
      if(wordptr[numword]==NULL)
        printf("Memory Error\n");
      strcpy(wordptr[numword]+1, str);
      wordptr[numword][l]=0;            /* Remove new line */
      wordptr[numword][0] = l-1;

      if(numword > 0)
      if(strcmp(wordptr[numword]+1,wordptr[numword-1]+1)<0) 
      {
        ostr = wordptr[numword];
        i = numword;
        while(i && (strcmp(ostr+1,wordptr[i-1]+1)<0)) {
          wordptr[i] = wordptr[i-1];
          i--;
        }
        wordptr[i]=ostr;
      }
      numword++;
      if(numword % 500 ==0)
        printf("%d\n",numword);
    }
  }
  fclose(fp);
  printf("Reading dictionary done.\n");
}

	
void fixline(line)
unsigned char *line;
{
  unsigned char top,up,middle,low;
  unsigned char out[MAXLINELENGTH];
  int i,j,c;

  i=j=0;
  strcpy(out,line);
  top=up=middle=low=0;
  while(c=out[i++]) {
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
