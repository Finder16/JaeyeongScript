#ifndef __JAEYEONG_STRINGS_H__
#define __JAEYEONG_STRINGS_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <windows.h>
#include <stdarg.h>
#include "apua.h"
#include "jarray.h"
#include "jmem.h"

//! @struct string
//! @brief Represents a string.
//!
//! This structure represents a string in the program.
//! It contains a pointer to a byte array, the length of the array, 
//! and a flag indicating whether the string is a literal.
struct string {
  // The pointer to the byte array representing the string.
  byte* str;
  // The length of the string.
  size_t len;
  // A flag indicating whether the string is a literal. If it is a literal, it should not be freed.
  int is_lit;
};

//! @brief 다양한 데이터 타입을 저장할 수 있는 유니온입니다.
//! @details `StrIntpMem`은 다양한 데이터 타입을 저장할 수 있는 유니온입니다.
union StrIntpMem {
  u32 d_c; //! @brief d_c 32비트 부호 없는 정수를 저장합니다.
  u8 d_u8; //! @brief d_u8 8비트 부호 없는 정수를 저장합니다.
  i8 d_i8; //! @brief d_i8 8비트 부호 있는 정수를 저장합니다.
  u16 d_u16; //! @brief d_u16 16비트 부호 없는 정수를 저장합니다.
  i16 d_i16; //! @brief d_i16 16비트 부호 있는 정수를 저장합니다
  u32 d_u32; //! @brief d_u32 32비트 부호 없는 정수를 저장합니다.
  int d_i32; //! @brief d_i32 32비트 부호 있는 정수를 저장합니다.
  u64 d_u64; //! @brief d_u64 64비트 부호 없는 정수를 저장합니다.
  i64 d_i64; //! @brief d_i64 64비트 부호 있는 정수를 저장합니다.
  f32 d_f32; //! @brief d_f32 32비트 부동 소수점 수를 저장합니다.
  f64 d_f64; //! @brief d_f64 64비트 부동 소수점 수를 저장합니다.
  string d_s; //! @brief d_s 문자열을 저장합니다.
  string d_r; //! @brief d_r 문자열을 저장합니다.
  void* d_p; //! @brief d_p 포인터를 저장합니다.
  void* d_vp; //! @brief d_vp void 포인터를 저장합니다.
};

struct StrIntpData {
  string str;
  u32 fmt;
  StrIntpMem d;
};

typedef enum {
  StrIntFlag__UpperCase = (1 << 5)
} StrIntFlag;

typedef enum {
  StrIntpType__si_no_str = 0, // 0
  StrIntpType__si_c, // 0+1
  StrIntpType__si_u8, // 0+2
  StrIntpType__si_i8, // 0+3
  StrIntpType__si_u16, // 0+4
  StrIntpType__si_i16, // 0+5
  StrIntpType__si_u32, // 0+6
  StrIntpType__si_i32, // 0+7
  StrIntpType__si_u64, // 0+8
  StrIntpType__si_i64, // 0+9
  StrIntpType__si_e32, // 0+10
  StrIntpType__si_e64, // 0+11
  StrIntpType__si_f32, // 0+12
  StrIntpType__si_f64, // 0+13
  StrIntpType__si_g32, // 0+14
  StrIntpType__si_g64, // 0+15
  StrIntpType__si_s, // 0+16
  StrIntpType__si_p, // 0+17
  StrIntpType__si_r, // 0+18
  StrIntpType__si_vp, // 0+19
}  StrIntpType;

#define _CLRFlag(a) ((a) &~ StrIntFlag__UpperCase)

string string_substr(string s, int start, int _end);

//! @brief 빈 문자열을 생성하는 함수입니다.
//! @details 이 함수는 빈 문자열을 생성하고 반환합니다. 
//! `_SLIT0` 매크로는 빈 문자열을 나타내는 매크로입니다.
//! @return 빈 문자열입니다.
string make_empty_string();

