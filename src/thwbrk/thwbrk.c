/* Thai Word Break Library
 * based on cttex by Vuthichai A. (vuthi@[crtl.titech.ac.jp|linux.thai.net])

 * Created 2001-07-15
 * $Id: thwbrk.c,v 1.2 2001-07-31 15:03:06 thep Exp $
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

  // convert to tis620-0 string
  tis620_0_string = malloc(inputLength+1);
  inputLengthReturned = th_uni2tis_line(s, tis620_0_string, inputLength+1);
  if ( inputLength != inputLengthReturned) {
    free(tis620_0_string);
    tis620_0_string = malloc(inputLengthReturned+1);
    th_uni2tis_line(s, tis620_0_string, inputLengthReturned+1);
  };
  
  // Do word cut
  returnValue = th_brk(tis620_0_string, pos, n);

  // Deallocate memory
  free(tis620_0_string);

  return returnValue;
}

int th_wbrk_line(const thwchar_t *in, thwchar_t *_out, size_t n, const thwchar_t* _cutCode ) {
  thchar_t *tis620_0_string, *tis620_0_out, *tis620_0_cutCode;

  unsigned int inputLength, inputLengthReturned, cutCodeLength;
  unsigned int tis620_0_outLength;
  int returnValue;

  inputLength = wcslen(in);

  // convert to tis620-0 string
  tis620_0_string = malloc(inputLength+1);
  inputLengthReturned = th_uni2tis_line(in, tis620_0_string, inputLength+1);
  if ( inputLength != inputLengthReturned) {
    free(tis620_0_string);
    tis620_0_string = malloc(inputLengthReturned+1);
    th_uni2tis_line(in, tis620_0_string, inputLengthReturned+1);
  };
  
  // check the length of cutCode
  cutCodeLength = wcslen(_cutCode);

  // convert cutcode to tis620_0;
  tis620_0_cutCode = malloc( cutCodeLength+1);
  th_uni2tis_line(_cutCode, tis620_0_cutCode, cutCodeLength+1);

  // malloc for output cut string
  tis620_0_outLength = ( 1 + cutCodeLength ) * strlen(tis620_0_string) + 1;
  tis620_0_out = malloc( tis620_0_outLength);
  
  // Do word cut
  th_brk_line(tis620_0_string, tis620_0_out, tis620_0_outLength, tis620_0_cutCode);
  
  // Convert back
  returnValue = th_tis2uni_line(tis620_0_out, _out, n);

  // Doallocate memory
  free(tis620_0_out);
  free(tis620_0_cutCode);
  free(tis620_0_string);

  return returnValue;
}



