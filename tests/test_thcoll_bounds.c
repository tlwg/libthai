/* Regression test for leading vowels at the end of Thai strings. */
#include <thai/thcoll.h>

int
main (void)
{
    const thchar_t a[] = { 0xe8, 0xe0, 0 };
    const thchar_t b[] = { 0xe9, 0xe0, 0 };
    const thchar_t word_a[] = { 0xe8, 0xe0, 0xa1, 0 };
    const thchar_t word_b[] = { 0xe9, 0xe0, 0xa1, 0 };

    if (th_strcoll (a, b) >= 0 || th_strcoll (b, a) <= 0)
        return 1;
    if (th_strcoll (a, a) != 0)
        return 1;
    if (th_strcoll (word_a, word_b) >= 0 ||
        th_strcoll (word_b, word_a) <= 0)
        return 1;
    return 0;
}