//! @brief 주어진 wide 문자열을 일반 문자열로 변환하는 함수입니다.
//! @details 이 함수는 주어진 wide 문자열(`wchar_t*`)을 일반 문자열(`string`)로 변환합니다. 
//! 변환은 `string_from_wide` 함수를 사용하여 수행됩니다. 이 함수는 wide 문자열을 입력으로 받아 일반 문자열을 반환합니다.
//! 입력 wide 문자열은 `u16*` 형태로 캐스팅되어 `string_from_wide` 함수에 전달됩니다.
//! @param wstr 변환할 wide 문자열입니다.
//! @return 변환된 일반 문자열입니다.
string wchar_to_string(const wchar_t* wstr);

//! @brief 두 문자열을 연결하는 함수입니다.
//! @details 이 함수는 두 문자열을 연결하고 반환합니다. 
//! 새로운 문자열의 길이는 두 입력 문자열의 길이의 합이며, `jmalloc` 함수를 사용하여 새로운 문자열의 메모리를 할당합니다.
//! `memcpy` 함수를 사용하여 입력 문자열의 내용을 새로운 문자열로 복사합니다.
//! @param s 첫 번째 문자열입니다.
//! @param a 두 번째 문자열입니다.
//! @return 연결된 새로운 문자열입니다.
string string__plus(string s, string a);

//! @brief 주어진 포인터와 길이로 문자열을 생성하는 함수입니다.
//! @details 이 함수는 주어진 포인터와 길이로 문자열을 생성하고 반환합니다. 
//! 생성된 문자열은 리터럴이 아닙니다(`is_lit = 0`).
//! @param bp 문자열의 시작 포인터입니다.
//! @param len 문자열의 길이입니다.
//! @return 생성된 문자열입니다.
string string_with_len(u8* bp, int len);

//! @brief 주어진 초기 크기로 새로운 문자열 빌더를 생성하는 함수입니다.
//! @details 이 함수는 주어진 초기 크기로 새로운 문자열 빌더를 생성하고 반환합니다. 
//! 문자열 빌더는 `__new_array_with_default` 함수를 사용하여 생성되며, 이 함수는 초기 값, 배열 크기, 요소의 크기, 기본 값으로 배열을 생성합니다.
//! 생성된 문자열 빌더의 플래그는 `ArrayFlags__noslices`로 설정됩니다.
//! @param initial_size 문자열 빌더의 초기 크기입니다.
//! @return 생성된 문자열 빌더입니다.
strings__Builder strings__new_builder(int initial_size);

//! @brief 문자열에 특정 문자가 포함되어 있는지 확인하는 함수입니다.
//! @details 이 함수는 문자열 `s`와 문자 `x`를 입력으로 받아, `s`에 `x`가 포함되어 있는지 확인합니다.
//! @param s 검사할 문자열입니다.
//! @param x 찾을 문자입니다.
//! @return `x`가 `s`에 포함되어 있으면 `true`, 그렇지 않으면 `false`를 반환합니다.
bool string_contains_u8(string s, u8 x);

//! @brief 문자열에 특정 부분 문자열이 포함되어 있는지 확인하는 함수입니다.
//! @details 이 함수는 문자열 `s`와 부분 문자열 `substr`를 입력으로 받아, `s`에 `substr`가 포함되어 있는지 확인합니다.
//! @param s 검사할 문자열입니다.
//! @param substr 찾을 부분 문자열입니다.
//! @return `substr`가 `s`에 포함되어 있으면 `true`, 그렇지 않으면 `false`를 반환합니다.
bool string_contains(string s, string substr);

//! @brief 문자열에 특정 문자들 중 어느 하나라도 포함되어 있는지 확인하는 함수입니다.
//! @details 이 함수는 문자열 `s`와 문자들의 집합 `chars`를 입력으로 받아, `s`에 `chars` 중 어느 하나라도 포함되어 있는지 확인합니다.
//! @param s 검사할 문자열입니다.
//! @param chars 찾을 문자들의 집합입니다.
//! @return `chars` 중 어느 하나라도 `s`에 포함되어 있으면 `true`, 그렇지 않으면 `false`를 반환합니다.
bool string_contains_any(string s, string chars);

