#ifndef __JAEYEONG_APUA_H__
#define __JAEYEONG_APUA_H__
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
typedef int64_t i64;
typedef int16_t i16;
typedef int8_t i8;
typedef uint64_t u64;
typedef uint32_t u32;
typedef uint8_t u8;
typedef uint16_t u16;
typedef u8 byte;
typedef int32_t i32;
typedef uint32_t rune;
typedef size_t usize;
typedef ptrdiff_t isize;
typedef float f32;
typedef double f64;
typedef int64_t int_literal;

#define UNSAFE
#define DONOTUSE

#if (defined (__STDC_VERSION__) && __STDC_VERSION__ > 201710L) \
  || (defined(__cplusplus) && __cplusplus >= 201103)
# define _jNULL nullptr
#else
# define _jNULL NULL
#endif /* __STDC_VERSION__ */

#ifdef __cplusplus
  #include <utility>
	#define _MOV std::move
#else
	#define _MOV
#endif /* __cplusplus */
#define ADDR(type, expr) (&((type[]){expr}[0]))

typedef struct string string;
typedef union  StrIntpMem StrIntpMem;
typedef struct StrIntpData StrIntpData;
typedef struct strconv__BF_param strconv__BF_param;
typedef union  strconv__Float32u strconv__Float32u;
typedef struct strconv__Dec32 strconv__Dec32;
typedef union  strconv__Uf32 strconv__Uf32;
typedef struct strconv__Dec64 strconv__Dec64;
typedef struct strconv__Uint128 strconv__Uint128;
typedef union  strconv__Uf64 strconv__Uf64;
typedef struct multi_return_strconv__Dec32_bool multi_return_strconv__Dec32_bool;
typedef struct multi_return_strconv__Dec64_bool multi_return_strconv__Dec64_bool;
typedef struct array array;
typedef struct CompilerOptions CompilerOptions;
typedef enum   Language Language;
typedef enum   Edition Edition;
typedef struct array Array_u8;
typedef        Array_u8 strings__Builder;

static inline u64 __at_least_one(i64 n) { return (n == 0U) ? (1U) : (n); } 
static inline bool _us32_gt(uint32_t a, int32_t b) { return a > INT32_MAX || (int32_t)a > b; }
static inline bool _us32_ge(uint32_t a, int32_t b) { return a >= INT32_MAX || (int32_t)a >= b; }
static inline bool _us32_eq(uint32_t a, int32_t b) { return a <= INT32_MAX && (int32_t)a == b; }
static inline bool _us32_ne(uint32_t a, int32_t b) { return a > INT32_MAX || (int32_t)a != b; }
static inline bool _us32_le(uint32_t a, int32_t b) { return a <= INT32_MAX && (int32_t)a <= b; }
static inline bool _us32_lt(uint32_t a, int32_t b) { return a < INT32_MAX && (int32_t)a < b; }
static inline bool _us64_gt(uint64_t a, int64_t b) { return a > INT64_MAX || (int64_t)a > b; }
static inline bool _us64_ge(uint64_t a, int64_t b) { return a >= INT64_MAX || (int64_t)a >= b; }
static inline bool _us64_eq(uint64_t a, int64_t b) { return a <= INT64_MAX && (int64_t)a == b; }
static inline bool _us64_ne(uint64_t a, int64_t b) { return a > INT64_MAX || (int64_t)a != b; }
static inline bool _us64_le(uint64_t a, int64_t b) { return a <= INT64_MAX && (int64_t)a <= b; }
static inline bool _us64_lt(uint64_t a, int64_t b) { return a < INT64_MAX && (int64_t)a < b; }

//! @def UNREACHABLE()
//! @brief Triggers an error when unreachable code is reached.
//!
//! This macro triggers an error when code that should be unreachable is reached.
//! It prints an error message to the standard error output and terminates the program.
#define UNREACHABLE() \
  do { \
    fprintf(stderr, "A-pu-A! UNREACHABLE code reached in %s at line %d\n", __FILE__, __LINE__); \
    exit(EXIT_FAILURE); \
  } while (0)
#endif