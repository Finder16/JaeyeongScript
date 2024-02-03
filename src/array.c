#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jaeyeong.h"

extern const i32 _const_max_int;

extern bool ArrayFlags_has(ArrayFlags* e, ArrayFlags flag);
extern bool ArrayFlags_all(ArrayFlags *e, ArrayFlags flag);
extern void array_set_unsafe(array* a, int i, void* val);

array __new_array(int mylen, int cap, int elm_size) {
  int cap_ = (cap < mylen ? (mylen) : (cap));
  array arr = ((array){.data = jcalloc((u64)(((u64)(cap_)) * ((u64)(elm_size)))),.offset = 0,.len = mylen,.cap = cap_,/*.flags = 0,*/.element_size = elm_size,});
  return arr;
}

array __new_array_with_default(int mylen, int cap, int elm_size, void* val) {
  int cap_ = (cap < mylen ? (mylen) : (cap));
  array arr = ((array){.data = 0,.offset = 0,.len = mylen,.cap = cap_,/*.flags = 0,*/.element_size = elm_size,});
  u64 total_size = (u64)(((u64)(cap_)) * ((u64)(elm_size)));
  arr.data = (cap_ > 0 && mylen == 0) ? (jmalloc(__at_least_one(total_size))) : (jcalloc(total_size));
  if (val != 0) {
    u8* eptr = ((u8*)(arr.data));
    if (eptr != ((void*)0)) {
      if (arr.element_size == 1) {
        u8 byte_value = *(((u8*)(val)));
        for (int i = 0; i < arr.len; ++i)
          eptr[i] = byte_value;
      } else {
        for (int _t1 = 0; _t1 < arr.len; ++_t1) {
          memcpy(eptr, val, arr.element_size);
          eptr += arr.element_size;
        }
      }
    }
  }
  return arr;
}

array __new_array_with_multi_default(int mylen, int cap, int elm_size, void* val) {
  int cap_ = (cap < mylen ? (mylen) : (cap));
  array arr = ((array){.data = 0,.offset = 0,.len = mylen,.cap = cap_,/*.flags = 0,*/.element_size = elm_size,});
  u64 total_size = (u64)(((u64)(cap_)) * ((u64)(elm_size)));
  arr.data = jcalloc(__at_least_one(total_size));
  if (val != 0) {
    u8* eptr = ((u8*)(arr.data));
    if (eptr != ((void*)0)) {
      for (int i = 0; i < arr.len; ++i) {
        memcpy(eptr, ((char*)(val)) + (int)(i * arr.element_size), arr.element_size);
        eptr += arr.element_size;
      }
    }
  }
  return arr;
}

array __new_array_with_array_default(int mylen, int cap, int elm_size, array val, int depth) {
  int cap_ = (cap < mylen ? (mylen) : (cap));
  array arr = ((array){.data = jmalloc(__at_least_one((u64)(((u64)(cap_)) * ((u64)(elm_size))))),.offset = 0,.len = mylen,.cap = cap_,/*.flags = 0,*/.element_size = elm_size,});
  u8* eptr = ((u8*)(arr.data));
  { // Unsafe block
    if (eptr != ((void*)0)) {
      for (int _t1 = 0; _t1 < arr.len; ++_t1) {
        array val_clone = array_clone_to_depth(&val, depth);
        memcpy(eptr, &val_clone, arr.element_size);
        eptr += arr.element_size;
      }
    }
  }
  return arr;
}

array new_array_from_c_array(int len, int cap, int elm_size, void* c_array) {
  int cap_ = (cap < len ? (len) : (cap));
  array arr = ((array){.data = jcalloc((u64)(((u64)(cap_)) * ((u64)(elm_size)))),.offset = 0,.len = len,.cap = cap_,/*.flags = 0,*/.element_size = elm_size,});
  memcpy(arr.data, c_array, (u64)(((u64)(len)) * ((u64)(elm_size))));
  return arr;
}

array new_array_from_c_array_no_alloc(int len, int cap, int elm_size, void* c_array) {
  array arr = ((array){.data = c_array,.offset = 0,.len = len,.cap = cap,/*.flags = 0,*/.element_size = elm_size,});
  return arr;
}