//! @brief 문자열이 특정 문자들만으로 이루어져 있는지 확인하는 함수입니다.
//! @details 이 함수는 문자열 `s`와 문자들의 집합 `chars`를 입력으로 받아, `s`가 `chars`만으로 이루어져 있는지 확인합니다.
//! @param s 검사할 문자열입니다.
//! @param chars 찾을 문자들의 집합입니다.
//! @return `s`가 `chars`만으로 이루어져 있으면 `true`, 그렇지 않으면 `false`를 반환합니다.
bool string_contains_only(string s, string chars);

//! @brief 문자열에 특정 부분 문자열들 중 어느 하나라도 포함되어 있는지 확인하는 함수입니다.
//! @details 이 함수는 문자열 `s`와 부분 문자열들의 배열 `substrs`를 입력으로 받아, `s`에 `substrs` 중 어느 하나라도 포함되어 있는지 확인합니다.
//! @param s 검사할 문자열입니다.
//! @param substrs 찾을 부분 문자열들의 배열입니다.
//! @return `substrs` 중 어느 하나라도 `s`에 포함되어 있으면 `true`, 그렇지 않으면 `false`를 반환합니다.
bool string_contains_any_substr(string s, Array_string substrs);

//! @brief 문자열 내의 특정 문자열을 다른 문자열로 대체하는 함수입니다.
//! @details 이 함수는 문자열 `s`에서 `rep` 문자열을 찾아 `with` 문자열로 대체합니다. 
//! 만약 `s`가 비어있거나, `rep`가 비어있거나, `rep`의 길이가 `s`의 길이보다 크면 `s`의 복사본을 반환합니다. 
//! 또한 `s`가 `rep`를 포함하지 않으면 `s`의 복사본을 반환합니다.
//! @param s 대체할 대상 문자열입니다.
//! @param rep `s`에서 찾을 문자열입니다.
//! @param with `rep`를 대체할 문자열입니다.
//! @return `rep`가 `s`에서 대체된 새로운 문자열을 반환합니다. `rep`가 `s`에 없거나, `s` 또는 `rep`가 비어있는 경우, `s`의 복사본을 반환합니다.
string string_replace(string s, string rep, string with);

//! @brief 주어진 포인터와 길이로 문자열을 생성하는 함수입니다.
//! @details 이 함수는 주어진 포인터와 길이로 문자열을 생성하고 반환합니다. 
//! 생성된 문자열은 리터럴이 아닙니다(`is_lit = 0`).
//! @param bp 문자열의 시작 포인터입니다.
//! @param len 문자열의 길이입니다.
//! @return 생성된 문자열입니다.
string u8_string_with_len(u8* bp, int len);

//! @brief 문자열 빌더의 내용을 문자열로 변환하는 함수입니다.
//! @details 이 함수는 문자열 빌더의 내용을 문자열로 변환하고 반환합니다. 
//! 문자열 빌더의 내용은 `memdup_noscan` 함수를 사용하여 복사되며, 복사된 내용은 `u8_string_with_len` 함수를 사용하여 문자열로 변환됩니다.
//! 문자열 빌더는 변환 후에 비워집니다(`array_trim` 함수 사용).
//! @param b 변환할 문자열 빌더입니다.
//! @return 변환된 문자열입니다.
string strings__Builder_str(strings__Builder* b);

//! @brief 문자열 빌더를 해제하는 함수입니다.
//! @details 이 함수는 문자열 빌더의 메모리를 해제합니다. 
//! 문자열 빌더의 데이터가 `NULL`이 아닌 경우, `jfree` 함수를 사용하여 메모리를 해제하고, 데이터 포인터를 `NULL`로 설정합니다.
//! @param b 해제할 문자열 빌더입니다.
void strings__Builder_free(strings__Builder* b);

