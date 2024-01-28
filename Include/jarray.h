#ifndef __JAEYEONG_ARRAY_H__
#define __JAEYEONG_ARRAY_H__
#include <stdbool.h>
#include <string.h>
#include "apua.h"

typedef enum {
	ArrayFlags__noslices = 1U, // u64(1) << 0
	ArrayFlags__noshrink = 2U, // u64(1) << 1
	ArrayFlags__nogrow = 4U, // u64(1) << 2
	ArrayFlags__nofree = 8U, // u64(1) << 3
}  ArrayFlags;

struct array {
  void* data;
  int offset;
	int len;
	int cap;
  ArrayFlags flags;
  int element_size;
};

inline bool ArrayFlags_all(ArrayFlags* e, ArrayFlags flag) {
  return ((((int)(*e)) & (((int)(flag))))) == ((int)(flag));
}

inline void ArrayFlags_set(ArrayFlags* e, ArrayFlags flag) {
	*e = ((ArrayFlags)((((int)(*e)) | (((int)(flag))))));
}

// Attr: [inline]
inline void ArrayFlags_set_all(ArrayFlags* e) {
	*e = ((ArrayFlags)(0b1111));
}

array __new_array(int mylen, int cap, int elm_size);
array __new_array_with_default(int mylen, int cap, int elm_size, void* val);
array __new_array_with_multi_default(int mylen, int cap, int elm_size, void* val);
array __new_array_with_array_default(int mylen, int cap, int elm_size, array val, int depth);
// array __new_array_with_map_default(int mylen, int cap, int elm_size, map val);
array new_array_from_c_array(int len, int cap, int elm_size, void* c_array);
array new_array_from_c_array_no_alloc(int len, int cap, int elm_size, void* c_array);
void array_ensure_cap(array* a, int required);
array array_repeat(array a, int count);
array array_repeat_to_depth(array a, int count, int depth);
void array_insert(array* a, int i, void* val);
void array_insert_many(array* a, int i, void* val, int size);
void array_prepend(array* a, void* val);
void array_prepend_many(array* a, void* val, int size);
void array_delete(array* a, int i);
void array_delete_many(array* a, int i, int size);
void array_clear(array* a);
void array_reset(array* a);
void array_trim(array* a, int index);
void array_drop(array* a, int num);
void* array_get_unsafe(array a, int i);
void* array_get(array a, int i);
void* array_get_with_check(array a, int i);
void* array_first(array a);
void* array_last(array a);
void* array_pop(array* a);
void array_delete_last(array* a);
array array_slice(array a, int start, int _end);
array array_slice_ni(array a, int _start, int _end);
array array_clone_static_to_depth(array a, int depth);
array array_clone(array* a);
array array_clone_to_depth(array* a, int depth);
inline void array_set_unsafe(array* a, int i, void* val) { memcpy(((u8*)(a->data)) + (u64)(((u64)(a->element_size)) * ((u64)(i))), val, a->element_size); }
void array_set(array* a, int i, void* val);
void array_push(array* a, void* val);
void array_push_many(array* a3, void* val, int size);
void array_free(array* a);

inline bool ArrayFlags_has(ArrayFlags* e, ArrayFlags flag) { return ((((int)(*e)) & (((int)(flag))))) != 0; }
#endif /* __JAEYEONG_ARRAY_H__ */