void array_ensure_cap(array* a, int required) {
  if (required <= a->cap) {
    return;
  }
  if (ArrayFlags_has(&a->flags, ArrayFlags__nogrow)) __panic( str_intp(2, _MOV((StrIntpData[]){{LANG(JAEYEONG_ERR_ARR_ENSURE_CAP_NOGROW), /*100 &int*/0x7, {.d_i32 = required}}, {_SLIT0, 0, { .d_c = 0 }}})));
  int cap = (a->cap > 0 ? (a->cap) : (2));
  for (;;) {
    if (!(required > cap)) break;
    cap *= 2;
  }
  u64 new_size = (u64)(((u64)(cap)) * ((u64)(a->element_size)));
  u8* new_data = jmalloc(__at_least_one(new_size));
  if (a->data != ((void*)0)) {
    memcpy(new_data, a->data, (u64)(((u64)(a->len)) * ((u64)(a->element_size))));
    if (ArrayFlags_has(&a->flags, ArrayFlags__noslices)) jfree(a->data);
  }
  a->data = new_data;
  a->offset = 0;
  a->cap = cap;
}

array array_repeat(array a, int count) {
  return array_repeat_to_depth(a, count, 0);
}

array array_repeat_to_depth(array a, int count, int depth) {
  if (count < 0) __panic( str_intp(2, _MOV((StrIntpData[]){{LANG(JAEYEONG_ERR_ARR_REPEAT_COUNT_NEG), 0x7, {.d_i32 = count}}, {_SLIT0, 0, { .d_c = 0 }}})));
  u64 size = (u64)((u64)(((u64)(count)) * ((u64)(a.len))) * ((u64)(a.element_size)));
  if (size == 0U) size = ((u64)(a.element_size));
  array arr = ((array){.data = jcalloc(size),.offset = 0,.len = (int)(count * a.len),.cap = (int)(count * a.len),.flags = 0,.element_size = a.element_size,});
  if (a.len > 0) {
    u64 a_total_size = (u64)(((u64)(a.len)) * ((u64)(a.element_size)));
    u64 arr_step_size = (u64)(((u64)(a.len)) * ((u64)(arr.element_size)));
    u8* eptr = ((u8*)(arr.data));
    if (eptr != ((void*)0)) {
      for (int _t1 = 0; _t1 < count; ++_t1) {
        if (depth > 0) {
          array ary_clone = array_clone_to_depth(&a, depth);
          memcpy(eptr, ((u8*)(ary_clone.data)), a_total_size);
        } else {
          memcpy(eptr, ((u8*)(a.data)), a_total_size);
        }
        eptr += arr_step_size;
      }
    }
  }
  return arr;
}

void array_insert(array* a, int i, void* val) {
  if (i < 0 || i > a->len) __panic( str_intp(3, _MOV((StrIntpData[]){{LANG(JAEYEONG_ERR_ARR_INSERT_OOR), 0x7, {.d_i32 = i}}, {_SLIT(", a.len == "), 0x7, {.d_i32 = a->len}}, {_SLIT(")"), 0, { .d_c = 0 }}})));
  if (a->len >= a->cap) array_ensure_cap(a, (int)(a->len + 1));
  memmove(array_get_unsafe(/*rec*/*a, (int)(i + 1)), array_get_unsafe(/*rec*/*a, i), (u64)(((u64)(((int)(a->len - i)))) * ((u64)(a->element_size))));
  array_set_unsafe(a, i, val);
  a->len++;
}

void array_insert_many(array* a, int i, void* val, int size) {
  if (i < 0 || i > a->len) __panic( str_intp(3, _MOV((StrIntpData[]){{LANG(JAEYEONG_ERR_ARR_INSERT_MANY_OOR), 0x7, {.d_i32 = i}}, {_SLIT(", a.len == "), 0x7, {.d_i32 = a->len}}, {_SLIT(")"), 0, { .d_c = 0 }}})));
  array_ensure_cap(a, (int)(a->len + size));
  int elem_size = a->element_size;
  void* iptr = array_get_unsafe(/*rec*/*a, i);
  memmove(array_get_unsafe(/*rec*/*a, (int)(i + size)), iptr, (u64)(((u64)((int)(a->len - i))) * ((u64)(elem_size))));
  memcpy(iptr, val, (u64)(((u64)(size)) * ((u64)(elem_size))));
  a->len += size;
}

