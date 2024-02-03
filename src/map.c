#include <stdio.h>
#include <stdlib.h>
#include "jaeyeong.h"
#include "wyhash.h"

const u32 _const_hash_mask = 16777215;
const u32 _const_probe_inc = 16777216;
extern const u8 _const_min_u8; // precomputed2
extern const u8 _const_max_u8; // precomputed2
extern const u16 _const_min_u16; // precomputed2
extern const u16 _const_max_u16; // precomputed2
extern const u32 _const_min_u32; // precomputed2
extern const u32 _const_max_u32; // precomputed2
extern const u64 _const_min_u64; // precomputed2
extern const u64 _const_max_u64; // precomputed2
extern const f64 _const_max_load_factor; // precomputed2

void DenseArray_zeros_to_end(DenseArray* d) {
  u8* tmp_value = jmalloc(d->value_bytes);
  u8* tmp_key = jmalloc(d->key_bytes);
  int count = 0;
  for (int i = 0; i < d->len; ++i) {
    if (DenseArray_has_index(d, i)) {
      if (count != i) {
        memcpy(tmp_key, DenseArray_key(d, count), d->key_bytes);
        memcpy(DenseArray_key(d, count), DenseArray_key(d, i), d->key_bytes);
        memcpy(DenseArray_key(d, i), tmp_key, d->key_bytes);
        memcpy(tmp_value, DenseArray_value(d, count), d->value_bytes);
        memcpy(DenseArray_value(d, count), DenseArray_value(d, i), d->value_bytes);
        memcpy(DenseArray_value(d, i), tmp_value, d->value_bytes);
      }
      count++;
    }
  }
  jfree(tmp_value);
  jfree(tmp_key);
  d->deletes = 0U;
  jfree(d->all_deleted);
  d->len = count;
  int old_cap = d->cap;
  d->cap = (count < 8 ? (8) : (count));
  d->values = realloc_data(d->values, (int)(d->value_bytes * old_cap), (int)(d->value_bytes * d->cap));
  d->keys = realloc_data(d->keys, (int)(d->key_bytes * old_cap), (int)(d->key_bytes * d->cap));
}

DenseArray new_dense_array(int key_bytes, int value_bytes) {
  int cap = 8;
  return ((DenseArray){
    .key_bytes = key_bytes,
    .value_bytes = value_bytes,
    .cap = cap,
    .len = 0,
    .deletes = 0U,
    .all_deleted = ((void*)0),
    .keys = jmalloc(__at_least_one((u64)(((u64)(cap)) * ((u64)(key_bytes))))),
    .values = jmalloc(__at_least_one((u64)(((u64)(cap)) * ((u64)(value_bytes))))),
  });
}

void* DenseArray_key(DenseArray* d, int i) {
  return ((void*)(d->keys + (int)(i * d->key_bytes)));
}

void* DenseArray_value(DenseArray* d, int i) {
  return ((void*)(d->values + (int)(i * d->value_bytes)));
}

bool DenseArray_has_index(DenseArray* d, int i) {
  return d->deletes == 0U || d->all_deleted[i] == 0;
}

int DenseArray_expand(DenseArray* d) {
  int old_cap = d->cap;
  int old_key_size = (int)(d->key_bytes * old_cap);
  int old_value_size = (int)(d->value_bytes * old_cap);
  if (d->cap == d->len) {
    d->cap += (d->cap >> 3);
    d->keys = realloc_data(d->keys, old_key_size, (int)(d->key_bytes * d->cap));
    d->values = realloc_data(d->values, old_value_size, (int)(d->value_bytes * d->cap));
    if (d->deletes != 0U) {
      d->all_deleted = realloc_data(d->all_deleted, old_cap, d->cap);
      memset(((void*)(d->all_deleted + d->len)), 0, (int)(d->cap - d->len));
    }
  }
  int push_index = d->len;
  if (d->deletes != 0U) d->all_deleted[push_index] = 0;
  d->len++;
  return push_index;
}

