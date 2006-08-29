/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * thbrk.c - Thai word break routine
 * Created: 2006-08-20
 * Author:  Theppitak Karoonboonyanan <thep@linux.thai.net>
 */

#include <string.h>
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

/*----------------------------------*
 *   PRIVATE METHODS DECLARATIONS   *
 *----------------------------------*/

static SBTrie *     brk_get_dict ();

static BrkPool *    brk_root_pool (int pos_size);
static int          brk_do (const thchar_t *s, int len, int pos[], size_t n,
                            int do_recover);
static int          brk_recover (const thchar_t *text, int len, int pos);

#define th_isleadable(c) \
    (th_isthcons(c)||th_isldvowel(c)||th_isthdigit(c))

int
th_brk_line (const thchar_t *in, thchar_t *out, size_t n, const char *delim)
{
    int        *brk_pos;
    int         n_brk_pos, i, j;
    int         delim_len;
    thchar_t   *p_out;

    n_brk_pos = strlen ((const char *) in);
    brk_pos = (int *) malloc (n_brk_pos * sizeof (int));

    n_brk_pos = th_brk (in, brk_pos, n_brk_pos);
    
    delim_len = strlen (delim);
    for (i = j = 0, p_out = out; n > 1 && i < n_brk_pos; i++) {
        while (n > 1 && j < brk_pos[i]) {
            *p_out++ = in [j++];
            --n;
        }
        if (n > delim_len + 1) {
            strcpy ((char *) p_out, delim);
            p_out += delim_len;
            n -= delim_len;
        }
    }
    while (n > 1 && in [j]) {
        *p_out++ = in [j++];
        --n;
    }
    *p_out = '\0';

    free (brk_pos);

    return p_out - out;
}

int
th_brk (const thchar_t *s, int pos[], size_t n)
{
    const thchar_t *chunk;
    int             cur_pos;

    chunk = s;
    cur_pos = 0;

    brk_pool_allocator_use ();

    while (*chunk && cur_pos < n) {
        const thchar_t *str_end;
        int             n_brk, i;

        while (*chunk &&
               (!th_isthai (*chunk) ||
                th_isthpunct (*chunk) ||
                th_isthdigit (*chunk)))
        {
            thchar_t cur_char, next_char;

            /* peek next char and mark break pos if character type changes 
             * without space in between
             */
            cur_char = *chunk;
            next_char = *(chunk + 1);
            if (next_char && !isspace (next_char) &&
                (isspace (cur_char) ||
                 th_isthpunct (cur_char) ||
                 (!th_isthai (cur_char) && th_isthai (next_char)) ||
                 (th_isthdigit (cur_char) && !th_isthdigit (next_char)) ||
                 (isdigit (cur_char) && !isdigit (next_char))))
            {
                pos [cur_pos++] = (chunk - s) + 1;
                if (cur_pos >= n)
                    break;
            }

            ++chunk;
        }
        if (!*chunk || cur_pos >= n)
            break;

        str_end = chunk;
        while (*str_end &&
               (th_isthai (*str_end)
                && !th_isthpunct (*str_end)
                && !th_isthdigit (*str_end)))
        {
            ++str_end;
        }

        /* do string break within Thai chunk */
        n_brk = brk_do (chunk, str_end - chunk, pos + cur_pos, n - cur_pos, 1);
        for (i = 0; i < n_brk; i++)
            pos [cur_pos + i] += chunk - s;
        cur_pos += n_brk;
        chunk = str_end;

        /* if next character is Thai punct (e.g. Mai Yamok, Paiyan Noi)
         * or white space, don't break
         */
        if (*chunk && (th_isthpunct (*chunk) || isspace (*chunk)) &&
            cur_pos > 0 && pos [cur_pos - 1] == chunk -s)
        {
            --cur_pos;
        }
        /* otherwise, mark break pos at boundary if character type changes
         * without space in between and not currently marked
         */
        else if (cur_pos < n && *chunk && !isspace (*chunk) &&
                 cur_pos > 0 && pos [cur_pos - 1] != chunk - s)
        {
            pos [cur_pos++] = chunk - s;
        }
    }

    brk_pool_allocator_clear ();

    return cur_pos;
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

static int
brk_do (const thchar_t *s, int len, int pos[], size_t n, int do_recover)
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

                if (!do_recover) {
                    pool = brk_pool_delete (pool, node);
                    keep_on = 0;
                    break;
                }

                /* try to recover from error */
                if (-1 != (recovered = brk_recover (s, len, shot->str_pos))) {
                    /* add penalty by recovered - recent break pos */
                    shot->penalty += recovered;
                    if (shot->cur_brk_pos > 0)
                        shot->penalty -= shot->brk_pos[shot->cur_brk_pos - 1];

                    shot->str_pos = recovered;
                    sb_trie_state_rewind (shot->dict_state);
                    if (shot->str_pos < len) {
                        shot->brk_pos [shot->cur_brk_pos++] = shot->str_pos;
                        if (shot->cur_brk_pos >= n) {
                            best_brk_contest (best_brk, shot);
                            pool = brk_pool_delete (pool, node);
                            keep_on = 0;
                            break;
                        }
                    }
                } else {
                    /* add penalty with string len - recent break pos */
                    shot->penalty += len;
                    if (shot->cur_brk_pos > 0)
                        shot->penalty -= shot->brk_pos[shot->cur_brk_pos - 1];

                    best_brk_contest (best_brk, shot);
                    pool = brk_pool_delete (pool, node);
                    keep_on = 0;
                    break;
                }
            }
        } while (shot->str_pos < len
                 && !(sb_trie_state_is_terminal (shot->dict_state)
                      && th_isleadable (s[shot->str_pos])));

        if (!keep_on)
            continue;

        if (shot->str_pos < len && !sb_trie_state_is_leaf (shot->dict_state)) {
            /* add node to mark break position instead of current */
            node = brk_pool_node_new (shot);
            pool = brk_pool_add (pool, node);
        }

        sb_trie_state_rewind (node->shot.dict_state);
        node->shot.brk_pos [node->shot.cur_brk_pos++] = node->shot.str_pos;

        if (node->shot.str_pos == len || node->shot.cur_brk_pos >= n) {
            /* path is done; contest and remove */
            best_brk_contest (best_brk, &node->shot);
            pool = brk_pool_delete (pool, node);
        } else if (NULL != (match = brk_pool_match (pool, node))) {
            BrkPool *del_node;

            /* break pos matches another node, contest and keep better one */
            del_node = (match->shot.penalty < node->shot.penalty ||
                        (match->shot.penalty == node->shot.penalty &&
                         match->shot.cur_brk_pos < node->shot.cur_brk_pos))
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

static int
brk_recover (const thchar_t *text, int len, int pos)
{
    int brk_pos[RECOVERED_WORDS];
    int n;

    while (pos < len) {
        if (th_isleadable (text[pos]) &&
            (0 == pos || !th_isldvowel (text[pos - 1])))
        {
            n = brk_do (text + pos, len - pos, brk_pos, RECOVERED_WORDS, 0);
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
           shot->cur_brk_pos < best_brk->cur_brk_pos))))
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
