/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * thbrk.c - Thai word break routine
 * Created: 2006-08-20
 * Author:  Theppitak Karoonboonyanan <thep@linux.thai.net>
 */

#include <stdlib.h>
#include <limits.h>
#include <datrie/sb-trie.h>
#include <thai/thctype.h>
#include <thai/thbrk.h>

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
} BestBrk;

static BestBrk *    best_brk_new (int n_brk_pos);
static void         best_brk_free (BestBrk *best_brk);
static int          best_brk_contest (BestBrk *best_brk, const BrkShot *shot);

/*----------------------------------*
 *   PRIVATE METHODS DECLARATIONS   *
 *----------------------------------*/

static SBTrie *     brk_get_dict ();

static BrkPool *    brk_root_pool (int pos_size);
static int          brk_do (const thchar_t *s, int pos[], size_t n,
                            int do_recover);
static int          brk_recover (const thchar_t *text, int pos);

int
th_brk (const thchar_t *s, int pos[], size_t n)
{
    return brk_do (s, pos, n, 1);
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

    node = brk_pool_node_new (&root_shot);
    pool = brk_pool_add (pool, node);

    brk_shot_destruct (&root_shot);

    return pool;
}

static int
brk_do (const thchar_t *s, int pos[], size_t n, int do_recover)
{
    BrkPool     *pool;
    BrkPool     *node;
    BestBrk     *best_brk;
    int          i;

    pool = brk_root_pool (n);
    best_brk = best_brk_new (n);

    while (NULL != (node = brk_pool_get_node (pool, s))) {
        BrkShot *shot = &node->shot;
        BrkPool *match;
        int      keep_on;

        /* walk dictionary character-wise till a word is matched */
        keep_on = 1;
        do {
            if (!sb_trie_state_walk (shot->dict_state, s[shot->str_pos++])) {
                int recovered;

                /* try to recover from error first */
                if (do_recover &&
                    (recovered = brk_recover (s, shot->str_pos)) != -1)
                {
                    shot->str_pos = recovered;
                    sb_trie_state_rewind (shot->dict_state);
                    if (s[shot->str_pos]) {
                        shot->brk_pos [shot->cur_brk_pos++] = shot->str_pos;
                        if (shot->cur_brk_pos >= n) {
                            best_brk_contest (best_brk, shot);
                            pool = brk_pool_delete (pool, node);
                            keep_on = 0;
                        }
                    }
                } else {
                    best_brk_contest (best_brk, shot);
                    pool = brk_pool_delete (pool, node);
                    keep_on = 0;
                }
            }
        } while (keep_on && s[shot->str_pos]
                 && !sb_trie_state_is_terminal (shot->dict_state));

        if (!keep_on)
            continue;

        if (s[shot->str_pos] && !sb_trie_state_is_leaf (shot->dict_state)) {
            /* add node to mark break position instead of current */
            node = brk_pool_node_new (shot);
            pool = brk_pool_add (pool, node);
        }

        sb_trie_state_rewind (node->shot.dict_state);
        node->shot.brk_pos [node->shot.cur_brk_pos++] = node->shot.str_pos;

        if ('\0' == s[node->shot.str_pos] || node->shot.cur_brk_pos >= n) {
            /* path is done; contest and remove */
            best_brk_contest (best_brk, &node->shot);
            pool = brk_pool_delete (pool, node);
        } else if (NULL != (match = brk_pool_match (pool, node))) {
            BrkPool *del_node;

            /* break pos matches another node, contest and keep better one */
            del_node = (match->shot.cur_brk_pos < node->shot.cur_brk_pos)
                       ? node : match;
            pool = brk_pool_delete (pool, del_node);
        }
    }

    for (i = 0; i < best_brk->cur_brk_pos; i++)
        pos[i] = best_brk->brk_pos[i];

    brk_pool_free (pool);
    best_brk_free (best_brk);
    return i;
}

#define RECOVERED_WORDS 2
#define th_isleadable(c) \
    (th_isthcons(c)||th_isldvowel(c)||th_isthdigit(c))

static int
brk_recover (const thchar_t *text, int pos)
{
    int brk_pos[RECOVERED_WORDS];
    int n;

    while (text[pos]) {
        if (th_isleadable (text[pos])) {
            n = brk_do (text + pos, brk_pos, RECOVERED_WORDS, 0);
            if (n == RECOVERED_WORDS || (n > 0 && '\0' == text[brk_pos[n-1]]))
                return pos;
        }
        ++pos;
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
}

static void
brk_shot_destruct (BrkShot *shot)
{
    if (shot->dict_state)
        sb_trie_state_free (shot->dict_state);
    if (shot->brk_pos)
        free (shot->brk_pos);
}

static BrkPool *
brk_pool_node_new (const BrkShot *shot)
{
    BrkPool *node;

    node = (BrkPool *) malloc (sizeof (BrkPool));
    if (!node)
        return NULL;

    node->next = NULL;
    brk_shot_copy (&node->shot, shot);

    return node;
}

static void
brk_pool_free_node (BrkPool *pool)
{
    brk_shot_destruct (&pool->shot);
    free (pool);
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
    BrkPool *p, *q;

    for (p = pool, q = NULL; p && p != node; p = p->next)
        q = p;

    if (q)
        q->next = node->next;
    else if (pool)
        pool = pool->next;
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
         shot->cur_brk_pos < best_brk->cur_brk_pos))
    {
        int i;

        for (i = 0; i < shot->cur_brk_pos; i++)
            best_brk->brk_pos[i] = shot->brk_pos[i];
        best_brk->cur_brk_pos = shot->cur_brk_pos;
        best_brk->str_pos = shot->str_pos;

        return 1;
    }
    return 0;
}

/*
vi:ts=4:ai:expandtab
*/
