/*
 * $Id: test_thcell.c,v 1.8 2006-03-13 15:02:30 thep Exp $
 * test_thcell.c : Test suite for <thai/thcell.h> functions
 * Created: 2001-08-09
 * Author:  Theppitak Karoonboonyanan
 */

#include <thai/thcell.h>
#include <thai/tis.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static const thchar_t test_msg[] = "¹éÓ¹ÓÓ¡Õè¡èÕ¡Øè¡èØ¡Øì¡ìØ¡Ôì¡ìÔàÔàÓàé¹¡Ôí¡×ç";
static const struct thcell_t test_ans_nodecomp_am[] = {
    { NONU, 0, MAITHO },
    { SARA_AM, 0, 0 },
    { NONU, 0, 0 },
    { SARA_AM, 0, 0 },
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
    { KOKAI, SARA_I, NIKHAHIT },
    { KOKAI, SARA_UEE, MAITAIKHU },
    { 0, 0, 0 }
};
static const struct thcell_t test_ans_decomp_am[] = {
    { NONU, SARA_AM, MAITHO },
    { NONU, SARA_AM, 0 },
    { 0, SARA_AM, 0 },
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
    { KOKAI, SARA_I, NIKHAHIT },
    { KOKAI, SARA_UEE, MAITAIKHU },
    { 0, 0, 0 }
};

int test_th_next_cell()
{
    int   err_no = 0;
    const thchar_t *s;
    int   len;
    const struct thcell_t *pCell;

    fprintf(stderr, "testing th_next_cell() without decomposing SARA AM...\n");
    pCell = test_ans_nodecomp_am;
    s = test_msg;
    len = strlen((const char *)test_msg);
    while (*s) {
        struct thcell_t aCell;
        size_t nChars;

        nChars = th_next_cell(s, len, &aCell, 0);
        s += nChars; len -= nChars;
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

    fprintf(stderr, "testing th_next_cell() decomposing SARA AM...\n");
    s = test_msg;
    len = strlen((const char *)test_msg);
    pCell = test_ans_decomp_am;
    while (*s) {
        struct thcell_t aCell;
        size_t nChars;

        nChars = th_next_cell(s, len, &aCell, 1);
        s += nChars; len -= nChars;
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

    fprintf(stderr, "testing th_prev_cell() without decomposing SARA AM...\n");
    pCell = test_ans_nodecomp_am +
            (sizeof test_ans_nodecomp_am)/(sizeof test_ans_nodecomp_am[0]) - 2;
    s = test_msg;
    pos = strlen((const char *)test_msg);
    while (pos > 0) {
        struct thcell_t aCell;

        pos -= th_prev_cell(s, pos, &aCell, 0);
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

    fprintf(stderr, "testing th_prev_cell() decomposing SARA AM...\n");
    pCell = test_ans_decomp_am +
            (sizeof test_ans_decomp_am)/(sizeof test_ans_decomp_am[0]) - 2;
    s = test_msg;
    pos = strlen((const char *)test_msg);
    while (pos > 0) {
        struct thcell_t aCell;

        pos -= th_prev_cell(s, pos, &aCell, 1);
        if (aCell.base != pCell->base ||
            aCell.hilo != pCell->hilo ||
            aCell.top  != pCell->top)
        {
            fprintf(stderr, "(%c,%c,%c) != (%c,%c,%c)\n",
                    aCell.base, aCell.hilo, aCell.top,
                    pCell->base, pCell->hilo, pCell->top);
            ++err_no;
        }
        if (pCell > test_ans_decomp_am)
            --pCell;
    }

    return err_no;
}

#define TESTCELLS 10

int test_th_make_cells()
{
    int err_no = 0;
    struct thcell_t *cells;
    const thchar_t *s;
    int   len;
    const struct thcell_t *pCell;

    cells = (struct thcell_t *) malloc(TESTCELLS * sizeof(struct thcell_t));

    fprintf(stderr, "testing th_make_cells() without decomposing SARA AM...\n");
    pCell = test_ans_nodecomp_am;
    s = test_msg;
    len = strlen((const char *)test_msg);

    while (*s) {
        size_t nCells = TESTCELLS;
        size_t i;
        size_t nChars = th_make_cells(s, len, cells, &nCells, 0);
        s += nChars; len -= nChars;
        for (i = 0; i < nCells; ++i) {
            if (cells[i].base != pCell->base ||
                cells[i].hilo != pCell->hilo ||
                cells[i].top  != pCell->top)
            {
                fprintf(stderr, "(%c,%c,%c) != (%c,%c,%c)\n",
                        cells[i].base, cells[i].hilo, cells[i].top,
                        pCell->base, pCell->hilo, pCell->top);
                ++err_no;
            }
            if (pCell->base || pCell->hilo || pCell->top)
                ++pCell;
        }
    }

    fprintf(stderr, "testing th_make_cells() decomposing SARA AM...\n");
    pCell = test_ans_decomp_am;
    s = test_msg;
    len = strlen((const char *)test_msg);

    while (*s) {
        size_t nCells = TESTCELLS;
        size_t i;
        size_t nChars = th_make_cells(s, len, cells, &nCells, 1);
        s += nChars; len -= nChars;
        for (i = 0; i < nCells; ++i) {
            if (cells[i].base != pCell->base ||
                cells[i].hilo != pCell->hilo ||
                cells[i].top  != pCell->top)
            {
                fprintf(stderr, "(%c,%c,%c) != (%c,%c,%c)\n",
                        cells[i].base, cells[i].hilo, cells[i].top,
                        pCell->base, pCell->hilo, pCell->top);
                ++err_no;
            }
            if (pCell->base || pCell->hilo || pCell->top)
                ++pCell;
        }
    }

    free(cells);

    return err_no;
}

int main()
{
    int err_no = 0;

    err_no += test_th_next_cell();
    err_no += test_th_prev_cell();
    err_no += test_th_make_cells();

    return err_no;
}

