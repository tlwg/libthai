/*
 * test_thstr.c : Test suite for <thai/thstr.h> functions
 * Created: 2001-08-03
 * Author:  Theppitak Karoonboonyanan
 */

#include <thai/thstr.h>
#include <string.h>

int test_th_normalize()
{
    const thchar_t* test_str = (const thchar_t *)"¤ØØ³»èÙ«èèÙ«èèÒ";
    const thchar_t* ans_str = (const thchar_t *)"¤Ø³»Ùè«Ùè«èÒ";
    thchar_t resBuff[50];

    th_normalize(resBuff, test_str, sizeof resBuff);
    return (strcmp((const char *)resBuff, (const char *)ans_str) == 0) ? 0 : 1;
}

int main()
{
    return test_th_normalize();
}

