/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * brk-maximal.c - Thai word break with maximal matching scheme
 * Created: 2006-08-20
 * Author:  Theppitak Karoonboonyanan <thep@linux.thai.net>
 */

#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <datrie/sb-trie.h>
#include <thai/tis.h>
#include <thai/thctype.h>
#include "brk-maximal.h"

#define DICT_NAME   "thbrk"

/**
 * @brief Break shot
 */
typedef struct _BrkShot {
    SBTrieState    *dict_state;
    int             str_pos;
    int            *brk_pos;
    int             n_brk_pos;
    int             cur_brk_pos;
    int             penalty;
} BrkShot;

static void         brk_shot_copy (BrkShot *dst, const BrkShot *src);
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
static BrkPool *    brk_pool_get_node (BrkPool *pool, const thchar_t *s);
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

static SBTrie *     brk_get_dict ();

static BrkPool *    brk_root_pool (int pos_size);
static int          brk_recover (const thchar_t *text, int len, int pos,
                                 RecovHist *rh);

#define th_isleadable(c) \
    (th_isthcons(c)||th_isldvowel(c)||(c)==RU||(c)==LU)

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
brk_maximal_do (const thchar_t *s, int len, int pos[], size_t n, int do_recover)
{
    BrkPool     *pool;
    BrkPool     *node;
    BestBrk     *best_brk;
    RecovHist    recov_hist;
    int          i;

    pool = brk_root_pool (n);
    best_brk = best_brk_new (n);
    recov_hist.pos = recov_hist.recov = -1;

    while (NULL != (node = brk_pool_get_node (pool, s))) {
        BrkShot *shot = &node->shot;
        BrkPool *match;
        int      is_keep_node, is_terminal, is_recovered;

        /* walk dictionary character-wise till a word is matched */
        is_keep_node = 1;
        is_recovered = 0;
        do {
            if (!sb_trie_state_walk (shot->dict_state, s[shot->str_pos++])) {
                int recovered;

                is_terminal = 0;

                if (!do_recover) {
                    is_keep_node = 0;
                    break;
                }

                /* try to recover from error */
                recovered = brk_recover (s, len, shot->str_pos, &recov_hist);
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

            is_terminal = sb_trie_state_is_terminal (shot->dict_state);
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
        } while (!(is_terminal && th_isleadable (s[shot->str_pos])));

        if (!is_keep_node && !do_recover) {
            pool = brk_pool_delete (pool, node);
            continue;
        }

        /* if node still kept, mark break position and rewind dictionary */
        if (is_keep_node && (is_terminal || is_recovered)) {
            if (shot->str_pos < len && is_terminal &&
                !sb_trie_state_is_leaf (shot->dict_state))
            {
                /* add node to mark break position instead of current */
                node = brk_pool_node_new (shot);
                pool = brk_pool_add (pool, node);
            }

            sb_trie_state_rewind (node->shot.dict_state);
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

                del_node = (match->shot.penalty < node->shot.penalty ||
                            (match->shot.penalty == node->shot.penalty &&
                            match->shot.cur_brk_pos < node->shot.cur_brk_pos))
                        ? node : match;
                if (del_node == node)
                    node = match;
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

    root_shot.dict_state = sb_trie_root (brk_get_dict());
    root_shot.brk_pos = (int *) malloc (pos_size * sizeof (int));
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
brk_recover (const thchar_t *text, int len, int pos, RecovHist *rh)
{
    int brk_pos[RECOVERED_WORDS];
    int n, p;

    while (pos < len && !th_isleadable (text[pos]) &&
           (0 == pos || !th_isldvowel (text[pos - 1])))
    {
        ++pos;
    }
    if (rh->pos == pos)
        return rh->recov;

    for (p = pos; p < len; ++p) {
        if (th_isleadable (text[p]) &&
            (0 == p || !th_isldvowel (text[p - 1])))
        {
            n = brk_maximal_do (text + p, len - p, brk_pos, RECOVERED_WORDS, 0);
            if (n == RECOVERED_WORDS || (n > 0 && '\0' == text[brk_pos[n-1]])) {
                rh->pos = pos;
                rh->recov = p;
                return p;
            }
        }
    }

    return -1;
}

static SBTrie *
brk_get_dict ()
{
    static SBTrie *brk_dict = 0;

    if (!brk_dict)
        brk_dict = sb_trie_open (DICT_DIR, DICT_NAME, TRIE_IO_READ);

    return brk_dict;
}

static void
brk_shot_copy (BrkShot *dst, const BrkShot *src)
{
    int i;

    dst->dict_state = sb_trie_state_clone (src->dict_state);
    dst->str_pos = src->str_pos;
    dst->brk_pos = (int *) malloc (src->n_brk_pos * sizeof (int));
    for (i = 0; i < src->cur_brk_pos; i++)
        dst->brk_pos[i] = src->brk_pos[i];
    dst->n_brk_pos = src->n_brk_pos;
    dst->cur_brk_pos = src->cur_brk_pos;
    dst->penalty = src->penalty;
}

static void
brk_shot_destruct (BrkShot *shot)
{
    if (shot->dict_state)
        sb_trie_state_free (shot->dict_state);
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
    } else {
        node = (BrkPool *) malloc (sizeof (BrkPool));
        if (!node)
            return NULL;
    }

    node->next = NULL;
    brk_shot_copy (&node->shot, shot);

    return node;
}

static void
brk_pool_free_node (BrkPool *pool)
{
    brk_shot_destruct (&pool->shot);

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
brk_pool_get_node (BrkPool *pool, const thchar_t *s)
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
        int i;

        for (i = 0; i < shot->cur_brk_pos; i++)
            best_brk->brk_pos[i] = shot->brk_pos[i];
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
