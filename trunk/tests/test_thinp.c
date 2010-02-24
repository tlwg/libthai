/*
 * test_thinp.c : Test suite for <thai/thinp.h> functions
 * Created: 2001-08-09
 * Author:  Theppitak Karoonboonyanan
 */

#include <thai/thinp.h>
#include <string.h>
#include <stdio.h>

const thchar_t test_keys[] = "น้ำนำ้กี่ก่ีกุ่กุ่กุ์ก์ุกิ์ก์ิเิเำเ้นิ์ัน์ันุ่ินา์ฤาฦา";
const thchar_t res_level0[] = "น้ำนำ้กี่ก่ีกุ่กุ่กุ์ก์ุกิ์ก์ิเิเำเ้นิ์ัน์ันุ่ินา์ฤาฦา";
const thchar_t res_level1[] = "น้ำนำกี่ก่กุ่ก่กุ์ก์กิ์ก์เเำเนิ์น์นุ่นาฤาฦา";
const thchar_t res_level2[] = "น้ำนำกี่ก่กุ่ก่กุ์ก์กิ์ก์เนิ์น์นุ่นาฤ";
const thchar_t res_validate[] = "น้ำน้ำกี่กี่กุ่กุ่กุ์กุ์กิ์กิ์เนันันิ่นาฤๅฦๅ";

static int test_simple_input(const thchar_t keys[],
                             const thchar_t ans[], int level)
{
    thchar_t buffer[80];
    int      cur_pos = 0;
    int      err_no = 0;

    while (*keys) {
        thchar_t prev_c = cur_pos ? buffer[cur_pos-1] : 0;
        if (th_isaccept(prev_c, *keys, level)) {
            buffer[cur_pos++] = *keys;
        }
        ++keys;
    }
    buffer[cur_pos] = 0;

    err_no = strcmp((const char*)buffer, (const char*)ans);
    if (err_no != 0) {
        fprintf(stderr, "(%s)!=(%s)\n", buffer, ans);
    }
    return err_no;
}

static int test_th_isaccept()
{
    int err_no = 0;

    err_no += test_simple_input(test_keys, res_level0, 0);
    err_no += test_simple_input(test_keys, res_level1, 1);
    err_no += test_simple_input(test_keys, res_level2, 2);

    return err_no;
}

static int test_th_validate()
{
    int      err_no = 0;
    thchar_t buffer[80];
    int      cur_pos = 0;
    const thchar_t *keys = test_keys;

    while (*keys) {
        struct thcell_t prev_cell;
        struct thinpconv_t conv;

        th_prev_cell(buffer, cur_pos, &prev_cell, 1);
        if (th_validate(prev_cell, *keys, &conv)) {
            strcpy(&buffer[cur_pos + conv.offset], conv.conv);
            cur_pos += conv.offset + strlen(conv.conv);
        }
        ++keys;
    }
    buffer[cur_pos] = 0;

    err_no = strcmp((const char*)buffer, (const char*)res_validate);
    if (err_no != 0) {
        fprintf(stderr, "(%s)!=(%s)\n", buffer, res_validate);
    }

    return err_no;
}

int main()
{
    int err_no = 0;

    err_no += test_th_isaccept();
    err_no += test_th_validate();

    return err_no ? 1 : 0;
}

