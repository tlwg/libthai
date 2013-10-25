/*
 * test_thinp.c : Test suite for <thai/thinp.h> functions
 * Created: 2001-08-09
 * Author:  Theppitak Karoonboonyanan
 */

#include <thai/thinp.h>
#include <string.h>
#include <stdio.h>

const thchar_t test_keys[] = "��ӹ�����ա���ء���ء������������ѹ�ѹ��Թ������";
const thchar_t res_level0[] = "��ӹ�����ա���ء���ء������������ѹ�ѹ��Թ������";
const thchar_t res_level1[] = "��ӹӡ��������������������������";
const thchar_t res_level2[] = "��ӹӡ��������������������";
const thchar_t res_validate[] = "��ӹ�ӡ�����������������ѹѹ�������";

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
            strcpy((char *)&buffer[cur_pos + conv.offset],
                   (const char *)conv.conv);
            cur_pos += conv.offset + strlen((const char *)conv.conv);
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

