#ifndef __JAEYEONG_MEMORY_H__
#define __JAEYEONG_MEMORY_H__
#include <stdlib.h>
#include "apua.h"

DONOTUSE u8* prealloc_calloc(isize n);
DONOTUSE u8* prealloc_malloc(isize n);
u8* jcalloc(isize n);
u8* jcalloc_noscan(isize n);
UNSAFE u8* jmalloc(isize n);
UNSAFE u8* malloc_noscan(isize n);
UNSAFE u8* jrealloc(u8* b, isize n);
UNSAFE u8* realloc_data(u8* old_data, int old_size, int new_size);
UNSAFE void* memdup(void* src, isize sz);
UNSAFE void* memdup_noscan(void* src, isize sz);
UNSAFE void jfree(void* ptr);

#endif /* __JAEYEONG_MEMORY_H__ */