//! @brief 문자열을 대문자로 변환하는 함수입니다.
//! @details 이 함수는 문자열의 모든 소문자를 대문자로 변환합니다. 
//! 변환은 ASCII 코드를 사용하여 수행되며, 소문자('a'-'z')는 대문자('A'-'Z')로 변환됩니다.
//! 변환된 문자열은 새로운 메모리에 저장되며, 원래 문자열은 변경되지 않습니다.
//! @param s 대문자로 변환할 문자열입니다.
//! @return 대문자로 변환된 문자열입니다.
string string_to_upper(string s);

//! @brief 문자열을 복제하는 함수입니다.
//! @details 이 함수는 주어진 문자열을 복제하고 반환합니다. 
//! 복제는 `jmalloc` 함수를 사용하여 새로운 메모리를 할당하고, `memcpy` 함수를 사용하여 문자열의 내용을 복사하여 수행됩니다.
//! 복제된 문자열은 원래 문자열과 동일한 내용을 가지지만, 다른 메모리 위치에 저장됩니다.
//! @param a 복제할 문자열입니다.
//! @return 복제된 문자열입니다.
string string_clone(string a);

//! @brief 문자열을 생성하는 함수입니다.
//! @details 이 함수는 주어진 문자 배열(`s`)과 길이(`len`)를 사용하여 문자열을 생성하고 반환합니다. 
//! 문자 배열이 `NULL`인 경우, 에러 메시지를 출력하고 프로그램을 종료합니다.
//! @param s 문자열의 내용을 담고 있는 문자 배열입니다.
//! @param len 문자열의 길이입니다.
//! @return 생성된 문자열입니다.
string tos(u8* s, int len);

//! @brief 문자열 메모리를 해제하는 함수입니다.
//! @details 이 함수는 문자열의 메모리를 해제합니다. 
//! 문자열이 이미 해제된 상태(`is_lit == -98761234`)에서 다시 해제를 시도하면, 에러 메시지를 출력합니다.
//! 문자열이 리터럴(`is_lit == 1`)이거나 `NULL`인 경우, 메모리 해제를 수행하지 않습니다.
//! 그 외의 경우, `jfree` 함수를 사용하여 문자열 메모리를 해제하고, 문자열 포인터를 `NULL`로 설정하며, `is_lit` 값을 `-98761234`로 설정합니다.
//! @param s 메모리를 해제할 문자열입니다.
void string_free(string* s);

//! @brief 문자열이 특정 접미사로 끝나는지 확인하는 함수입니다.
//! @details 이 함수는 주어진 문자열(`wstr`)이 특정 접미사(`wsuffix`)로 끝나는지 확인합니다. 
//! 문자열이나 접미사가 `NULL`인 경우, `false`를 반환합니다.
//! 접미사의 길이가 문자열의 길이보다 긴 경우, `false`를 반환합니다.
//! 그 외의 경우, `wcsncmp` 함수를 사용하여 문자열의 끝 부분과 접미사를 비교하고, 일치하는 경우 `true`를 반환합니다.
//! @param wstr 접미사를 확인할 문자열입니다.
//! @param wsuffix 확인할 접미사입니다.
//! @return 문자열이 접미사로 끝나는 경우 `true`, 그렇지 않은 경우 `false`를 반환합니다.
bool endsWithW(const wchar_t *wstr, const wchar_t *wsuffix);

//! @brief 빈 문자열을 생성하는 매크로입니다.
//! @details 이 매크로는 빈 문자열을 생성합니다. 문자열의 내용은 빈 문자열(""), 길이는 0, 리터럴 플래그는 1입니다.
#define _SLIT0 (string){.str=(byte*)(""), .len=0, .is_lit=1}

