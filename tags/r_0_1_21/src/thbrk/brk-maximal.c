/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * libthai - Thai Language Support Library
 * Copyright (C) 2001  Theppitak Karoonboonyanan <thep@linux.thai.net>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

/*
 * brk-maximal.c - Thai word break with maximal matching scheme
 * Created: 2006-08-20
 * Author:  Theppitak Karoonboonyanan <thep@linux.thai.net>
 */

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <datrie/trie.h>
#include <thai/tis.h>
#include <thai/thwchar.h>
#include "brk-maximal.h"
#include "brk-common.h"

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

static int          brk_shot_init (BrkShot *dst, const BrkShot *src);
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
static void         brk_pool_node_free (BrkPool *pool);

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

static BrkPool *    brk_root_pool (int pos_size);
static int          brk_maximal_do_impl (const thchar_t *s, int len,
                                         const char *brkpos_hints,
                                         int pos[], size_t n);
static int          brk_recover_try (const thchar_t *s, int len,
                                     const char *brkpos_hints,
                                     size_t recov_words, int *last_brk_pos);
static int          brk_recover (const thchar_t *text, int len, int pos,
                                 const char *brkpos_hints, RecovHist *rh);

/*---------------------*
 *   PRIVATE GLOBALS   *
 *---------------------*/
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
    brk_brkpos_hints (s, len, brkpos_hints);

    ret = brk_maximal_do_impl (s, len, brkpos_hints, pos, n);

    free (brkpos_hints);

    return ret;
}