bool map_eq_string(void* a, void* b) {
  return fast_string_eq(*((string*)(a)), *((string*)(b)));
}

bool map_eq_int_1(void* a, void* b) {
  return *((u8*)(a)) == *((u8*)(b));
}

bool map_eq_int_2(void* a, void* b) {
  return *((u16*)(a)) == *((u16*)(b));
}

bool map_eq_int_4(void* a, void* b) {
  return *((u32*)(a)) == *((u32*)(b));
}

bool map_eq_int_8(void* a, void* b) {
  return *((u64*)(a)) == *((u64*)(b));
}

void map_clone_string(void* dest, void* pkey) {
  string s = *((string*)(pkey));
  *((string*)(dest)) = string_clone(s);
}

void map_clone_int_1(void* dest, void* pkey) {
  *((u8*)(dest)) = *((u8*)(pkey));
}

void map_clone_int_2(void* dest, void* pkey) {
  *((u16*)(dest)) = *((u16*)(pkey));
}

void map_clone_int_4(void* dest, void* pkey) {
  *((u32*)(dest)) = *((u32*)(pkey));
}

void map_clone_int_8(void* dest, void* pkey) {
  *((u64*)(dest)) = *((u64*)(pkey));
}

void map_free_string(void* pkey) {
  string_free(ADDR(string, (*((string*)(pkey)))));
}

map new_map(int key_bytes, int value_bytes, u64 (*hash_fn)(void* ), bool (*key_eq_fn)(void* , void* ), void (*clone_fn)(void* , void* ), void (*free_fn)(void* )) {
  int metasize = ((int)((u32)(sizeof(u32) * ((int_literal)(_const_init_capicity + _const_extra_metas_inc)))));
  bool has_string_keys = _us32_lt(sizeof(void*),key_bytes);
  return ((map){
    .key_bytes = key_bytes,
    .value_bytes = value_bytes,
    .even_index = _const_init_even_index,
    .cached_hashbits = _const_max_cached_hashbits,
    .shift = _const_init_log_capicity,
    .key_values = new_dense_array(key_bytes, value_bytes),
    .metas = ((u32*)(jcalloc_noscan(metasize))),
    .extra_metas = _const_extra_metas_inc,
    .has_string_keys = has_string_keys,
    .hash_fn = (void*)hash_fn,
    .key_eq_fn = (void*)key_eq_fn,
    .clone_fn = (void*)clone_fn,
    .free_fn = (void*)free_fn,
    .len = 0,
  });
}

map new_map_init(u64 (*hash_fn)(void* ), bool (*key_eq_fn)(void* , void* ), void (*clone_fn)(void* , void* ), void (*free_fn)(void* ), int n, int key_bytes, int value_bytes, void* keys, void* values) {
  map out = new_map(key_bytes, value_bytes, (void*)hash_fn, (void*)key_eq_fn, (void*)clone_fn, (void*)free_fn);
  u8* pkey = ((u8*)(keys));
  u8* pval = ((u8*)(values));
  for (int _t1 = 0; _t1 < n; ++_t1) {
    map_set(&out, pkey, pval);
    pkey = pkey + key_bytes;
    pval = pval + value_bytes;
  }
  return out;
}

map new_map_update_init(map* update, int n, int key_bytes, int value_bytes, void* keys, void* values) {
  map out = map_clone(update);
  u8* pkey = ((u8*)(keys));
  u8* pval = ((u8*)(values));
  for (int _t1 = 0; _t1 < n; ++_t1) {
    map_set(&out, pkey, pval);
    pkey = pkey + key_bytes;
    pval = pval + value_bytes;
  }
  return out;
}

map map_move(map* m) {
  map r = *m;
  memset(m, 0, ((int)(sizeof(map))));
  return r;
}

void map_clear(map* m) {
  m->len = 0;
  m->even_index = 0U;
  m->key_values.len = 0;
}

