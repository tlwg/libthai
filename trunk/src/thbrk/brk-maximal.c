/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * brk-maximal.c - Thai word break with maximal matching scheme
 * Created: 2006-08-20
 * Author:  Theppitak Karoonboonyanan <thep@linux.thai.net>
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <datrie/trie.h>
#include <thai/tis.h>
#include <thai/thctype.h>
#include <thai/thwchar.h>
#include "brk-maximal.h"

#define DICT_NAME   "thbrk"

/**
 * @brief Break shot
 */
typedef struct _BrkShot {
    TrieState      *dict_state;
    int             str_pos;
    int            *brk_pos;
    int             n_brk_pos;
    int             cur_brk_pos;
    int             penalty;
} BrkShot;

static void         brk_shot_init (BrkShot *dst, const BrkShot *src);
static void         brk_shot_reuse (BrkShot *dst, const BrkShot *src);
static void         brk_shot_destruct (BrkShot *shot);

/**
 * @brief Break pool
 */

typedef struct _BrkPool BrkPool;

struct _BrkPool {
    BrkPool        *next;
    BrkShot         shot;
};

static void         brk_pool_allocator_use ();
static void         brk_pool_allocator_clear ();

static BrkPool *    brk_pool_node_new (const BrkShot *shot);

static void         brk_pool_free (BrkPool *pool);
static BrkPool *    brk_pool_get_node (BrkPool *pool);
static BrkPool *    brk_pool_match (BrkPool *pool, BrkPool *node);
static BrkPool *    brk_pool_add (BrkPool *pool, BrkPool *node);
static BrkPool *    brk_pool_delete (BrkPool *pool, BrkPool *node);

/**
 * @brief Best break solution
 */
typedef struct {
    int    *brk_pos;
    int     n_brk_pos;
    int     cur_brk_pos;
    int     str_pos;
    int     penalty;
} BestBrk;

static BestBrk *    best_brk_new (int n_brk_pos);
static void         best_brk_free (BestBrk *best_brk);
static int          best_brk_contest (BestBrk *best_brk, const BrkShot *shot);

/**
 * @brief Recover history
 */
typedef struct {
    int     pos;
    int     recov;
} RecovHist;

/*----------------------------------*
 *   PRIVATE METHODS DECLARATIONS   *
 *----------------------------------*/

static void         th_brkpos_hints (const thchar_t *str, int len, char *hints);

static Trie *       brk_get_dict ();

static BrkPool *    brk_root_pool (int pos_size);
static int          brk_maximal_do_impl (const thchar_t *s, int len,
                                         const char *brkpos_hints,
                                         int pos[], size_t n,
                                         int do_recover);
static int          brk_recover (const thchar_t *text, int len, int pos,
                                 const char *brkpos_hints, RecovHist *rh);

static void
th_brkpos_hints (const thchar_t *str, int len, char *hints)
{
    int  i;

    if (len < 0)
        len = strlen ((const char *)str);

    memset (hints, 0, len);

    for (i = 0; i < len; /* nop */) {
        if (th_isthcons (str[i])) {
            if (i+1 < len && str[i+1] == THANTHAKHAT) {
                i += 2; /* the cons + THANTHAKHAT */
            } else if (i+2 < len && str[i+2] == THANTHAKHAT) {
                i += 3; /* the cons + intermediate char + THANTHAKHAT */
            } else if (i+2 < len && str[i] != KOKAI && str[i+1] == MAITAIKHU
                       && (str[i+2] == OANG || str[i+2] == WOWAEN))
            {
                hints[i] = 1;
                i += 4; /* the cons + MAITAIKHU + OANG/WOWAEN + cons */
            } else if ((i > 0
                        && (str[i-1] == MAIHUNAKAT || str[i-1] == SARA_UEE))
                       || (i > 1 && th_isthtone (str[i-1])
                           && (str[i-2] == MAIHUNAKAT || str[i-2] == SARA_UEE)))
            {
                i++;
            } else {
                hints[i++] = 1;
            }
        } else if (str[i] == SARA_E || str[i] == SARA_AE) {
            hints[i] = 1; /* sara e/ae */
            i += 2; /* sara e/ae + the supposedly cons */
            if (i >= len)
                break;
            if (str[i] == MAITAIKHU) {
               i += 2; /* MAITAIKHU + the supposedly cons */
            } else if (th_isupvowel (str[i])) {
               i++; /* the upper vowel, as part of composite vowel */
               if (i < len && th_isthtone (str[i]))
                   i++;
               i++; /* the supposedly cons */
            } else if (i+2 < len && str[i] != KOKAI && str[i+1] == MAITAIKHU
                       && str[i+2] != OANG && str[i+2] != WOWAEN)
            {
               i += 3; /* 2nd cons + MAITAIKHU + final cons */
            }
        } else if (th_isldvowel (str[i])) {
            hints[i] = 1; /* the ldvowel */
            i += 2; /* the ldvowel + the supposedly cons */
        } else if (str[i] == RU || str[i] == LU) {
            hints[i++] = 1;
        } else {
            i++;
        }
    }
}

