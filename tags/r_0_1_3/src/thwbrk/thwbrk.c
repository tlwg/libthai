/* Thai Word Break Library
 * based on cttex by Vuthichai A. (vuthi@[crtl.titech.ac.jp|linux.thai.net])

 * Created 2001-07-15
 * $Id: thwbrk.c,v 1.5 2001-08-04 15:26:49 ott Exp $
 */

#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <stdlib.h>

#include <thai/thailib.h>
#include <thai/thwchar.h>
#include <thai/thbrk.h>


int th_wbrk(const thwchar_t *s, int pos[], size_t n) {
  thchar_t* tis620_0_string;
  unsigned int inputLength, inputLengthReturned;
  int returnValue;

  inputLength = wcslen(s);

  /* convert to tis620-0 string */
  tis620_0_string = malloc(inputLength+1);
  inputLengthReturned = th_uni2tis_line(s, tis620_0_string, inputLength+1);
  if ( inputLength != inputLengthReturned) {
    free(tis620_0_string);
    tis620_0_string = malloc(inputLengthReturned+1);
    th_uni2tis_line(s, tis620_0_string, inputLengthReturned+1);
  };
  
  /* Do word cut */
  returnValue = th_brk(tis620_0_string, pos, n);

  /* Deallocate memory */
  free(tis620_0_string);

  return returnValue;
}

int th_wbrk_line(const thwchar_t *in, thwchar_t *_out, size_t n, const thwchar_t* _cutCode ) {

  thchar_t *tis620_0_string, *tis620_0_out;
  thwchar_t *uni_out, *preout;

  unsigned int inputLength, inputLengthReturned, cutCodeLength;
  unsigned int tis620_0_outLength, preoutLength, minValue;
  int i, returnValue;
  char* cutCode = "\xFE";

  inputLength = wcslen(in);

  /* convert to tis620-0 string */
  tis620_0_string = malloc(inputLength+1);
  inputLengthReturned = th_uni2tis_line(in, tis620_0_string, inputLength+1);
  if ( inputLength != inputLengthReturned) {
    free(tis620_0_string);
    tis620_0_string = malloc(inputLengthReturned+1);
    th_uni2tis_line(in, tis620_0_string, inputLengthReturned+1);
  };
  
  /* malloc for tis620-0output cut string */
  tis620_0_outLength =  2 * strlen( (char*) tis620_0_string);
  tis620_0_out = malloc( tis620_0_outLength+1);
  
  /* Do word cut */
  tis620_0_outLength = th_brk_line(tis620_0_string, tis620_0_out, tis620_0_outLength+1, cutCode);
  
  /* Create equivalent unicode output */
  uni_out = (thwchar_t *) malloc((tis620_0_outLength+1)*sizeof(thwchar_t));
  th_tis2uni_line( tis620_0_out, uni_out, tis620_0_outLength+1);
  
  /* check the length of cutCode */
  cutCodeLength = wcslen(_cutCode);

  /* malloc the pre output unicode string */
  preoutLength = tis620_0_outLength * cutCodeLength;
  preout = (thwchar_t *) malloc( (preoutLength+1)* sizeof(thwchar_t));
  *preout = '\0';

  /* create the real output */
  for ( i = 0 ; i < tis620_0_outLength; i++) {
    if ( strchr(cutCode, tis620_0_out[i]) != NULL ) { /* ok now we found the cut point */
    /*if ( cutCode[0] == tis620_0_out[i] ) { // ok now we found the cut point */
      /* change to user supplied cutcode */
      wcscat( preout, _cutCode);
    } else {
      /* copy to output */
      wcsncat( preout, uni_out + i, 1 );
    }
  };

  /* get the real output length */
  returnValue = wcslen(preout);

  /* now copy to the real _out that will be returned to caller */
  if ( returnValue < n ) {
    minValue = returnValue;
  } else {
    minValue = n;
  };

  wcsncpy(_out, preout, minValue);

  /* Deallocate memory */
  free(uni_out);
  free(preout);
  free(tis620_0_out);
  free(tis620_0_string);

  return returnValue;
}