multi_return_u32_u32 map_key_to_index(map* m, void* pkey) {
  u64 hash = m->hash_fn(pkey);
  u64 index = (hash & m->even_index);
  u64 meta = (((((hash >> m->shift)) & _const_hash_mask)) | _const_probe_inc);
  return (multi_return_u32_u32){.arg0=((u32)(index)), .arg1=((u32)(meta))};
}

multi_return_u32_u32 map_meta_less(map* m, u32 _index, u32 _metas) {
  u32 index = _index;
  u32 meta = _metas;
  for (;;) {
    if (!(meta < m->metas[index])) break;
    index += 2U;
    meta += _const_probe_inc;
  }
  return (multi_return_u32_u32){.arg0=index, .arg1=meta};
}

void map_meta_greater(map* m, u32 _index, u32 _metas, u32 kvi) {
  u32 meta = _metas;
  u32 index = _index;
  u32 kv_index = kvi;
  for (;;) {
    if (!(m->metas[index] != 0U)) break;
    if (meta > m->metas[index]) {
      u32 tmp_meta = m->metas[index];
      m->metas[index] = meta;
      meta = tmp_meta;
      u32 tmp_index = m->metas[(u32)(index + 1U)];
      m->metas[(u32)(index + 1U)] = kv_index;
      kv_index = tmp_index;
    }
    index += 2U;
    meta += _const_probe_inc;
  }
  m->metas[index] = meta;
  m->metas[(u32)(index + 1U)] = kv_index;
  u32 probe_count = (u32)(((meta >> _const_hashbits)) - 1U);
  map_ensure_extra_metas(m, probe_count);
}

void map_ensure_extra_metas(map* m, u32 probe_count) {
  if (((probe_count << 1U)) == m->extra_metas) {
    u32 size_of_u32 = sizeof(u32);
    u32 old_mem_size = ((u32)((u32)(m->even_index + 2U) + m->extra_metas));
    m->extra_metas += _const_extra_metas_inc;
    u32 mem_size = ((u32)((u32)(m->even_index + 2U) + m->extra_metas));
    u8* x = realloc_data(((u8*)(m->metas)), ((int)((u32)(size_of_u32 * old_mem_size))), ((int)((u32)(size_of_u32 * mem_size))));
    m->metas = ((u32*)(x));
    memset(m->metas + mem_size - _const_extra_metas_inc, 0, ((int)((u32)(sizeof(u32) * _const_extra_metas_inc))));
    if (probe_count == 252U) {
      __panic(LANG(JAEYEONG_ERR_PROBE_OVERFLOW));
      UNREACHABLE();
    }
  }
}

void map_set(map* m, void* key, void* value) {
  f32 load_factor = (f32)(((f32)((((u32)(m->len)) << 1U))) / ((f32)(m->even_index)));
  if (load_factor > ((f32)(_const_max_load_factor))) map_expand(m);
  multi_return_u32_u32 mr_11688 = map_key_to_index(m, key);
  u32 index = mr_11688.arg0;
  u32 meta = mr_11688.arg1;
  multi_return_u32_u32 mr_11724 = map_meta_less(m, index, meta);
  index = mr_11724.arg0;
  meta = mr_11724.arg1;
  for (;;) {
    if (!(meta == m->metas[index])) break;
    int kv_index = ((int)(m->metas[(u32)(index + 1U)]));
    void* pkey = DenseArray_key(&m->key_values, kv_index);
    if (m->key_eq_fn(key, pkey)) {
      void* pval = DenseArray_value(&m->key_values, kv_index);
      memcpy(pval, value, m->value_bytes);
      return;
    }
    index += 2U;
    meta += _const_probe_inc;
  }
  int kv_index = DenseArray_expand(&m->key_values);
  void* pkey = DenseArray_key(&m->key_values, kv_index);
  void* pvalue = DenseArray_value(&m->key_values, kv_index);
  m->clone_fn(pkey, key);
  memcpy(((u8*)(pvalue)), value, m->value_bytes);
  map_meta_greater(m, index, meta, ((u32)(kv_index)));
  m->len++;
}