void array_prepend(array* a, void* val) { array_insert(a, 0, val); }

void array_prepend_many(array* a, void* val, int size) { array_insert_many(a, 0, val, size); }

void array_delete(array* a, int i) { array_delete_many(a, i, 1); }

void array_delete_many(array* a, int i, int size) {
  if (i < 0 || (int)(i + size) > a->len) {
    string endidx = (size > 1 ? ( str_intp(2, _MOV((StrIntpData[]){{_SLIT(".."), /*100 &int*/0x7, {.d_i32 = (int)(i + size)}}, {_SLIT0, 0, { .d_c = 0 }}}))) : (_SLIT("")));
    __panic( str_intp(4, _MOV((StrIntpData[]){{LANG(JAEYEONG_ERR_ARR_DELETE_OOR), 0x7, {.d_i32 = i}}, {_SLIT0, 0x10, {.d_s = endidx}}, {_SLIT(", a.len == "), 0x7, {.d_i32 = a->len}}, {_SLIT(")"), 0, { .d_c = 0 }}})));
  }
  if (ArrayFlags_all(&a->flags, (ArrayFlags__noshrink | ArrayFlags__noslices))) {
    memmove(((u8*)(a->data)) + (u64)(((u64)(i)) * ((u64)(a->element_size))), ((u8*)(a->data)) + (u64)(((u64)((int)(i + size))) * ((u64)(a->element_size))), (u64)(((u64)((int)((int)(a->len - i) - size))) * ((u64)(a->element_size))));
    a->len -= size;
    return;
  }
  void* old_data = a->data;
  int new_size = (int)(a->len - size);
  int new_cap = (new_size == 0 ? (1) : (new_size));
  a->data = jcalloc((u64)(((u64)(new_cap)) * ((u64)(a->element_size))));
  memcpy(a->data, old_data, (u64)(((u64)(i)) * ((u64)(a->element_size))));
  memcpy(((u8*)(a->data)) + (u64)(((u64)(i)) * ((u64)(a->element_size))), ((u8*)(old_data)) + (u64)(((u64)((int)(i + size))) * ((u64)(a->element_size))), (u64)(((u64)((int)((int)(a->len - i) - size))) * ((u64)(a->element_size))));
  if (ArrayFlags_has(&a->flags, ArrayFlags__noslices)) jfree(old_data);
  a->len = new_size;
  a->cap = new_cap;
}

void array_clear(array* a) { a->len = 0; }
void array_reset(array* a) { memset(a->data, 0, (int)(a->len * a->element_size)); }
void array_trim(array* a, int index) { if (index < a->len) a->len = index; }

void array_drop(array* a, int num) {
  if (num <= 0) return;
  int n = (num <= a->len ? (num) : (a->len));
  u64 blen = (u64)(((u64)(n)) * ((u64)(a->element_size)));
  a->data = ((u8*)(a->data)) + blen;
  a->offset += ((int)(blen));
  a->len -= n;
  a->cap -= n;
}

void* array_get_unsafe(array a, int i) { return ((u8*)(a.data)) + (u64)(((u64)(i)) * ((u64)(a.element_size))); }

void* array_get(array a, int i) {
  if (i < 0 || i >= a.len) __panic( str_intp(3, _MOV((StrIntpData[]){{LANG(JAEYEONG_ERR_ARR_GET_OOR), 0x7, {.d_i32 = i}}, {_SLIT(", a.len == "), 0x7, {.d_i32 = a.len}}, {_SLIT(")"), 0, { .d_c = 0 }}})));
  return ((u8*)(a.data)) + (u64)(((u64)(i)) * ((u64)(a.element_size)));
}

void* array_get_with_check(array a, int i) {
  if (i < 0 || i >= a.len) return 0;
  return ((u8*)(a.data)) + (u64)(((u64)(i)) * ((u64)(a.element_size)));
}