//! @brief 주어진 문자열을 사용하여 문자열을 생성하는 매크로입니다.
//! @details 이 매크로는 주어진 문자열(`s`)을 사용하여 문자열을 생성합니다. 문자열의 내용은 주어진 문자열, 길이는 주어진 `문자열의 길이 - 1`, 리터럴 플래그는 `1`입니다.
//! @param s 문자열의 내용입니다.
#define _SLIT(s) ((string){.str=(byte*)("" s), .len=(sizeof(s)-1), .is_lit=1})

//! @brief 주어진 문자열과 길이를 사용하여 문자열을 생성하는 매크로입니다.
//! @details 이 매크로는 주어진 문자열(`s`)과 길이(`n`)를 사용하여 문자열을 생성합니다. 문자열의 내용은 주어진 문자열, 길이는 주어진 길이, 리터럴 플래그는 1입니다.
//! @param s 문자열의 내용입니다.
//! @param n 문자열의 길이입니다.
#define _SLEN(s, n) ((string){.str=(byte*)("" s), .len=n, .is_lit=1})

void StrIntpData_process_str_intp_data(StrIntpData* data, strings__Builder* sb);

//! @brief 문자열을 생성하는 함수입니다.
//! @details 이 함수는 주어진 데이터의 길이(`data_len`)와 `StrIntpData` 배열(`input_base`)을 입력으로 받아 문자열을 생성합니다. 
//! 각 `StrIntpData` 항목에 대해, 형식 플래그에서 `UpperCase` 플래그를 확인하고, 플래그를 지웁니다. 
//! 그런 다음 데이터의 유형에 따라 형식화된 데이터를 문자열 `str`에 추가합니다.
//! @param data_len 데이터의 길이입니다.
//! @param input_base 문자열의 내용을 담고 있는 `StrIntpData` 배열입니다.
//! @return 생성된 문자열입니다.
string str_intp(int data_len, StrIntpData* input_base);

bool fast_string_eq(string a, string b);

//! @brief 문자열 빌더에서 주어진 인덱스의 바이트를 반환하는 함수입니다.
//! @param b 바이트를 가져올 문자열 빌더입니다.
//! @param n 가져올 바이트의 인덱스입니다.
//! @return 인덱스 `n`에 있는 바이트입니다.
inline u8 strings__Builder_byte_at(strings__Builder* b, int n) { return (*(u8*)array_get(*(((Array_u8*)(b))), n)); }

//! @brief 문자열 빌더에 문자열을 추가하는 함수입니다.
//! @param b 문자열을 추가할 문자열 빌더입니다.
//! @param s 추가할 문자열입니다.
inline void strings__Builder_write_string(strings__Builder* b, string s) {
  if (s.len == 0) return;
  array_push_many(b, s.str, s.len);
}

//! @brief 문자열 빌더에 문자열을 추가하고 줄바꿈을 하는 함수입니다.
//! @param b 문자열을 추가할 문자열 빌더입니다.
//! @param s 추가할 문자열입니다.
inline void strings__Builder_writeln_string(strings__Builder* b, string s) {
  strings__Builder_write_string(b, s);
  strings__Builder_write_string(b, _SLIT("\n"));
}

void strings__Builder_write_ptr(strings__Builder* b, u8* ptr, int len);

u8 string_at(string s, int idx);

string string_repeat(string s, int count);

string string_trim(string s, string cutset);

multi_return_int_int string_trim_indexes(string s, string cutset);

static inline __attribute__((always_inline)) bool u8_is_space(u8 c) {
  return c == 32 || (c > 8 && c < 14) || c == 0x85 || c == 0xa0;
}

