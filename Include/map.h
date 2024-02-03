#ifndef __JAEYEONG_MAP_H__
#define __JAEYEONG_MAP_H__
#include "apua.h"

#define _const_hashbits 24
#define _const_max_cached_hashbits 16
#define _const_init_log_capicity 5
#define _const_init_capicity 32
#define _const_init_even_index 30
#define _const_extra_metas_inc 4
#define _const_prealloc_block_size 16777216
#define _const_degree 6
#define _const_mid_index 5
#define _const_max_len 11

struct DenseArray {
  int key_bytes;
  int value_bytes;
  int cap;
  int len;
  u32 deletes;
  u8* all_deleted;
  u8* keys;
  u8* values;
};

struct map {
  int key_bytes;
  int value_bytes;
  u32 even_index;
  u8 cached_hashbits;
  u8 shift;
  DenseArray key_values;
  u32* metas;
  u32 extra_metas;
  bool has_string_keys;
  MapHashFn hash_fn;
  MapEqFn key_eq_fn;
  MapCloneFn clone_fn;
  MapFreeFn free_fn;
  int len;
};

struct multi_return_u32_u32 {
  u32 arg0;
  u32 arg1;
};

void DenseArray_zeros_to_end(DenseArray* d);
DenseArray new_dense_array(int key_bytes, int value_bytes);
void* DenseArray_key(DenseArray* d, int i);
void* DenseArray_value(DenseArray* d, int i);
bool DenseArray_has_index(DenseArray* d, int i);
int DenseArray_expand(DenseArray* d);
map new_map(int key_bytes, int value_bytes, u64 (*hash_fn)(void*), bool (*key_eq_fn)(void*, void*), void (*clone_fn)(void*, void*), void (*free_fn)(void*));
map new_map_init(u64 (*hash_fn)(void*), bool (*key_eq_fn)(void*, void*), void (*clone_fn)(void* , void*), void (*free_fn)(void*), int n, int key_bytes, int value_bytes, void* keys, void* values);
map map_move(map* m);
void map_clear(map* m);
multi_return_u32_u32 map_key_to_index(map* m, void* pkey);
multi_return_u32_u32 map_meta_less(map* m, u32 _index, u32 _metas);
void map_meta_greater(map* m, u32 _index, u32 _metas, u32 kvi);
void map_ensure_extra_metas(map* m, u32 probe_count);
void map_set(map* m, void* key, void* value);
void map_expand(map* m);
void map_rehash(map* m);
void map_reserve(map* m, u32 meta_bytes);
void map_cached_rehash(map* m, u32 old_cap);
void* map_get_and_set(map* m, void* key, void* zero);
void* map_get(map* m, void* key, void* zero);
void* map_get_check(map* m, void* key);
bool map_exists(map* m, void* key);
void DenseArray_delete(DenseArray* d, int i);
void map_delete(map* m, void* key);
array map_keys(map* m);
array map_values(map* m);
DenseArray DenseArray_clone(DenseArray* d);
map map_clone(map* m);
void map_free(map* m);

u64 map_hash_string(void* pkey);
u64 map_hash_int_1(void* pkey);
u64 map_hash_int_2(void* pkey);
u64 map_hash_int_4(void* pkey);
u64 map_hash_int_8(void* pkey);
bool map_eq_string(void* a, void* b);
void map_clone_string(void* dest, void* pkey);
void map_free_string(void* pkey);
bool map_eq_int_1(void* a, void* b);
bool map_eq_int_2(void* a, void* b);
bool map_eq_int_4(void* a, void* b);
bool map_eq_int_8(void* a, void* b);
void map_clone_int_1(void* dest, void* pkey);
void map_clone_int_2(void* dest, void* pkey);
void map_clone_int_4(void* dest, void* pkey);
void map_clone_int_8(void* dest, void* pkey);
#endif /* __JAEYEONG_MAP_H__ */