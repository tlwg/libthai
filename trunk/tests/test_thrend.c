/*
 * test_thrend.c : Test suite for <thai/thrend.h> functions
 * Created: 2001-08-10
 * Author:  Theppitak Karoonboonyanan
 */

#include <thai/thrend.h>
#include <string.h>
#include <stdio.h>

static const thchar_t test_msg[] = "¾èÍ»Ùè¾Õè»Õè®Ø°Ø­Ø¡Ó»Ó¡éÓ»éÓ»Óé·èÕ¡ç»ç¡Ôíà¡×çÍ¡";
static const thchar_t ans_tis[] = "¾èÍ»Ùè¾Õè»Õè®Ø°Ø­Ø¡íÒ»íÒ¡íéÒ»íéÒ»íÒ\xddé·è\xddÕ¡ç»ç¡Ôíà¡×çÍ¡";
static const thchar_t ans_tis_nd[] = "¾èÍ»Ùè¾Õè»Õè®Ø°Ø­Ø¡Ó»Ó¡éÓ»éÓ»Ó\xddé·è\xddÕ¡ç»ç¡Ôíà¡×çÍ¡";
static const thglyph_t ans_win_nd[] = "¾\x8bÍ»Ù\x86¾Õè»\x82\x9b®\xfc\x80Ø\x90Ø¡Ó»Ó¡\x8cÓ»\x87Ó»Ó\xdd\x8c·\x8b\xddÕ¡ç»\x9a¡Ôíà¡×çÍ¡";
static const thglyph_t ans_win[] = "¾\x8bÍ»Ù\x86¾Õè»\x82\x9b®\xfc\x80Ø\x90Ø¡íÒ»\x99Ò¡íéÒ»\x99\x9cÒ»\x99Ò\xdd\x8c·\x8b\xddÕ¡ç»\x9a¡Ôíà¡×çÍ¡";
static const thglyph_t ans_mac_nd[] = "¾\x88Í»Ù\x83¾Õè»\x95\x98®\xfc\x80Ø\x90Ø¡Ó»Ó¡\x89Ó»\x84Ó»Ó\xdd\x89·\x88\xddÕ¡ç»\x93¡Ôíà¡×çÍ¡";
static const thglyph_t ans_mac[] = "¾\x88Í»Ù\x83¾Õè»\x95\x98®\xfc\x80Ø\x90Ø¡íÒ»\x8fÒ¡íéÒ»\x8f\x99Ò»\x8fÒ\xdd\x89·\x88\xddÕ¡ç»\x93¡Ôíà¡×çÍ¡";

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