static int
brk_maximal_do_impl (const thchar_t *s, int len,
                     const char *brkpos_hints,
                     int pos[], size_t n)
{
    BrkPool     *pool;
    BrkPool     *node;
    BestBrk     *best_brk;
    RecovHist    recov_hist;
    int          ret;

    pool = brk_root_pool (n);
    best_brk = best_brk_new (n);
    if (!best_brk)
        return 0;
    recov_hist.pos = recov_hist.recov = -1;

    while (NULL != (node = brk_pool_get_node (pool))) {
        BrkShot *shot = &node->shot;
        BrkPool *match;
        int      is_keep_node, is_terminal, is_recovered;
        int      str_pos;

        /* walk dictionary character-wise till a word is matched */
        is_keep_node = 1;
        is_recovered = 0;
        str_pos = shot->str_pos;
        do {
            if (!trie_state_walk (shot->dict_state, th_tis2uni (s[str_pos++])))
            {
                int recovered;

                is_terminal = 0;

                /* try to recover from error */
                recovered = brk_recover (s, len, shot->str_pos + 1,
                                         brkpos_hints, &recov_hist);
                if (-1 != recovered) {
                    /* add penalty by recovered - recent break pos */
                    shot->penalty += recovered;
                    if (shot->cur_brk_pos > 0)
                        shot->penalty -= shot->brk_pos[shot->cur_brk_pos - 1];

                    str_pos = recovered;
                    is_recovered = 1;
                } else {
                    /* add penalty with string len - recent break pos */
                    shot->penalty += len;
                    if (shot->cur_brk_pos > 0)
                        shot->penalty -= shot->brk_pos[shot->cur_brk_pos - 1];

                    shot->brk_pos [shot->cur_brk_pos++] = str_pos = len;
                    is_keep_node = 0;
                }
                break;
            }

            is_terminal = trie_state_is_terminal (shot->dict_state);
            if (str_pos >= len) {
                if (!is_terminal) {
                    /* add penalty with string len - recent break pos */
                    shot->penalty += len;
                    if (shot->cur_brk_pos > 0)
                        shot->penalty -= shot->brk_pos[shot->cur_brk_pos - 1];

                    shot->brk_pos [shot->cur_brk_pos++] = len;
                    is_keep_node = 0;
                }
                break;
            }
        } while (!(is_terminal && brkpos_hints[str_pos]));

        shot->str_pos = str_pos;

        /* if node still kept, mark break position and rewind dictionary */
        if (is_keep_node && (is_terminal || is_recovered)) {
            if (shot->str_pos < len && is_terminal &&
                !trie_state_is_single (shot->dict_state))
            {
                /* add node to mark break position instead of current */
                node = brk_pool_node_new (shot);
                pool = brk_pool_add (pool, node);
                shot = &node->shot;
            }

            trie_state_rewind (shot->dict_state);
            shot->brk_pos [shot->cur_brk_pos++] = shot->str_pos;
        }

        if (!is_keep_node || shot->str_pos == len || shot->cur_brk_pos >= n) {
            /* path is done; contest and remove */
            best_brk_contest (best_brk, shot);
            pool = brk_pool_delete (pool, node);
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

    ret = best_brk->cur_brk_pos;
    memcpy (pos, best_brk->brk_pos, ret * sizeof (pos[0]));

    brk_pool_free (pool);
    best_brk_free (best_brk);
    return ret;
}

static int
brk_recover_try (const thchar_t *s, int len,
                 const char *brkpos_hints,
                 size_t recov_words, int *last_brk_pos)
{
    BrkPool     *pool;
    BrkPool     *node;
    int          ret;

    pool = brk_root_pool (recov_words);
    ret = 0;

    while (NULL != (node = brk_pool_get_node (pool))) {
        BrkShot *shot = &node->shot;
        BrkPool *match;
        int      is_keep_node, is_terminal;

        /* walk dictionary character-wise till a word is matched */
        is_keep_node = 1;
        for (;;) {
            do {
                if (!trie_state_walk (shot->dict_state,
                                      th_tis2uni (s[shot->str_pos++])))
                {
                    is_keep_node = 0;
                    break;
                }

                is_terminal = trie_state_is_terminal (shot->dict_state);
                if (shot->str_pos >= len) {
                    if (!is_terminal) {
                        is_keep_node = 0;
                    }
                    break;
                }
            } while (!(is_terminal && brkpos_hints[shot->str_pos]));

            if (!is_keep_node) {
                pool = brk_pool_delete (pool, node);
                break;
            }

            /* if node still kept, mark break position and rewind dictionary */
            if (shot->str_pos < len &&
                !trie_state_is_single (shot->dict_state))
            {
                /* add node to mark break position instead of current */
                node = brk_pool_node_new (shot);
                pool = brk_pool_add (pool, node);
                shot = &node->shot;
            }

            trie_state_rewind (shot->dict_state);
            shot->brk_pos [shot->cur_brk_pos++] = shot->str_pos;

            if (shot->str_pos == len || shot->cur_brk_pos == recov_words) {
                /* path is done; get result & remove it */
                if (shot->cur_brk_pos > ret) {
                    ret = shot->cur_brk_pos;
                    *last_brk_pos = shot->brk_pos[ret - 1];
                }
                pool = brk_pool_delete (pool, node);
                /* stop as soon as first solution is found */
                if (ret == recov_words)
                    goto recov_done;
                break;
            } else {
                /* find matched nodes, contest and keep the best one */
                while (NULL != (match = brk_pool_match (pool, node))) {
                    pool = brk_pool_delete (pool, match);
                }
            }
        }
    }

recov_done:
    brk_pool_free (pool);
    return ret;
}

static BrkPool *
brk_root_pool (int pos_size)
{
    Trie       *dict;
    BrkPool    *pool;
    BrkPool    *node;
    BrkShot     root_shot;

    pool = NULL;

    if (NULL == (dict = brk_get_dict()))
        return NULL;
    root_shot.dict_state = trie_root (dict);
    root_shot.brk_pos = NULL; /* it's not used anyway */
    root_shot.n_brk_pos = pos_size;
    root_shot.str_pos = root_shot.cur_brk_pos = 0;
    root_shot.penalty = 0;

    node = brk_pool_node_new (&root_shot);
    if (node) {
        pool = brk_pool_add (pool, node);
    }

    brk_shot_destruct (&root_shot);

    return pool;
}

#define RECOVERED_WORDS 3

static int
brk_recover (const thchar_t *text, int len, int pos,
             const char *brkpos_hints, RecovHist *rh)
{
    int last_brk_pos;
    int n, p;

    while (pos < len && !brkpos_hints[pos]) {
        ++pos;
    }
    if (rh->pos == pos)
        return rh->recov;

    for (p = pos; p < len; ++p) {
        if (brkpos_hints[p]) {
            n = brk_recover_try (text + p, len - p, brkpos_hints + p,
                                 RECOVERED_WORDS, &last_brk_pos);
            if (n == RECOVERED_WORDS
                || (n > 0 && '\0' == text[last_brk_pos]))
            {
                rh->pos = pos;
                rh->recov = p;
                return p;
            }
        }
    }

    return -1;
}

static int
brk_shot_init (BrkShot *dst, const BrkShot *src)
{
    dst->dict_state = trie_state_clone (src->dict_state);
    dst->str_pos = src->str_pos;
    dst->brk_pos = (int *) malloc (src->n_brk_pos * sizeof (int));
    if (!dst->brk_pos)
        return -1;
    memcpy (dst->brk_pos, src->brk_pos, src->cur_brk_pos * sizeof (int));
    dst->n_brk_pos = src->n_brk_pos;
    dst->cur_brk_pos = src->cur_brk_pos;
    dst->penalty = src->penalty;

    return 0;
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
        if (brk_shot_init (&node->shot, shot) != 0) {
            free (node);
            return NULL;
        }
    }

    node->next = NULL;

    return node;
}

static void
brk_pool_node_free (BrkPool *pool)
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
        brk_pool_node_free (pool);
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
    brk_pool_node_free (node);

    return pool;
}

static BestBrk *
best_brk_new (int n_brk_pos)
{
    BestBrk *best_brk;

    if ((size_t) n_brk_pos > SIZE_MAX / sizeof (int))
        return NULL;

    best_brk = (BestBrk *) malloc (sizeof (BestBrk));
    if (!best_brk)
        return NULL;

    best_brk->brk_pos = (int *) malloc ((size_t) n_brk_pos * sizeof (int));
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
