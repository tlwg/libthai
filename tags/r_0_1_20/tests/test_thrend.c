/*
 * test_thrend.c : Test suite for <thai/thrend.h> functions
 * Created: 2001-08-10
 * Author:  Theppitak Karoonboonyanan
 */

#include <thai/thrend.h>
#include <string.h>
#include <stdio.h>

static const thchar_t test_msg[] = "��ͻ������ذحءӻӡ�ӻ�ӻ���ա�������͡";
static const thchar_t ans_tis[] = "��ͻ������ذحء�һ�ҡ��һ��һ��\xdd��\xddա�������͡";
static const thchar_t ans_tis_nd[] = "��ͻ������ذحءӻӡ�ӻ�ӻ�\xdd��\xddա�������͡";
static const thglyph_t ans_win_nd[] = "�\x8bͻ�\x86���\x82\x9b�\xfc\x80�\x90ءӻӡ\x8cӻ\x87ӻ�\xdd\x8c�\x8b\xddա�\x9a������͡";
static const thglyph_t ans_win[] = "�\x8bͻ�\x86���\x82\x9b�\xfc\x80�\x90ء�һ\x99ҡ��һ\x99\x9cһ\x99�\xdd\x8c�\x8b\xddա�\x9a������͡";
static const thglyph_t ans_mac_nd[] = "�\x88ͻ�\x83���\x95\x98�\xfc\x80�\x90ءӻӡ\x89ӻ\x84ӻ�\xdd\x89�\x88\xddա�\x93������͡";
static const thglyph_t ans_mac[] = "�\x88ͻ�\x83���\x95\x98�\xfc\x80�\x90ء�һ\x8fҡ��һ\x8f\x99һ\x8f�\xdd\x89�\x88\xddա�\x93������͡";

int test_th_render_tis()
{
    thglyph_t rend_buff[80];
    int err_no = 0;

    fprintf(stderr, "Testing th_render_text_tis() w/o decomposing SARA AM\n");
    th_render_text_tis(test_msg, rend_buff, sizeof rend_buff, 0);
    if (strcmp((const char*)rend_buff, (const char*)ans_tis_nd) != 0) {
        fprintf(stderr, "(%s)!=(%s)\n", rend_buff, ans_tis_nd);
        ++err_no;
    }
    fprintf(stderr, "Testing th_render_text_tis() decomposing SARA AM\n");
    th_render_text_tis(test_msg, rend_buff, sizeof rend_buff, 1);
    if (strcmp((const char*)rend_buff, (const char*)ans_tis) != 0) {
        fprintf(stderr, "(%s)!=(%s)\n", rend_buff, ans_tis);
        ++err_no;
    }

    return err_no;
}

int test_th_render_win()
{
    thglyph_t rend_buff[80];
    int err_no = 0;

    fprintf(stderr, "Testing th_render_text_win() w/o decomposing SARA AM\n");
    th_render_text_win(test_msg, rend_buff, sizeof rend_buff, 0);
    if (strcmp((const char*)rend_buff, (const char*)ans_win_nd) != 0) {
        fprintf(stderr, "(%s)!=(%s)\n", rend_buff, ans_win_nd);
        ++err_no;
    }
    fprintf(stderr, "Testing th_render_text_win() decomposing SARA AM\n");
    th_render_text_win(test_msg, rend_buff, sizeof rend_buff, 1);
    if (strcmp((const char*)rend_buff, (const char*)ans_win) != 0) {
        fprintf(stderr, "(%s)!=(%s)\n", rend_buff, ans_win);
        ++err_no;
    }

    return err_no;
}

int test_th_render_mac()
{
    thglyph_t rend_buff[80];
    int err_no = 0;

    fprintf(stderr, "Testing th_render_text_mac() w/o decomposing SARA AM\n");
    th_render_text_mac(test_msg, rend_buff, sizeof rend_buff, 0);
    if (strcmp((const char*)rend_buff, (const char*)ans_mac_nd) != 0) {
        fprintf(stderr, "(%s)!=(%s)\n", rend_buff, ans_mac_nd);
        ++err_no;
    }
    fprintf(stderr, "Testing th_render_text_mac() decomposing SARA AM\n");
    th_render_text_mac(test_msg, rend_buff, sizeof rend_buff, 1);
    if (strcmp((const char*)rend_buff, (const char*)ans_mac) != 0) {
        fprintf(stderr, "(%s)!=(%s)\n", rend_buff, ans_mac);
        ++err_no;
    }

    return err_no;
}

int main()
{
    int err_no = 0;

    err_no += test_th_render_tis();
    err_no += test_th_render_win();
    err_no += test_th_render_mac();

    return err_no;
}

