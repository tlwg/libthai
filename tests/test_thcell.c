#include <thai/thcell.h>
#include <thai/tis.h>
#include <string.h>
#include <stdio.h>

static const thchar_t test_msg[] = "¹éÓ¹Ó¡Õè¡èÕ¡Øè¡èØ¡Øì¡ìØ¡Ôì¡ìÔàÔàÓàé¹";
static const struct thcell_t test_ans_nodecomp_am[] = {
    { NONU, 0, MAITHO },
    { SARA_AM, 0, 0 },
    { NONU, 0, 0 },
    { SARA_AM, 0, 0 },
    { KOKAI, SARA_II, MAIEK },
    { KOKAI, 0, MAIEK },
    { 0, SARA_II, 0 },
    { KOKAI, SARA_U, MAIEK },
    { KOKAI, 0, MAIEK },
    { 0, SARA_U, 0 },
    { KOKAI, SARA_U, THANTHAKHAT },
    { KOKAI, 0, THANTHAKHAT },
    { 0, SARA_U, 0 },
    { KOKAI, SARA_I, THANTHAKHAT },
    { KOKAI, 0, THANTHAKHAT },
    { 0, SARA_I, 0 },
    { SARA_E, 0, 0 },
    { 0, SARA_I, 0 },
    { SARA_E, 0, 0 },
    { SARA_AM, 0, 0 },
    { SARA_E, 0, 0 },
    { 0, 0, MAITHO },
    { NONU, 0, 0 },
    { 0, 0, 0 }
};
static const struct thcell_t test_ans_decomp_am[] = {
    { NONU, SARA_AM, MAITHO },
    { NONU, SARA_AM, 0 },
    { KOKAI, SARA_II, MAIEK },
    { KOKAI, 0, MAIEK },
    { 0, SARA_II, 0 },
    { KOKAI, SARA_U, MAIEK },
    { KOKAI, 0, MAIEK },
    { 0, SARA_U, 0 },
    { KOKAI, SARA_U, THANTHAKHAT },
    { KOKAI, 0, THANTHAKHAT },
    { 0, SARA_U, 0 },
    { KOKAI, SARA_I, THANTHAKHAT },
    { KOKAI, 0, THANTHAKHAT },
    { 0, SARA_I, 0 },
    { SARA_E, 0, 0 },
    { 0, SARA_I, 0 },
    { SARA_E, 0, 0 },
    { 0, SARA_AM, 0 },
    { SARA_E, 0, 0 },
    { 0, 0, MAITHO },
    { NONU, 0, 0 },
    { 0, 0, 0 }
};

int test_th_next_cell()
{
    int   err_no = 0;
    const thchar_t *s;
    int   len;
    const struct thcell_t *pCell;

    fprintf(stderr, "testing without decomposing SARA AM...\n");
    pCell = test_ans_nodecomp_am;
    s = test_msg;
    len = strlen((const char *)test_msg);
    while (*s) {
        struct thcell_t aCell;
        size_t nChars;

        s = th_next_cell(s, len, &aCell, &nChars, 0);
        len -= nChars;
        if (aCell.base != pCell->base ||
            aCell.hilo != pCell->hilo ||
            aCell.top  != pCell->top)
        {
            fprintf(stderr, "(%c,%c,%c) != (%c,%c,%c)\n",
                    aCell.base, aCell.hilo, aCell.top,
                    pCell->base, pCell->hilo, pCell->top);
            ++err_no;
        }
        if (pCell->base || pCell->hilo || pCell->top)
            ++pCell;
    }

    fprintf(stderr, "testing decomposing SARA AM...\n");
    s = test_msg;
    len = strlen((const char *)test_msg);
    pCell = test_ans_decomp_am;
    while (*s) {
        struct thcell_t aCell;
        size_t nChars;

        s = th_next_cell(s, len, &aCell, &nChars, 1);
        len -= nChars;
        if (aCell.base != pCell->base ||
            aCell.hilo != pCell->hilo ||
            aCell.top  != pCell->top)
        {
            fprintf(stderr, "(%c,%c,%c) != (%c,%c,%c)\n",
                    aCell.base, aCell.hilo, aCell.top,
                    pCell->base, pCell->hilo, pCell->top);
            ++err_no;
        }
        if (pCell->base || pCell->hilo || pCell->top)
            ++pCell;
    }

    return err_no;
}

int test_th_prev_cell()
{
    int   err_no = 0;
    const thchar_t *s;
    int   pos;
    const struct thcell_t *pCell;

    fprintf(stderr, "testing without decomposing SARA AM...\n");
    pCell = test_ans_nodecomp_am +
            (sizeof test_ans_nodecomp_am)/(sizeof test_ans_nodecomp_am[0]) - 2;
    s = test_msg;
    pos = strlen((const char *)test_msg);
    while (pos > 0) {
        struct thcell_t aCell;
        size_t nChars;

        pos = th_prev_cell(s, pos, &aCell, &nChars, 0);
        if (aCell.base != pCell->base ||
            aCell.hilo != pCell->hilo ||
            aCell.top  != pCell->top)
        {
            fprintf(stderr, "(%c,%c,%c) != (%c,%c,%c)\n",
                    aCell.base, aCell.hilo, aCell.top,
                    pCell->base, pCell->hilo, pCell->top);
            ++err_no;
        }
        if (pCell > test_ans_nodecomp_am)
            --pCell;
    }

    fprintf(stderr, "testing decomposing SARA AM...\n");
    pCell = test_ans_decomp_am +
            (sizeof test_ans_decomp_am)/(sizeof test_ans_decomp_am[0]) - 2;
    s = test_msg;
    pos = strlen((const char *)test_msg);
    while (pos > 0) {
        struct thcell_t aCell;
        size_t nChars;

        pos = th_prev_cell(s, pos, &aCell, &nChars, 1);
        if (aCell.base != pCell->base ||
            aCell.hilo != pCell->hilo ||
            aCell.top  != pCell->top)
        {
            fprintf(stderr, "(%c,%c,%c) != (%c,%c,%c)\n",
                    aCell.base, aCell.hilo, aCell.top,
                    pCell->base, pCell->hilo, pCell->top);
            ++err_no;
        }
        if (pCell > test_ans_nodecomp_am)
            --pCell;
    }

    return err_no;
}

int main()
{
    int err_no = 0;

    err_no += test_th_next_cell();
    err_no += test_th_prev_cell();
    //err_no += test_th_make_cells();

    return err_no;
}

