/*
 * hashtbl.c - hash table
 * Created: 2001-09-13
 * Author: Theppitak Karoonboonyanan
 */

#include "hashtbl.h"
#include <stdlib.h>
#include <assert.h>

typedef struct _hash_cell_t hash_cell_t;

enum _cell_flag_t {
    HCF_UNUSED,
    HCF_DELETED,
    HCF_USED
};

struct _hash_cell_t {
    enum _cell_flag_t  flag_;
    void              *key_;
    void              *val_;
};

struct _hash_table_t {
    int          table_size_;
    int          n_data_;
    hash_cell_t *p_hash_cells_;
    hash_func_t  hasher_;
    eq_func_t    eqer_;
};

#define NumPrimes_ 28
static const unsigned long Primes_[NumPrimes_] =
{
    53,         97,         193,       389,       769,
    1543,       3079,       6151,      12289,     24593,
    49157,      98317,      196613,    393241,    786433,
    1572869,    3145739,    6291469,   12582917,  25165843,
    50331653,   100663319,  201326611, 402653189, 805306457, 
    1610612741, 3221225473UL, 4294967291UL
};

/* find lowest i : Primes_[i] >= n */
static unsigned long next_prime_(unsigned long n)
{
    int l = 0, h = NumPrimes_;
    while (l < h - 1) {
        int i = (l + h)/2;
        if (Primes_[i] == n) { return n; }
        else if (Primes_[i] < n) { l = i; }
        else { h = i; }

        /* check loop invariant */
        assert(Primes_[l] <= Primes_[h]);
        assert(n <= Primes_[h]);
    }
    return Primes_[h];
}

hash_table_t* hash_table_new(hash_func_t hasher, eq_func_t eqer)
{
    hash_table_t *ht = (hash_table_t *) malloc(sizeof(hash_table_t));
    ht->table_size_ = Primes_[0];
    ht->n_data_ = 0;
    ht->p_hash_cells_ =
        (hash_cell_t *) malloc(ht->table_size_ * sizeof(hash_cell_t));
    ht->hasher_ = hasher;
    ht->eqer_ = eqer;
    return ht;
}

void hash_table_destroy(hash_table_t *ht)
{
    free(ht->p_hash_cells_);
    free(ht);
}

static int hash_table_find_free_cell_(const hash_table_t *ht, const void *key)
{
    int h = (*ht->hasher_)(key, ht->table_size_);
    int i = h, d = 1;
    while (ht->p_hash_cells_[i].flag_ == HCF_USED) {
        if ((*ht->eqer_)(ht->p_hash_cells_[i].key_, key))
            return -2;
        i = (i + d) % ht->table_size_;
        if (i == h) return -1;
        d += 2;
    }
    return i;
}

static void hash_table_add_noresize_(hash_table_t *ht, void *key, void *val)
{
    int index = hash_table_find_free_cell_(ht, key);
    if (index >= 0) {
        ht->p_hash_cells_[index].flag_ = HCF_USED;
        ht->p_hash_cells_[index].key_ = key;
        ht->p_hash_cells_[index].val_ = val;

        ++ht->n_data_;
    }
}

static void hash_table_resize_(hash_table_t *ht, int size_hint)
{
    if (size_hint > ht->table_size_) {
        int old_size;
        hash_cell_t *old_table;
        int i;

        old_size = ht->table_size_;
        old_table = ht->p_hash_cells_;
        ht->table_size_ = next_prime_(size_hint);
        ht->p_hash_cells_ =
            (hash_cell_t *) malloc(ht->table_size_ * sizeof(hash_cell_t));
        ht->n_data_ = 0;
        for (i = 0; i < old_size; ++i) {
            if (old_table[i].flag_ == HCF_USED) {
                hash_table_add_noresize_(ht,
                                         old_table[i].key_, old_table[i].val_);
            }
        }
        free(old_table);
    }
}

void hash_table_insert(hash_table_t *ht, void *key, void *val)
{
    hash_table_resize_(ht, ht->n_data_+1);
    hash_table_add_noresize_(ht, key, val);
}

static int hash_table_lookup_(const hash_table_t *ht, void *key)
{
    int h = (*ht->hasher_)(key, ht->table_size_);
    int i = h, d = 1;
    while ((ht->p_hash_cells_[i].flag_ == HCF_USED &&
            !(*ht->eqer_)(ht->p_hash_cells_[i].key_, key)) ||
           ht->p_hash_cells_[i].flag_ == HCF_DELETED)
    {
       i = (i + d) % ht->table_size_;
       if (i == h) { return -1; }
       d += 2;
    }
    return (ht->p_hash_cells_[i].flag_ == HCF_USED) ? i : -1;
}

void hash_table_remove(hash_table_t *ht, void *key)
{
    int index = hash_table_lookup_(ht, key);
    if (index >= 0) {
        ht->p_hash_cells_[index].flag_ = HCF_DELETED;
        --ht->n_data_;
    }
}

void** hash_table_lookup(const hash_table_t *ht, void *key)
{
    int index = hash_table_lookup_(ht, key);
    return (index == -1) ? 0 : &ht->p_hash_cells_[index].val_;
}