/*---------------------*
 *   PRIVATE GLOBALS   *
 *---------------------*/
static Trie *brk_dict = 0;

void
brk_maximal_on_unload ()
{
    if (brk_dict) {
        trie_free (brk_dict);
    }
}

void
brk_maximal_init ()
{
    brk_pool_allocator_use ();
}

void
brk_maximal_quit ()
{
    brk_pool_allocator_clear ();
}

int
brk_maximal_do (const thchar_t *s, int len, int pos[], size_t n)
{
    char        *brkpos_hints;
    int          ret;

    brkpos_hints = (char *) malloc (len);
    th_brkpos_hints (s, len, brkpos_hints);

    ret = brk_maximal_do_impl (s, len, brkpos_hints, pos, n, 1);

    free (brkpos_hints);

    return ret;
}

static int
brk_maximal_do_impl (const thchar_t *s, int len,
                     const char *brkpos_hints,
                     int pos[], size_t n,
                     int do_recover)
{
    BrkPool     *pool;
    BrkPool     *node;
    BestBrk     *best_brk;
    RecovHist    recov_hist;
    int          i;

    pool = brk_root_pool (n);
    best_brk = best_brk_new (n);
    recov_hist.pos = recov_hist.recov = -1;

    while (NULL != (node = brk_pool_get_node (pool))) {
        BrkShot *shot = &node->shot;
        BrkPool *match;
        int      is_keep_node, is_terminal, is_recovered;

        /* walk dictionary character-wise till a word is matched */
        is_keep_node = 1;
        is_recovered = 0;
        do {
            if (!trie_state_walk (shot->dict_state,
                                  th_tis2uni (s[shot->str_pos++])))
            {
                int recovered;

                is_terminal = 0;

                if (!do_recover) {
                    is_keep_node = 0;
                    break;
                }

                /* try to recover from error */
                recovered = brk_recover (s, len, shot->str_pos,
                                         brkpos_hints, &recov_hist);
                if (-1 != recovered) {
                    /* add penalty by recovered - recent break pos */
                    shot->penalty += recovered;
                    if (shot->cur_brk_pos > 0)
                        shot->penalty -= shot->brk_pos[shot->cur_brk_pos - 1];

                    shot->str_pos = recovered;
                    is_recovered = 1;
                } else {
                    /* add penalty with string len - recent break pos */
                    shot->penalty += len;
                    if (shot->cur_brk_pos > 0)
                        shot->penalty -= shot->brk_pos[shot->cur_brk_pos - 1];

                    is_keep_node = 0;
                }
                break;
            }

            is_terminal = trie_state_is_terminal (shot->dict_state);
            if (shot->str_pos >= len) {
                if (!is_terminal) {
                    /* add penalty with string len - recent break pos */
                    shot->penalty += len;
                    if (shot->cur_brk_pos > 0)
                        shot->penalty -= shot->brk_pos[shot->cur_brk_pos - 1];

                    is_keep_node = 0;
                }
                break;
            }
        } while (!(is_terminal && brkpos_hints[shot->str_pos]));

        if (!is_keep_node && !do_recover) {
            pool = brk_pool_delete (pool, node);
            continue;
        }

        /* if node still kept, mark break position and rewind dictionary */
        if (is_keep_node && (is_terminal || is_recovered)) {
            if (shot->str_pos < len && is_terminal &&
                !trie_state_is_single (shot->dict_state))
            {
                /* add node to mark break position instead of current */
                node = brk_pool_node_new (shot);
                pool = brk_pool_add (pool, node);
            }

            trie_state_rewind (node->shot.dict_state);
            node->shot.brk_pos [node->shot.cur_brk_pos++] = node->shot.str_pos;
        }

        if (!is_keep_node ||
            node->shot.str_pos == len || node->shot.cur_brk_pos >= n)
        {
            /* path is done; contest and remove */
            best_brk_contest (best_brk, &node->shot);
            pool = brk_pool_delete (pool, node);

            /* if in recovery mode, stop as soon as first solution is found */
            if (!do_recover)
                break;
        } else {
            /* find matched nodes, contest and keep the best one */
            while (NULL != (match = brk_pool_match (pool, node))) {
                BrkPool *del_node;

                if (match->shot.penalty < node->shot.penalty ||
                    (match->shot.penalty == node->shot.penalty &&
                     match->shot.cur_brk_pos < node->shot.cur_brk_pos))
                {
                    del_node = node;
                    node = match;
                } else {
                    del_node = match;
                }
                pool = brk_pool_delete (pool, del_node);
            }
        }
    }

    for (i = 0; i < best_brk->cur_brk_pos; i++)
        pos[i] = best_brk->brk_pos[i];

    brk_pool_free (pool);
    best_brk_free (best_brk);
    return i;
}

