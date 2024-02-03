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
#if defined(__LP64__) || defined(_WIN64)
typedef __int128_t i128;
typedef __uint128_t u128;
#endif

typedef u8 ArrFixedu8_4096 [4096];

#define UNSAFE
#define DONOTUSE

#define EMPTY_STRUCT_DEC
#define EMPTY_STRUCT_INIT

#ifdef _MSC_VER
  #undef EMPTY_STRUCT_DEC
  #undef EMPTY_STRUCT_INIT
  #define EMPTY_STRUCT_DEC unsigned char _dummy_pad
  #define EMPTY_STRUCT_INIT 0
#endif

#ifdef __TINYC__
  #undef EMPTY_STRUCT_DEC
  #undef EMPTY_STRUCT_INIT
  #define EMPTY_STRUCT_DEC unsigned char _dummy_pad
  #define EMPTY_STRUCT_INIT 0
#endif

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

//! @brief 주어진 표현식을 배열로 변환하고 그 주소를 반환하는 매크로입니다.
//! @details 이 매크로는 `expr` 표현식을 `type` 타입의 임시 배열로 변환하고, 그 배열의 첫 번째 요소의 주소를 반환합니다. 
//! 이를 통해 표현식의 결과를 주소로 사용할 수 있습니다.
//! @param type 표현식의 타입입니다.
//! @param expr 주소를 얻을 표현식입니다.
#define ADDR(type, expr) (&((type[]){expr}[0]))

//! @brief 주어진 구조체 타입에서 특정 필드까지의 오프셋을 계산하는 매크로입니다.
//! @details 이 매크로는 `PTYPE` 타입의 구조체에서 `FIELDNAME` 필드까지의 바이트 단위 오프셋을 계산합니다. 
//! 이 매크로는 `NULL` 포인터를 `PTYPE` 타입으로 캐스팅하여 필드의 주소를 얻는 방식으로 작동합니다.
//! @param PTYPE 구조체의 타입입니다.
//! @param FIELDNAME 오프셋을 계산할 필드의 이름입니다.
#define __offsetof(PTYPE,FIELDNAME) ((size_t)(&((PTYPE *)0)->FIELDNAME))

//! @brief 주어진 구조체 포인터에서 특정 필드까지의 오프셋을 계산하는 매크로입니다.
//! @details 이 매크로는 `ptr`이 가리키는 구조체에서 `FIELDNAME` 필드까지의 바이트 단위 오프셋을 계산합니다. 
//! `PTYPE`은 구조체의 타입을 나타냅니다.
//! @param ptr 오프셋을 계산할 구조체의 포인터입니다.
//! @param PTYPE 구조체의 타입입니다.
//! @param FIELDNAME 오프셋을 계산할 필드의 이름입니다.
#define __offsetof_ptr(ptr,PTYPE,FIELDNAME) ((size_t)((byte *)&((PTYPE *)ptr)->FIELDNAME - (byte *)ptr))

struct multi_return_int_int {
  int arg0;
  int arg1;
};

typedef struct string string;
typedef struct CompilerMessage CompilerMessage;
typedef struct Error Error;
typedef struct MessageError MessageError;
typedef struct ErrorInterface ErrorInterface;
typedef struct Warning Warning;
typedef struct Info Info;
typedef struct Option Option;
typedef        Option i8Option;
typedef        Option i16Option;
typedef        Option i32Option;
typedef        Option i64Option;
typedef        Option u8Option;
typedef        Option u16Option;
typedef        Option u32Option;
typedef        Option u64Option;
typedef        Option usizeOption;
typedef        Option isizeOption;
typedef        Option f32Option;
typedef        Option f64Option;
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
typedef struct multi_return_int_int multi_return_int_int;
typedef struct array array;
typedef struct CompilerOptions CompilerOptions;
typedef enum   Language Language;
typedef enum   Edition Edition;
typedef struct array Array_token;
typedef        array Array_string;
typedef        array Array_u8;
typedef        array Array_int;
typedef        Array_u8 strings__Builder;
typedef struct multi_return_u32_u32 multi_return_u32_u32;
typedef struct DenseArray DenseArray;
typedef struct map map;
typedef        map Map_string_bool;
typedef        map Map_string_Array_string;
typedef        map Map_String_String;
typedef struct LinesCache LinesCache;
typedef        Option OptionApuaFile;
typedef        Option OptionArrayString;
typedef        Option OptionString;
typedef struct Result Result;
typedef        Result ResultString;
typedef        Result ResultFilePtr; 
typedef        Result ResultInt;
typedef        Result ResultStringsBuilder;
typedef struct token token;
typedef struct tokpos tokpos;
typedef struct lexer lexer;
typedef struct Preferences Preferences;
typedef u64 (*MapHashFn)(void*);
typedef bool (*MapEqFn)(void*, void*);
typedef void (*MapCloneFn)(void*, void*);
typedef void (*MapFreeFn)(void*);

//! @brief 입력값이 0인 경우 1을 반환하고, 그렇지 않은 경우 입력값을 반환하는 함수입니다.
//! @param n 입력값입니다. 이 값이 0인 경우 1을 반환하고, 그렇지 않은 경우 입력값 그대로를 반환합니다.
//! @return 입력값이 0인 경우 1, 그렇지 않은 경우 입력값 그대로를 반환합니다.
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