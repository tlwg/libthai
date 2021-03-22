/* Test driver for thbrk 
 */

#define MAXLINELENGTH 100

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <thai/thbrk.h>
#include <iconv.h>

typedef struct _Sample Sample;
struct _Sample {
    const char *str;
    int         n_brk;
    int         brk_pos[MAXLINELENGTH];
    const char *ins_str;
};

const Sample TestSamples[] = {
    { u8"12% is 12 % and (12.00)% is (12.00) %",
      6, {4, 7, 12, 16, 25, 28},
      u8"12% |is |12 % |and |(12.00)% |is |(12.00) %"},
    { u8"ten% of all สิบ%ของทั้งหมด",
      5, {5, 8, 12, 16, 19 },
      u8"ten% |of |all |สิบ%|ของ|ทั้งหมด"},
    { u8"$12 is $ 12 and $(12.00) is $ (12.00)",
      6, {4, 7, 12, 16, 25, 28},
      u8"$12 |is |$ 12 |and |$(12.00) |is |$ (12.00)"},
    { u8"Brazilian R$2 Nicaraguan C$10 U$S5 US$5 5$ 5 $ Micro$oft C++",
      8, {10, 14, 25, 30, 35, 40, 47, 57 },
      u8"Brazilian |R$2 |Nicaraguan |C$10 |U$S5 |US$5 |5$ 5 $ |Micro$oft |C++"},
    { u8"฿12 บ้างเขียน 12฿ หรือ ฿ 12 หรือ 12 ฿",
      7, {4, 8, 14, 18, 23, 28, 33},
      u8"฿12 |บ้าง|เขียน |12฿ |หรือ |฿ 12 |หรือ |12 ฿"},
    { u8"฿(12.00) บ้างก็เขียน ฿ (12.00) หรือ (12.00)฿ หรือ (12.00) ฿",
      8, {9, 13, 15, 21, 31, 36, 45, 50},
      u8"฿(12.00) |บ้าง|ก็|เขียน |฿ (12.00) |หรือ |(12.00)฿ |หรือ |(12.00) ฿"},
    { u8"#hashtag #แฮชแท็ก #1 5# helloสวัสดี",
      5, {9, 18, 21, 24, 29},
      u8"#hashtag |#แฮชแท็ก |#1 |5# |hello|สวัสดี"},
    { u8"e.g. Ph.D.Engineering M.A.(Linguistics) ม.ค.มกราคมศกนี้",
      8, {5, 10, 22, 26, 40, 44, 50, 52},
      u8"e.g. |Ph.D.|Engineering |M.A.|(Linguistics) |ม.ค.|มกราคม|ศก|นี้"},
    { u8"(s)he (may) meet person(s)",
      3, {6, 12, 17},
      u8"(s)he |(may) |meet |person(s)"},
    { u8"สวัสดีครับ กอ.รมน. นี่เป็นการทดสอบตัวเอง",
      7, {6, 11, 19, 22, 26, 29, 34},
      u8"สวัสดี|ครับ |กอ.รมน. |นี่|เป็น|การ|ทดสอบ|ตัวเอง"},
    { u8"พันธุ์ข้าว กข43 น้ำตาลต่ำ กิโลละ 40บาท กระดาษ A4 ใน 4.3BSD",
      12, {6, 11, 16, 22, 26, 30, 33, 35, 39, 46, 49, 52},
      u8"พันธุ์|ข้าว |กข43 |น้ำตาล|ต่ำ |กิโล|ละ |40|บาท |กระดาษ |A4 |ใน |4.3BSD"},
    { 0, 0, {}, 0 }
};

iconv_t utf8_to_tis_iconv;
iconv_t tis_to_utf8_iconv;

void init_iconv (void)
{
    utf8_to_tis_iconv = iconv_open ("TIS-620", "UTF-8");
    tis_to_utf8_iconv = iconv_open ("UTF-8", "TIS-620");
}

void close_iconv (void)
{
    iconv_close (utf8_to_tis_iconv);
    iconv_close (tis_to_utf8_iconv);
}

size_t utf8_to_tis (const char *utf8_str, thchar_t *tis, size_t tis_sz)
{
    char  *in = (char *)utf8_str;
    size_t in_left = strlen (in) + 1;
    char  *out = (char *)tis;
    size_t out_left = tis_sz;
    return iconv (utf8_to_tis_iconv, &in, &in_left, &out, &out_left);
}

size_t tis_to_utf8 (const thchar_t *tis_str, char *utf8, size_t utf8_sz)
{
    char  *in = (char *)tis_str;
    size_t in_left = strlen (in) + 1;
    char  *out = utf8;
    size_t out_left = utf8_sz;
    return iconv (tis_to_utf8_iconv, &in, &in_left, &out, &out_left);
}

void show_breaks (int brk_pos[], int n_brk)
{
    int i;

    printf ("%d breaks: {", n_brk);
    for (i = 0; i < n_brk; ++i) {
        if (i > 0) {
            printf (", ");
        }
        printf ("%d", brk_pos[i]);
    }
    printf ("}\n");
}

int test_samples (ThBrk *brk, const Sample samples[])
{
    int success = 1;
    int i;

    for (i = 0; samples[i].str; ++i) {
        thchar_t tis_str[MAXLINELENGTH + 1];
        int brk_pos[MAXLINELENGTH];
        int n_brk, j;
        thchar_t ins_str[MAXLINELENGTH*2 + 1];
        char utf8_str[MAXLINELENGTH*3 + 1];

        printf ("Testing: %s\n", samples[i].str);

        utf8_to_tis (samples[i].str, tis_str, sizeof tis_str);

        n_brk = th_brk_find_breaks (brk, tis_str, brk_pos, MAXLINELENGTH);

        show_breaks (brk_pos, n_brk);

        if (n_brk != samples[i].n_brk) {
            printf ("Failed at case #%d: n_brk = %d, expected %d\n",
                    i, n_brk, samples[i].n_brk);
            success = 0;
        }
        for (j = 0; j < n_brk; ++j) {
            if (brk_pos[j] != samples[i].brk_pos[j]) {
                printf ("Failed at case #%d, brk_pos[%d] = %d, expected %d\n",
                        i, j, brk_pos[j], samples[i].brk_pos[j]);
                success = 0;
            }
        }

        th_brk_insert_breaks (brk, tis_str, ins_str, sizeof ins_str, "|");
        tis_to_utf8 (ins_str, utf8_str, sizeof utf8_str);

        printf ("Segmented: %s\n", utf8_str);

        if (strcmp (utf8_str, samples[i].ins_str) != 0) {
            printf ("Failed at case #%d: ins_str = \"%s\", expected \"%s\"\n",
                    i, utf8_str, samples[i].ins_str);
            success = 0;
        }
    }

    return success;
}

int main (void)
{
    int success = 0;
    ThBrk *brk = th_brk_new (NULL);
    if (!brk) {
        printf ("Unable to create word breaker!\n");
        exit (-1);
    }

    init_iconv();

    success = test_samples (brk, TestSamples);

    close_iconv();
    th_brk_delete (brk);

    return success ? 0 : -1;
}