//! @brief 와이드 문자열을 일반 문자열로 변환하는 함수입니다.
//! @details 이 함수는 와이드 문자열(`_wstr`)과 그 길이(`len`)를 입력으로 받아 일반 문자열로 변환합니다. 
//! 먼저 `WideCharToMultiByte` 함수를 사용하여 와이드 문자열을 일반 문자열로 표현하는 데 필요한 문자 수를 계산합니다. 
//! 그런 다음 일반 문자열에 대한 메모리를 할당하고 `WideCharToMultiByte`를 다시 사용하여 와이드 문자열을 일반 문자열로 변환합니다. 
//! 마지막으로 변환된 일반 문자열을 반환합니다.
//! @param _wstr 변환할 와이드 문자열입니다.
//! @param len 와이드 문자열의 길이입니다.
//! @return 변환된 일반 문자열입니다.
static inline string string_from_wide2(u16* _wstr, int len) {
  int num_chars = WideCharToMultiByte(65001, 0U, _wstr, len, 0, 0, 0, 0);
  u8* str_to = malloc_noscan((int)(num_chars + 1));
  if (str_to != 0) {
    WideCharToMultiByte(65001, 0U, _wstr, len, ((char*)(str_to)), num_chars, 0, 0);
    memset(str_to + num_chars, 0, 1);
  }
  return  ((string){.str = str_to, .len = strlen((char*)str_to)});
}

//! @brief 와이드 문자열을 일반 문자열로 변환하는 함수입니다.
//! @details 이 함수는 와이드 문자열(`_wstr`)을 입력으로 받아 일반 문자열로 변환합니다. 
//! `wcslen`을 사용하여 와이드 문자열의 길이를 계산한 후 `string_from_wide2`를 호출하여 와이드 문자열을 일반 문자열로 변환합니다.
//! @param _wstr 변환할 와이드 문자열입니다.
//! @return 변환된 일반 문자열입니다.
static inline string string_from_wide(u16* _wstr) {
  usize wstr_len = wcslen(_wstr);
  return string_from_wide2(_wstr, ((int)(wstr_len)));
}

u16* string_to_wide(string s);

//! @brief 형식 문자열을 사용하여 문자열을 생성하는 함수입니다.
//! @details 이 함수는 형식 문자열(`format`)과 가변 인자를 사용하여 문자열을 생성하고 반환합니다. 
//! 문자열의 길이는 `vsnprintf` 함수를 사용하여 계산하며, 문자열 메모리는 `jmalloc` 함수를 사용하여 할당합니다.
//! 문자열의 내용은 `vsnprintf` 함수를 사용하여 형식 문자열과 가변 인자를 사용하여 생성합니다.
//! `vsnprintf` 함수가 실패한 경우, 에러 메시지를 출력하고 프로그램을 종료합니다.
//! @param format 형식 문자열입니다.
//! @return 생성된 문자열입니다.
string format_string(string format, ...);

//! @brief 와이드 문자열을 일반 문자열로 변환하는 매크로입니다.
//! @details 이 매크로는 와이드 문자열 s를 입력으로 받아, string_from_wide 함수를 호출하여 일반 문자열로 변환합니다.
//! @param s 변환할 와이드 문자열입니다.
//! @return 변환된 일반 문자열을 반환합니다.
#define _SLITW(s) string_from_wide(L##s)

//! @brief 주어진 옵션이 우크라이나어인지 확인하는 매크로입니다.
//! 항상 `false`를 반환합니다.
//! @param x 언어 설정을 포함하는 구조체입니다.!!
#define IS_UKRANIAN(x) false
//! @brief 주어진 옵션이 한국어인지 확인하는 매크로입니다.
//! 항상 `false`를 반환합니다.
//! @param x 언어 설정을 포함하는 구조체입니다.
#define IS_KOREAN(x) false

