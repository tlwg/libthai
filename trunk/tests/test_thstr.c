#include <thai/thstr.h>
#include <string.h>

int test_th_normalize()
{
    const thchar_t* test_str = "��س��٫��٫���";
    const thchar_t* ans_str = "�س�������";
    thchar_t resBuff[50];

    th_normalize(resBuff, test_str, sizeof resBuff);
    return (strcmp(resBuff, ans_str) == 0) ? 0 : 1;
}

int main()
{
    return test_th_normalize();
}