void map_expand(map* m) {
  u32 old_cap = m->even_index;
  m->even_index = (u32)(((((u32)(m->even_index + 2U)) << 1U)) - 2U);
  if (m->cached_hashbits == 0) {
    m->shift += _const_max_cached_hashbits;
    m->cached_hashbits = _const_max_cached_hashbits;
    map_rehash(m);
  } else {
    map_cached_rehash(m, old_cap);
    m->cached_hashbits--;
  }
}

void map_rehash(map* m) {
  u32 meta_bytes = (u32)(sizeof(u32) * ((u32)((u32)(m->even_index + 2U) + m->extra_metas)));
  map_reserve(m, meta_bytes);
}

void map_reserve(map* m, u32 meta_bytes) {
  u8* x = jrealloc(((u8*)(m->metas)), ((int)(meta_bytes)));
  m->metas = ((u32*)(x));
  memset(m->metas, 0, ((int)(meta_bytes)));
  for (int i = 0; i < m->key_values.len; i++) {
    if (!DenseArray_has_index(&m->key_values, i)) continue;
    void* pkey = DenseArray_key(&m->key_values, i);
    multi_return_u32_u32 mr_13498 = map_key_to_index(m, pkey);
    u32 index = mr_13498.arg0;
    u32 meta = mr_13498.arg1;
    multi_return_u32_u32 mr_13536 = map_meta_less(m, index, meta);
    index = mr_13536.arg0;
    meta = mr_13536.arg1;
    map_meta_greater(m, index, meta, ((u32)(i)));
  }
}

void map_cached_rehash(map* m, u32 old_cap) {
  u32* old_metas = m->metas;
  int metasize = ((int)((u32)(sizeof(u32) * ((u32)((u32)(m->even_index + 2U) + m->extra_metas)))));
  m->metas = ((u32*)(jcalloc(metasize)));
  u32 old_extra_metas = m->extra_metas;
  for (u32 i = ((u32)(0U)); i <= (u32)(old_cap + old_extra_metas); i += 2U) {
    if (old_metas[i] == 0U) continue;
    u32 old_meta = old_metas[i];
    u32 old_probe_count = (((u32)(((old_meta >> _const_hashbits)) - 1U)) << 1U);
    u32 old_index = (((u32)(i - old_probe_count)) & ((m->even_index >> 1U)));
    u32 index = (((old_index | ((old_meta << m->shift)))) & m->even_index);
    u32 meta = (((old_meta & _const_hash_mask)) | _const_probe_inc);
    multi_return_u32_u32 mr_14335 = map_meta_less(m, index, meta);
    index = mr_14335.arg0;
    meta = mr_14335.arg1;
    u32 kv_index = old_metas[(u32)(i + 1U)];
    map_meta_greater(m, index, meta, kv_index);
  }
  jfree(old_metas);
}

void* map_get_and_set(map* m, void* key, void* zero) {
  for (;;) {
    multi_return_u32_u32 mr_14783 = map_key_to_index(m, key);
    u32 index = mr_14783.arg0;
    u32 meta = mr_14783.arg1;
    for (;;) {
      if (meta == m->metas[index]) {
        int kv_index = ((int)(m->metas[(u32)(index + 1U)]));
        void* pkey = DenseArray_key(&m->key_values, kv_index);
        if (m->key_eq_fn(key, pkey)) {
          void* pval = DenseArray_value(&m->key_values, kv_index);
          return ((u8*)(pval));
        }
      }
      index += 2U;
      meta += _const_probe_inc;
      if (meta > m->metas[index]) break;
    }
    map_set(m, key, zero);
  }
  return ((void*)0);
}

void* map_get(map* m, void* key, void* zero) {
  multi_return_u32_u32 mr_15510 = map_key_to_index(m, key);
  u32 index = mr_15510.arg0;
  u32 meta = mr_15510.arg1;
  for (;;) {
    if (meta == m->metas[index]) {
      int kv_index = ((int)(m->metas[(u32)(index + 1U)]));
      void* pkey = DenseArray_key(&m->key_values, kv_index);
      if (m->key_eq_fn(key, pkey)) {
        void* pval = DenseArray_value(&m->key_values, kv_index);
        return ((u8*)(pval));
      }
    }
    index += 2U;
    meta += _const_probe_inc;
    if (meta > m->metas[index]) break;
  }
  return zero;
}

