/*
 * hashtbl.h - hash table
 * Created: 2001-09-13
 * Author: Theppitak Karoonboonyanan
 */

#ifndef THAI_HASHTBL_H
#define THAI_HASHTBL_H

typedef struct _hash_table_t hash_table_t;
typedef int (*hash_func_t)(const void *key, int range);
typedef int (*eq_func_t)(const void *key1, const void *key2);

hash_table_t* hash_table_new(hash_func_t hasher, eq_func_t eqer);
void          hash_table_destroy(hash_table_t *ht);
void          hash_table_insert(hash_table_t *ht, void *key, void *val);
void          hash_table_remove(hash_table_t *ht, void *key);
void**        hash_table_lookup(const hash_table_t *ht, void *key);

#endif /* THAI_HASHTBL_H */