#define JAEYEONG_USAGE "jayeong [OPTIONS] INPUT"
#define _S_JAEYEONG "JaeyeongScript"
#define _S_JAEYEONG_USAGE "Usage: " JAEYEONG_USAGE
#define _S_JAEYEONG_HELP_VERBOSE "Use verbose output"
#define _S_JAEYEONG_HELP_VERSION "Print version info and exit"
#define _S_JAEYEONG_HELP_OUT "Write output to <filename>"
#define _S_JAEYEONG_HELP_EDITION "Specifies the compiler version to use when compiling the code. Specifies the compiler version to use when compiling. Does not affect the behavior of this option compiler on this version of the compiler."
#define _S_JAEYEONG_HELP_ENGLISH "Change the compiler's display language to English (default)."
#define _S_JAEYEONG_HELP_UKRAINIAN "Change the compiler's display language to Ukrainian."
#define _S_JAEYEONG_HELP_KOREAN "Change the compiler's display language to Korean."

#ifndef JAYEONG_NO_UKRANIAN
#undef IS_UKRANIAN
//! @brief 주어진 옵션이 우크라이나어인지 확인하는 매크로입니다.
//! @details 이 매크로는 `x.language`가 `Ukrainian`인지 확인하여 그 결과를 반환합니다.
//! @param x 언어 설정을 포함하는 구조체입니다.
#define IS_UKRANIAN(x) ((x.language) == Ukrainian)
#define _S_JAEYEONG_UA _S_JAEYEONG
#define _S_JAEYEONG_USAGE_UA "Використання: " JAEYEONG_USAGE
#define _S_JAEYEONG_HELP_VERBOSE_UA "Використовувати розширений вивід"
#define _S_JAEYEONG_HELP_VERSION_UA "Вивести інформацію про версію та вийти"
#define _S_JAEYEONG_HELP_OUT_UA "Записати результат у <filename>"
#define _S_JAEYEONG_HELP_EDITION_UA "Вказує версію компілятора, яку буде використано під час компіляції коду. Вказує версію компілятора для використання під час компіляції. Не впливає на поведінку цього параметра компілятора на цій версії компілятора."
#define _S_JAEYEONG_HELP_ENGLISH_UA "Змінити мову відображення компілятора на англійську (за замовчуванням)."
#define _S_JAEYEONG_HELP_UKRAINIAN_UA "Змінити мову відображення компілятора на українську."
#define _S_JAEYEONG_HELP_KOREAN_UA "Змінити мову відображення компілятора на корейську."
#endif /* JAYEONG_NO_UKRANIAN */

#ifndef JAEYEONG_NO_KOREAN
#undef IS_KOREAN
//! @brief 주어진 옵션이 한국어인지 확인하는 매크로입니다.
//! @details 이 매크로는 `x.language`가 `Korean`인지 확인하여 그 결과를 반환합니다.
//! @param x 언어 설정을 포함하는 구조체입니다.
#define IS_KOREAN(x) ((x.language) == Korean)
#define _S_JAEYEONG_KR _S_JAEYEONG
#define _S_JAEYEONG_USAGE_KR "사용법: " JAEYEONG_USAGE
#define _S_JAEYEONG_HELP_VERBOSE_KR "자세한 출력을 사용합니다."
#define _S_JAEYEONG_HELP_VERSION_KR "버전 정보를 출력하고 종료합니다."
#define _S_JAEYEONG_HELP_OUT_KR "결과를 <filename>에 씁니다."
#define _S_JAEYEONG_HELP_EDITION_KR "컴파일러 버전을 지정하여 코드를 컴파일할 때 사용할 컴파일러 버전을 지정합니다. 다만, 이 버전의 컴파일러에서는 이 옵션은 컴파일러의 동작에 아무런 영향도 미치지 않습니다."
#define _S_JAEYEONG_HELP_ENGLISH_KR "컴파일러의 표시 언어를 영어로 변경합니다(기본값)."
#define _S_JAEYEONG_HELP_UKRAINIAN_KR "컴파일러의 표시 언어를 우크라이나어로 변경합니다."
#define _S_JAEYEONG_HELP_KOREAN_KR "컴파일러의 표시 언어를 한국어로 변경합니다."
#endif /* JAEYEONG_NO_KOREAN */

#endif /* __JAEYEONG_STRINGS_H__ */