void* map_get_check(map* m, void* key) {
  multi_return_u32_u32 mr_16175 = map_key_to_index(m, key);
  u32 index = mr_16175.arg0;
  u32 meta = mr_16175.arg1;
  for (;;) {
    if (meta == m->metas[index]) {
      int kv_index = ((int)(m->metas[(u32)(index + 1U)]));
      void* pkey = DenseArray_key(&m->key_values, kv_index);
      if (m->key_eq_fn(key, pkey)) {
        void* pval = DenseArray_value(&m->key_values, kv_index);
        return ((u8*)(pval));
      }
    }
    index += 2U;
    meta += _const_probe_inc;
    if (meta > m->metas[index]) break;
  }
  return 0;
}

bool map_exists(map* m, void* key) {
  multi_return_u32_u32 mr_16685 = map_key_to_index(m, key);
  u32 index = mr_16685.arg0;
  u32 meta = mr_16685.arg1;
  for (;;) {
    if (meta == m->metas[index]) {
      int kv_index = ((int)(m->metas[(u32)(index + 1U)]));
      void* pkey = DenseArray_key(&m->key_values, kv_index);
      if (m->key_eq_fn(key, pkey)) return true;
    }
    index += 2U;
    meta += _const_probe_inc;
    if (meta > m->metas[index]) break;
  }
  return false;
}

void DenseArray_delete(DenseArray* d, int i) {
  if (d->deletes == 0U) d->all_deleted = jcalloc(d->cap);
  d->deletes++;
  d->all_deleted[i] = 1;
}

void map_delete(map* m, void* key) {
  multi_return_u32_u32 mr_17323 = map_key_to_index(m, key);
  u32 index = mr_17323.arg0;
  u32 meta = mr_17323.arg1;
  multi_return_u32_u32 mr_17359 = map_meta_less(m, index, meta);
  index = mr_17359.arg0;
  meta = mr_17359.arg1;
  for (;;) {
    if (!(meta == m->metas[index])) break;
    int kv_index = ((int)(m->metas[(u32)(index + 1U)]));
    void* pkey = DenseArray_key(&m->key_values, kv_index);
    if (m->key_eq_fn(key, pkey)) {
      for (;;) {
        if (!(((m->metas[(u32)(index + 2U)] >> _const_hashbits)) > 1U)) break;
        m->metas[index] = (u32)(m->metas[(u32)(index + 2U)] - _const_probe_inc);
        m->metas[(u32)(index + 1U)] = m->metas[(u32)(index + 3U)];
        index += 2U;
      }
      m->len--;
      DenseArray_delete(&m->key_values, kv_index);
      m->metas[index] = 0U;
      m->free_fn(pkey);
      memset(pkey, 0, m->key_bytes);
      if (m->key_values.len <= 32) return;
      if (_us32_ge(m->key_values.deletes,((m->key_values.len >> 1)))) {
        DenseArray_zeros_to_end(&m->key_values);
        map_rehash(m);
      }
      return;
    }
    index += 2U;
    meta += _const_probe_inc;
  }
}

array map_keys(map* m) {
  array keys = __new_array(m->len, 0, m->key_bytes);
  u8* item = ((u8*)(keys.data));
  if (m->key_values.deletes == 0U) {
    for (int i = 0; i < m->key_values.len; i++) {
      void* pkey = DenseArray_key(&m->key_values, i);
      m->clone_fn(item, pkey);
      item = item + m->key_bytes;
    }
    return keys;
  }
  for (int i = 0; i < m->key_values.len; i++) {
    if (!DenseArray_has_index(&m->key_values, i)) continue;
    void* pkey = DenseArray_key(&m->key_values, i);
    m->clone_fn(item, pkey);
    item = item + m->key_bytes;
  }
  return keys;
}