void* array_first(array a) {
  if (a.len == 0) __panic(LANG(JAEYEONG_ERR_ARR_FIRST_EMPTY));
  return a.data;
}

void* array_last(array a) {
  if (a.len == 0) __panic(LANG(JAEYEONG_ERR_ARR_LAST_EMPTY));
  return ((u8*)(a.data)) + (u64)(((u64)((int)(a.len - 1))) * ((u64)(a.element_size)));
}

void* array_pop(array* a) {
  if (a->len == 0) __panic(LANG(JAEYEONG_ERR_ARR_POP_EMPTY));
  int new_len = (int)(a->len - 1);
  u8* last_elem = ((u8*)(a->data)) + (u64)(((u64)(new_len)) * ((u64)(a->element_size)));
  a->len = new_len;
  return last_elem;
}

void array_delete_last(array* a) {
  if (a->len == 0) __panic(LANG(JAEYEONG_ERR_ARR_POP_EMPTY));
  a->len--;
}

array array_slice(array a, int start, int _end) {
  int end = (_end == _const_max_int ? (a.len) : (_end));
  #if !defined(CUSTOM_DEFINE_no_bounds_checking)
  {
    if (start > end) {
      __panic( str_intp(3, _MOV((StrIntpData[]){{LANG(JAEYEONG_ERR_ARR_SLICE_INV_INDEX), /*100 &int*/0x7, {.d_i32 = start}}, {_SLIT(" > "), /*100 &int*/0x7, {.d_i32 = end}}, {_SLIT(")"), 0, { .d_c = 0 }}})));
      UNREACHABLE();
    }
    if (end > a.len) {
      __panic( str_intp(3, _MOV((StrIntpData[]){{LANG(JAEYEONG_ERR_ARR_SLICE_BOOR), /*100 &int*/0x7, {.d_i32 = end}}, {_SLIT(" >= "), /*100 &int*/0x7, {.d_i32 = a.len}}, {_SLIT(")"), 0, { .d_c = 0 }}})));
      UNREACHABLE();
    }
    if (start < 0) {
      __panic(str_intp(2, _MOV((StrIntpData[]){{LANG(JAEYEONG_ERR_ARR_SLICE_BOOR), /*100 &int*/0x7, {.d_i32 = start}}, {_SLIT(" < 0)"), 0, { .d_c = 0 }}})));
      UNREACHABLE();
    }
  }
  #endif
  u64 offset = (u64)(((u64)(start)) * ((u64)(a.element_size)));
  u8* data = ((u8*)(a.data)) + offset;
  int l = (int)(end - start);
  array res = ((array){.data = data,.offset = (int)(a.offset + ((int)(offset))),.len = l,.cap = l,.flags = 0,.element_size = a.element_size,});
  return res;
}

array array_slice_ni(array a, int _start, int _end) {
  int end = (_end == _const_max_int ? (a.len) : (_end));
  int start = _start;
  if (start < 0) {
    start = (int)(a.len + start);
    if (start < 0) {
      start = 0;
    }
  }
  if (end < 0) {
    end = (int)(a.len + end);
    if (end < 0) {
      end = 0;
    }
  }
  if (end >= a.len) {
    end = a.len;
  }
  if (start >= a.len || start > end) {
    array res = ((array){.data = a.data,.offset = 0,.len = 0,.cap = 0,.flags = 0,.element_size = a.element_size,});
    return res;
  }
  u64 offset = (u64)(((u64)(start)) * ((u64)(a.element_size)));
  u8* data = ((u8*)(a.data)) + offset;
  int l = (int)(end - start);
  array res = ((array){.data = data,.offset = (int)(a.offset + ((int)(offset))),.len = l,.cap = l,.flags = 0,.element_size = a.element_size,});
  return res;
}

array array_clone_static_to_depth(array a, int depth) {
  return array_clone_to_depth(&a, depth);
}

array array_clone(array* a) {
  return array_clone_to_depth(a, 0);
}

