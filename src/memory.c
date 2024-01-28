#include <stdio.h>
#include <stdlib.h>
#include "jaeyeong.h"

i64 total_memory = ((i64)(0));

DONOTUSE u8* prealloc_calloc(isize n) {
  UNREACHABLE();
  return ((u8*)(0));
}

DONOTUSE u8* prealloc_malloc(isize n) {
  UNREACHABLE();
  return ((u8*)(0));
}

u8* jcalloc(isize n) {
	#if defined(_JAEYEONG_DEV_TRACE_CALLOC)
	{
		total_memory += n;
		fprintf(stderr, "jcalloc %6d total %10d\n", n, total_memory);
	}
	#endif
	if (n < 0) {
		__panic( str_intp(2, _MOV((StrIntpData[]){{_SLIT("calloc("), /*100 &isize*/0x9, {.d_i64 = n}}, {_SLIT(" < 0)"), 0, { .d_c = 0 }}})));
		UNREACHABLE();
	} else if (n == 0) return ((u8*)(0));
	#if defined(_JAEYEONG_PREALLOC)
  {
    return prealloc_calloc(n);
  }
	#else
  {
    return calloc(1, n);
  }
	#endif
	return 0;
}

u8* jcalloc_noscan(isize n) {
	#if defined(_JAEYEONG_DEV_TRACE_CALLOC)
	{
		total_m += n;
		fprintf(stderr, "jcalloc_noscan %6d total %10d\n", n, total_m);
	}
	#endif
	#if defined(_JAEYEONG_PREALLOC)
  {
    return prealloc_calloc(n);
  }
  #else
  {
    return jcalloc(n);
  }
	#endif
	return 0;
}

UNSAFE u8* jmalloc(isize n) {
	#if defined(_JAEYEONG_DEV_TRACE_MALLOC)
	{
		total_m += n;
		fprintf(stderr, "jmalloc %6d total %10d\n", n, total_m);
	}
	#endif
	if (n < 0) {
		__panic( str_intp(2, _MOV((StrIntpData[]){{_SLIT("malloc("), /*100 &isize*/0x9, {.d_i64 = n}}, {_SLIT(" < 0)"), 0, { .d_c = 0 }}})));
		UNREACHABLE();
	}
	u8* res = ((u8*)(0));
	#if defined(_JAEYEONG_PREALLOC) 
  {
    return prealloc_malloc(n);
  }
	#else
  {
    res = malloc(n);
  }
	#endif
	if (res == 0) {
		__panic( str_intp(2, _MOV((StrIntpData[]){{_SLIT("malloc("), /*100 &isize*/0x9, {.d_i64 = n}}, {_SLIT(") failed"), 0, { .d_c = 0 }}})));
		UNREACHABLE();
	}
	#if defined(_JAEYEONG_DEBUG_MALLOC)
  {
    memset(res, 0x4D, n);
  }
	#endif
	return res;
}

UNSAFE u8* malloc_noscan(isize n) {
	#if defined(_JAEYEONG_DEV_TRACE_MALLOC)
	{
		total_m += n;
		fprintf(stderr, "malloc_noscan %6d total %10d\n", n, total_m);
	}
	#endif
	if (n < 0) {
		__panic( str_intp(2, _MOV((StrIntpData[]){{_SLIT("malloc_noscan("), /*100 &isize*/0x9, {.d_i64 = n}}, {_SLIT(" < 0)"), 0, { .d_c = 0 }}})));
		UNREACHABLE();
	}
	u8* res = ((u8*)(0));
	#if defined(_JAEYEONG_PREALLOC)
  { 
    return prealloc_malloc(n);
  }
  #else
  {
    res = malloc(n);
  }
	#endif
	if (res == 0) {
		__panic( str_intp(2, _MOV((StrIntpData[]){{_SLIT("malloc_noscan("), /*100 &isize*/0x9, {.d_i64 = n}}, {_SLIT(") failed"), 0, { .d_c = 0 }}})));
		UNREACHABLE();
	}
	#if defined(_JAEYEONG_DEBUG_MALLOC)
  { 
    memset(res, 0x4D, n);
  }
	#endif
	return res;
}

UNSAFE u8* jrealloc(u8* b, isize n) {
	#if defined(_JAEYEONG_DEV_TRACE_REALLOC)
  {
    fprintf(stderr, "jrealloc %6d\n", n);
  }
	#endif
	u8* new_ptr = ((u8*)(0));
	#if defined(_JAEYEONG_PREALLOC)
	{
		new_ptr = jmalloc(n);
		memcpy(new_ptr, b, n);
		return new_ptr;
	}
  #else
  {
    new_ptr = realloc(b, n);
  }
	#endif
	if (new_ptr == 0) {
		__panic( str_intp(2, _MOV((StrIntpData[]){{_SLIT("realloc("), /*100 &isize*/0x9, {.d_i64 = n}}, {_SLIT(") failed"), 0, { .d_c = 0 }}})));
		UNREACHABLE();
	}
	return new_ptr;
}

UNSAFE u8* realloc_data(u8* old_data, int old_size, int new_size) {
	#if defined(_JAEYEONG_DEV_TRACE_REALLOC)
  { 
    fprintf(stderr, "realloc_data old_size: %6d new_size: %6d\n", old_size, new_size);
  }
	#endif
	#if defined(_JAEYEONG_PREALLOC) 
  {
    return prealloc_realloc(old_data, old_size, new_size);
  }
	#endif
	#if defined(CUSTOM_DEFINE_debug_realloc)
	{
		u8* new_ptr = jmalloc(new_size);
		int min_size = (old_size < new_size ? (old_size) : (new_size));
		memcpy(new_ptr, old_data, min_size);
		memset(old_data, 0x57, old_size);
		jfree(old_data);
		return new_ptr;
	}
	#endif
	u8* nptr = ((u8*)(0));
	nptr = realloc(old_data, new_size);
	if (nptr == 0) {
		__panic( str_intp(4, _MOV((StrIntpData[]){{_SLIT("realloc_data("), /*117 &u8*/0x17, {.d_p = (void*)(old_data)}}, {_SLIT(", "), /*100 &int*/0x7, {.d_i32 = old_size}}, {_SLIT(", "), /*100 &int*/0x7, {.d_i32 = new_size}}, {_SLIT(") failed"), 0, { .d_c = 0 }}})));
		UNREACHABLE();
	}
	return nptr;
}

UNSAFE void* memdup(void* src, isize sz) {
	#if defined(_JAEYEONG_DEV_TRACE_MEMDUP)
  {
    fprintf(stderr, "memdup size: %10d\n", sz);
  }
	#endif
	if (sz == 0) return jcalloc(1);
	u8* mem = jmalloc(sz);
	return memcpy(mem, src, sz);
}

UNSAFE void* memdup_noscan(void* src, isize sz) {
	#if defined(_JAEYEONG_DEV_TRACE_MEMDUP) 
  {
    fprintf(stderr, "memdup_noscan size: %10d\n", sz);
  }
	#endif
	if (sz == 0) return jcalloc_noscan(1);
	u8* mem = malloc_noscan(sz);
	return memcpy(mem, src, sz);
}

UNSAFE void jfree(void* ptr) {
	#if defined(_JAEYEONG_PREALLOC) 
  {
    return;
  }
	#else
  {
    free(ptr);
  }
	#endif
}