array map_values(map* m) {
  array values = __new_array(m->len, 0, m->value_bytes);
  u8* item = ((u8*)(values.data));
  if (m->key_values.deletes == 0U) {
    memcpy(item, m->key_values.values, (int)(m->value_bytes * m->key_values.len));
    return values;
  }
  for (int i = 0; i < m->key_values.len; i++) {
    if (!DenseArray_has_index(&m->key_values, i)) continue;
    void* pvalue = DenseArray_value(&m->key_values, i);
    memcpy(item, pvalue, m->value_bytes);
    item = item + m->value_bytes;
  }
  return values;
}

DenseArray DenseArray_clone(DenseArray* d) {
  DenseArray res = ((DenseArray){
    .key_bytes = d->key_bytes,
    .value_bytes = d->value_bytes,
    .cap = d->cap,
    .len = d->len,
    .deletes = d->deletes,
    .all_deleted = ((void*)0),
    .keys = ((void*)0),
    .values = ((void*)0),
  });
  if (d->deletes != 0U) res.all_deleted = memdup(d->all_deleted, d->cap);
  res.keys = memdup(d->keys, (int)(d->cap * d->key_bytes));
  res.values = memdup(d->values, (int)(d->cap * d->value_bytes));
  return res;
}

map map_clone(map* m) {
  int metasize = ((int)((u32)(sizeof(u32) * ((u32)((u32)(m->even_index + 2U) + m->extra_metas)))));
  map res = ((map){
    .key_bytes = m->key_bytes,
    .value_bytes = m->value_bytes,
    .even_index = m->even_index,
    .cached_hashbits = m->cached_hashbits,
    .shift = m->shift,
    .key_values = DenseArray_clone(&m->key_values),
    .metas = ((u32*)(malloc_noscan(metasize))),
    .extra_metas = m->extra_metas,
    .has_string_keys = m->has_string_keys,
    .hash_fn = (void*)m->hash_fn,
    .key_eq_fn = (void*)m->key_eq_fn,
    .clone_fn = (void*)m->clone_fn,
    .free_fn = (void*)m->free_fn,
    .len = m->len,
  });
  memcpy(res.metas, m->metas, metasize);
  if (!m->has_string_keys) return res;
  for (int i = 0; i < m->key_values.len; ++i) {
    if (!DenseArray_has_index(&m->key_values, i)) continue;
    m->clone_fn(DenseArray_key(&res.key_values, i), DenseArray_key(&m->key_values, i));
  }
  return res;
}

void map_free(map* m) {
  jfree(m->metas);
  m->metas = ((void*)0);
  if (m->key_values.deletes == 0U) {
    for (int i = 0; i < m->key_values.len; i++) {
      void* pkey = DenseArray_key(&m->key_values, i);
      m->free_fn(pkey);
      memset(pkey, 0, m->key_bytes);
    }
  } else {
    for (int i = 0; i < m->key_values.len; i++) {
      if (!DenseArray_has_index(&m->key_values, i)) continue;
      void* pkey = DenseArray_key(&m->key_values, i);
      m->free_fn(pkey);
      memset(pkey, 0, m->key_bytes);
    }
  }
  if (m->key_values.all_deleted != ((void*)0)) {
    jfree(m->key_values.all_deleted);
    m->key_values.all_deleted = ((void*)0);
  }
  if (m->key_values.keys != ((void*)0)) {
    jfree(m->key_values.keys);
    m->key_values.keys = ((void*)0);
  }
  if (m->key_values.values != ((void*)0)) {
    jfree(m->key_values.values);
    m->key_values.values = ((void*)0);
  }
  m->hash_fn = (void*)((void*)0);
  m->key_eq_fn = (void*)((void*)0);
  m->clone_fn = (void*)((void*)0);
  m->free_fn = (void*)((void*)0);
}

u64 map_hash_string(void* pkey) {
  string key = *((string*)(pkey));
  return wyhash(key.str, ((u64)(key.len)), 0U, ((u64*)(_wyp)));
}