static BrkPool *
brk_root_pool (int pos_size)
{
    BrkPool    *pool;
    BrkPool    *node;
    BrkShot     root_shot;

    pool = NULL;

    root_shot.dict_state = trie_root (brk_get_dict());
    root_shot.brk_pos = NULL; /* it's not used anyway */
    root_shot.n_brk_pos = pos_size;
    root_shot.str_pos = root_shot.cur_brk_pos = 0;
    root_shot.penalty = 0;

    node = brk_pool_node_new (&root_shot);
    pool = brk_pool_add (pool, node);

    brk_shot_destruct (&root_shot);

    return pool;
}

#define RECOVERED_WORDS 2

static int
brk_recover (const thchar_t *text, int len, int pos,
             const char *brkpos_hints, RecovHist *rh)
{
    int brk_pos[RECOVERED_WORDS];
    int n, p;

    while (pos < len && !brkpos_hints[pos])
    {
        ++pos;
    }
    if (rh->pos == pos)
        return rh->recov;

    for (p = pos; p < len; ++p) {
        if (brkpos_hints[p]) {
            n = brk_maximal_do_impl (text + p, len - p, brkpos_hints + p,
                                     brk_pos, RECOVERED_WORDS, 0);
            if (n == RECOVERED_WORDS || (n > 0 && '\0' == text[brk_pos[n-1]])) {
                rh->pos = pos;
                rh->recov = p;
                return p;
            }
        }
    }

    return -1;
}

static Trie *
brk_get_dict ()
{
    char   path[512];

    if (!brk_dict) {
        const char *dict_dir;

        /* Try LIBTHAI_DICTDIR env first */
        if (NULL != (dict_dir = getenv ("LIBTHAI_DICTDIR"))) {
            snprintf (path, sizeof path, "%s/%s.tri", dict_dir, DICT_NAME);
            brk_dict = trie_new_from_file (path);
        }

        /* Then, fall back to default DICT_DIR macro */
        if (!brk_dict) {
            brk_dict = trie_new_from_file (DICT_DIR "/" DICT_NAME ".tri");
        }
    }

    return brk_dict;
}

static void
brk_shot_init (BrkShot *dst, const BrkShot *src)
{
    dst->dict_state = trie_state_clone (src->dict_state);
    dst->str_pos = src->str_pos;
    dst->brk_pos = (int *) malloc (src->n_brk_pos * sizeof (int));
    memcpy (dst->brk_pos, src->brk_pos, src->cur_brk_pos * sizeof (int));
    dst->n_brk_pos = src->n_brk_pos;
    dst->cur_brk_pos = src->cur_brk_pos;
    dst->penalty = src->penalty;
}

static void
brk_shot_reuse (BrkShot *dst, const BrkShot *src)
{
    trie_state_copy (dst->dict_state, src->dict_state);
    dst->str_pos = src->str_pos;
    if (dst->n_brk_pos < src->n_brk_pos) {
        dst->brk_pos = (int *) realloc (dst->brk_pos,
                                        src->n_brk_pos * sizeof (int));
    }
    memcpy (dst->brk_pos, src->brk_pos, src->cur_brk_pos * sizeof (int));
    dst->n_brk_pos = src->n_brk_pos;
    dst->cur_brk_pos = src->cur_brk_pos;
    dst->penalty = src->penalty;
}

static void
brk_shot_destruct (BrkShot *shot)
{
    if (shot->dict_state)
        trie_state_free (shot->dict_state);
    if (shot->brk_pos)
        free (shot->brk_pos);
}

static BrkPool *brk_pool_free_list = NULL;
static int      brk_pool_allocator_refcnt = 0;

static void
brk_pool_allocator_use ()
{
    ++brk_pool_allocator_refcnt;
}

