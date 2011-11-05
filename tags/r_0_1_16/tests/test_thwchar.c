/* Test driver for thwchar
 */

#define MAXLINELENGTH 1000

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <thai/thwchar.h>

static const thchar_t win_sample[] = "æ\x8bÕªŸ\x86æ’Ëª\x82\x9bÆ\xfc\x80ÿ\x90ÿ°Ì“ª\x99“°ÌÈ“ª\x99\x9c“ª\x99“ \x8c∑\x8b ’°Áª\x9a";
static const thchar_t mac_sample[] = "æ\x88ÕªŸ\x83æ’Ëª\x95\x98Æ\xd8\xb0ÿ\xadÿ°Ì“ª\x8f“°ÌÈ“ª\x8f\x99“ª\x8f“ \x89∑\x88 ’°Áª\x93";

int main (int argc, char* argv[])
{
  thchar_t  tis_620_0[MAXLINELENGTH];
  thchar_t  newtis_620_0[MAXLINELENGTH];
  thwchar_t uni[MAXLINELENGTH];
  int       outputLength;
  const thchar_t *pc;
  int       err = 0;

  strcpy(tis_620_0," «— ¥’§√—∫ π’Ë‡ªÁπ°“√∑¥ Õ∫µ—«‡Õß");
  
  fprintf(stderr, "Testing thwchar...\n");
  fprintf(stderr, "Input:  tis-620-0 string of length %d: %s\n",
          strlen(tis_620_0), tis_620_0);

  /* tis-620-0 to Unicode conversion */
  outputLength = th_tis2uni_line(tis_620_0, uni, MAXLINELENGTH);
  fprintf(stderr, "Output: Unicode string of length %d:", wcslen(uni));

  /* Unicode to tis-620-0 conversion */
  fprintf(stderr, "\nConvert back to tis-620-0 string...\n");
  outputLength = th_uni2tis_line(uni, newtis_620_0, MAXLINELENGTH);
  fprintf(stderr, "Output: tis-620-0 string of length %d: %s\n",
          strlen(newtis_620_0), newtis_620_0);

  if (strcmp(newtis_620_0, tis_620_0) == 0) {
    fprintf(stderr, " Input = output, correct! Test thwchar OK.\n");
  } else {
    fprintf(stderr, " Input != output, incorrect!!\n");
    err = 1;
  }

  /* Test Unicode <-> Win/Mac extensions */
  for (pc = win_sample; *pc; ++pc) {
    if (th_uni2winthai(th_winthai2uni(*pc)) != *pc) {
      fprintf(stderr, "Inconsistent uni<->winthai conv: %02x -> %04lx, %02x\n",
              *pc, th_winthai2uni(*pc), th_uni2winthai(th_winthai2uni(*pc)));
      err = 1;
    }
  }
  for (pc = mac_sample; *pc; ++pc) {
    if (th_uni2macthai(th_macthai2uni(*pc)) != *pc) {
      fprintf(stderr, "Inconsistent uni<->macthai conv: %02x -> %04lx, %02x\n",
              *pc, th_macthai2uni(*pc), th_uni2macthai(th_macthai2uni(*pc)));
      err = 1;
    }
  }

  return err;
}