array array_clone_to_depth(array* a, int depth) {
  array arr = ((array){.data = jcalloc((u64)(((u64)(a->cap)) * ((u64)(a->element_size)))),.offset = 0,.len = a->len,.cap = a->cap,.flags = 0,.element_size = a->element_size,});
  if (depth > 0 && _us32_eq(sizeof(array),a->element_size) && a->len >= 0 && a->cap >= a->len) {
    for (int i = 0; i < a->len; ++i) {
      array ar = ((array){.data = 0,.offset = 0,.len = 0,.cap = 0,.flags = 0,.element_size = 0,});
      memcpy(&ar, array_get_unsafe(/*rec*/*a, i), ((int)(sizeof(array))));
      array ar_clone = array_clone_to_depth(&ar, (int)(depth - 1));
      array_set_unsafe(&arr, i, &ar_clone);
    }
    return arr;
  } else {
    if (a->data != 0) {
      memcpy(((u8*)(arr.data)), a->data, (u64)(((u64)(a->cap)) * ((u64)(a->element_size))));
    }
    return arr;
  }
  return (array){.data = 0,.offset = 0,.len = 0,.cap = 0,.element_size = 0,};
}

void array_set(array* a, int i, void* val) {
  if (i < 0 || i >= a->len) {
    __panic( str_intp(3, _MOV((StrIntpData[]){{LANG(JAEYEONG_ERR_ARR_SET_OOR), /*100 &int*/0x7, {.d_i32 = i}}, {_SLIT(", a.len == "), /*100 &int*/0x7, {.d_i32 = a->len}}, {_SLIT(")"), 0, { .d_c = 0 }}})));
    UNREACHABLE();
  }
  memcpy(((u8*)(a->data)) + (u64)(((u64)(a->element_size)) * ((u64)(i))), val, a->element_size);
}

void array_push(array* a, void* val) {
  if (a->len >= a->cap) array_ensure_cap(a, (int)(a->len + 1));
  memcpy(((u8*)(a->data)) + (u64)(((u64)(a->element_size)) * ((u64)(a->len))), val, a->element_size);
  a->len++;
}

void array_push_many(array* a3, void* val, int size) {
  if (size <= 0 || val == ((void*)0)) return;
  array_ensure_cap(a3, (int)(a3->len + size));
  if (a3->data == val && a3->data != 0) {
    array copy = array_clone(a3);
    memcpy(((u8*)(a3->data)) + (u64)(((u64)(a3->element_size)) * ((u64)(a3->len))), copy.data, (u64)(((u64)(a3->element_size)) * ((u64)(size))));
  } else {
    if (a3->data != 0 && val != 0)
      memcpy(((u8*)(a3->data)) + (u64)(((u64)(a3->element_size)) * ((u64)(a3->len))), val, (u64)(((u64)(a3->element_size)) * ((u64)(size))));
  }
  a3->len += size;
}

void array_free(array* a) {
  if (ArrayFlags_has(&a->flags, ArrayFlags__nofree)) {
    __panic(LANG(JAEYEONG_ERR_FREE_NOFREE));
    UNREACHABLE();
  }
  u8* mblock_ptr = ((u8*)((u64)(((u64)(a->data)) - ((u64)(a->offset)))));
  jfree(mblock_ptr);
  a->data = ((void*)0);
}

string Array_string_join(Array_string a, string sep) {
  if (a.len == 0) { return _SLIT(""); }
  int len = 0;
  for (int _t2 = 0; _t2 < a.len; ++_t2) {
    string val = ((string*)a.data)[_t2];
    len += (int)(val.len + sep.len);
  }
  len -= sep.len;
  string res = ((string){.str = malloc_noscan((int)(len + 1)), .len = len});
  int idx = 0;
  for (int i = 0; i < a.len; ++i) {
    string val = ((string*)a.data)[i];
    { // Unsafe block
      memcpy(((void*)(res.str + idx)), val.str, val.len);
      idx += val.len;
    }
    if (i != (int)(a.len - 1)) {
      { // Unsafe block
        memcpy(((void*)(res.str + idx)), sep.str, sep.len);
        idx += sep.len;
      }
    }
  }
  res.str[res.len] = 0;
  return res;
}