static void
brk_pool_allocator_clear ()
{
    if (--brk_pool_allocator_refcnt > 0)
        return;

    while (brk_pool_free_list) {
        BrkPool *next;

        next = brk_pool_free_list->next;
        brk_shot_destruct (&brk_pool_free_list->shot);
        free (brk_pool_free_list);
        brk_pool_free_list = next;
    }
}

static BrkPool *
brk_pool_node_new (const BrkShot *shot)
{
    BrkPool *node;

    if (brk_pool_free_list) {
        /* reuse old node if possible */
        node = brk_pool_free_list;
        brk_pool_free_list = brk_pool_free_list->next;
        brk_shot_reuse (&node->shot, shot);
    } else {
        node = (BrkPool *) malloc (sizeof (BrkPool));
        if (!node)
            return NULL;
        brk_shot_init (&node->shot, shot);
    }

    node->next = NULL;

    return node;
}

static void
brk_pool_free_node (BrkPool *pool)
{
    /* put it in free list for further reuse */
    pool->next = brk_pool_free_list;
    brk_pool_free_list = pool;
}

static void
brk_pool_free (BrkPool *pool)
{
    while (pool) {
        BrkPool *next;

        next = pool->next;
        brk_pool_free_node (pool);
        pool = next;
    }
}

static BrkPool *
brk_pool_get_node (BrkPool *pool)
{
    int      min_pos;
    BrkPool *chosen;

    /* find node with least progress */
    chosen = NULL;
    min_pos = INT_MAX;
    while (pool) {
        int pos;

        if (0 == pool->shot.cur_brk_pos)
            return pool;

        pos = pool->shot.brk_pos[pool->shot.cur_brk_pos - 1];
        if (pos < min_pos) {
            min_pos = pos;
            chosen = pool;
        }
        pool = pool->next;
    }

    return chosen;
}

static BrkPool *
brk_pool_match (BrkPool *pool, BrkPool *node)
{
    int node_cur_pos;

    node_cur_pos = node->shot.cur_brk_pos;
    while (pool) {
        if (pool != node) {
            if (node_cur_pos == 0) {
                if (pool->shot.cur_brk_pos == 0)
                    break;
            } else {
                if (pool->shot.cur_brk_pos > 0 &&
                    pool->shot.brk_pos[pool->shot.cur_brk_pos - 1]
                        == node->shot.brk_pos[node_cur_pos - 1])
                {
                    break;
                }
            }
        }
        pool = pool->next;
    }
    return pool;
}

static BrkPool *
brk_pool_add (BrkPool *pool, BrkPool *node)
{
    node->next = pool;
    return node;
}

static BrkPool *
brk_pool_delete (BrkPool *pool, BrkPool *node)
{
    if (pool == node) {
        pool = pool->next;
    } else {
        BrkPool *p;

        for (p = pool; p && p->next != node; p = p->next)
            ;
        if (p)
            p->next = node->next;
    }
    brk_pool_free_node (node);

    return pool;
}

static BestBrk *
best_brk_new (int n_brk_pos)
{
    BestBrk *best_brk;

    best_brk = (BestBrk *) malloc (sizeof (BestBrk));
    if (!best_brk)
        return NULL;

    best_brk->brk_pos = (int *) malloc (n_brk_pos * sizeof (int));
    if (!best_brk->brk_pos)
        goto exit1;
    best_brk->n_brk_pos = n_brk_pos;
    best_brk->cur_brk_pos = best_brk->str_pos = 0;
    best_brk->penalty = 0;

    return best_brk;

exit1:
    free (best_brk);
    return NULL;
}

static void
best_brk_free (BestBrk *best_brk)
{
    free (best_brk->brk_pos);
    free (best_brk);
}

static int
best_brk_contest (BestBrk *best_brk, const BrkShot *shot)
{
    if (shot->str_pos > best_brk->str_pos ||
        (shot->str_pos == best_brk->str_pos &&
         (shot->penalty < best_brk->penalty ||
          (shot->penalty == best_brk->penalty &&
           shot->cur_brk_pos <= best_brk->cur_brk_pos))))
    {
        memcpy (best_brk->brk_pos, shot->brk_pos,
                shot->cur_brk_pos * sizeof (int));
        best_brk->cur_brk_pos = shot->cur_brk_pos;
        best_brk->str_pos = shot->str_pos;
        best_brk->penalty = shot->penalty;

        return 1;
    }
    return 0;
}

/*
vi:ts=4:ai:expandtab
*/