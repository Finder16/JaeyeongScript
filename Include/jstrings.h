#ifndef __JAEYEONG_STRINGS_H__
#define __JAEYEONG_STRINGS_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <windows.h>
#include "apua.h"
#include "jarray.h"
#include "jmem.h"

struct string {
  byte* str;
  size_t len;
	int is_lit;
};

union StrIntpMem {
	u32 d_c;
	u8 d_u8;
	i8 d_i8;
	u16 d_u16;
	i16 d_i16;
	u32 d_u32;
	int d_i32;
	u64 d_u64;
	i64 d_i64;
	f32 d_f32;
	f64 d_f64;
	string d_s;
	string d_r;
	void* d_p;
	void* d_vp;
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

string wchar_to_string(wchar_t* wstr);
// string u8_ascii_str(_wU8 b);
string string__plus(string s, string a);
string string_with_len(u8* bp, int len);
strings__Builder strings__new_builder(int initial_size);
string strings__Builder_str(strings__Builder* b);
void strings__Builder_free(strings__Builder* b);
string string_clone(string a);
string tos(u8* s, int len);
void string_free(string* s);
bool endsWithW(const wchar_t *wstr, const wchar_t *wsuffix);
#define _SLIT0 (string){.str=(byte*)(""), .len=0, .is_lit=1}
#define _SLIT(s) ((string){.str=(byte*)("" s), .len=(sizeof(s)-1), .is_lit=1})
#define _SLEN(s, n) ((string){.str=(byte*)("" s), .len=n, .is_lit=1})

void StrIntpData_process_str_intp_data(StrIntpData* data, strings__Builder* sb);
string str_intp(int data_len, StrIntpData* input_base);

inline u8 strings__Builder_byte_at(strings__Builder* b, int n) { return (*(u8*)array_get(*(((Array_u8*)(b))), n)); }

inline void strings__Builder_write_string(strings__Builder* b, string s) {
	if (s.len == 0) return;
	array_push_many(b, s.str, s.len);
}

inline void strings__Builder_writeln_string(strings__Builder* b, string s) {
	strings__Builder_write_string(b, s);
	strings__Builder_write_string(b, _SLIT("\n"));
}

static inline string string_from_wide2(u16* _wstr, int len) {
	int num_chars = WideCharToMultiByte(65001, 0U, _wstr, len, 0, 0, 0, 0);
	u8* str_to = malloc_noscan((int)(num_chars + 1));
	if (str_to != 0) {
		WideCharToMultiByte(65001, 0U, _wstr, len, ((char*)(str_to)), num_chars, 0, 0);
		memset(str_to + num_chars, 0, 1);
	}
	return  ((string){.str = str_to, .len = strlen((char*)str_to)});
}

static inline string string_from_wide(u16* _wstr) {
	usize wstr_len = wcslen(_wstr);
	return string_from_wide2(_wstr, ((int)(wstr_len)));
}

#define _SLITW(s) string_from_wide(L##s)

#define _S_JAEYEONG "JaeyeongScript"
#define _S_JAEYEONG_USAGE "Usage: jayeong [OPTIONS] INPUT"
#define _S_JAEYEONG_HELP_VERBOSE "Use verbose output"
#define _S_JAEYEONG_HELP_VERSION "Print version info and exit"
#define _S_JAEYEONG_HELP_OUT "Write output to <filename>"
#define _S_JAEYEONG_HELP_EDITION "Specifies the compiler version to use when compiling the code. Specifies the compiler version to use when compiling. Does not affect the behavior of this option compiler on this version of the compiler."
#define _S_JAEYEONG_HELP_ENGLISH "Change the compiler's display language to English (default)."
#define _S_JAEYEONG_HELP_UKRAINIAN "Change the compiler's display language to Ukrainian."
#define _S_JAEYEONG_HELP_KOREAN "Change the compiler's display language to Korean."

#ifndef JAYEONG_NO_UKRANIAN
#define _S_JAEYEONG_UA _S_JAEYEONG
#define _S_JAEYEONG_USAGE_UA "Використання: jayeong [OPTIONS] INPUT"
#define _S_JAEYEONG_HELP_VERBOSE_UA "Використовувати розширений вивід"
#define _S_JAEYEONG_HELP_VERSION_UA "Вивести інформацію про версію та вийти"
#define _S_JAEYEONG_HELP_OUT_UA "Записати результат у <filename>"
#define _S_JAEYEONG_HELP_EDITION_UA "Вказує версію компілятора, яку буде використано під час компіляції коду. Вказує версію компілятора для використання під час компіляції. Не впливає на поведінку цього параметра компілятора на цій версії компілятора."
#define _S_JAEYEONG_HELP_ENGLISH_UA "Змінити мову відображення компілятора на англійську (за замовчуванням)."
#define _S_JAEYEONG_HELP_UKRAINIAN_UA "Змінити мову відображення компілятора на українську."
#define _S_JAEYEONG_HELP_KOREAN_UA "Змінити мову відображення компілятора на корейську."
#endif /* JAYEONG_NO_UKRANIAN */

#ifndef JAEYEONG_NO_KOREAN
#define _S_JAEYEONG_KR _S_JAEYEONG
#define _S_JAEYEONG_USAGE_KR "사용법: jayeong [OPTIONS] INPUT"
#define _S_JAEYEONG_HELP_VERBOSE_KR "자세한 출력을 사용합니다."
#define _S_JAEYEONG_HELP_VERSION_KR "버전 정보를 출력하고 종료합니다."
#define _S_JAEYEONG_HELP_OUT_KR "결과를 <filename>에 씁니다."
#define _S_JAEYEONG_HELP_EDITION_KR "컴파일러 버전을 지정하여 코드를 컴파일할 때 사용할 컴파일러 버전을 지정합니다. 다만, 이 버전의 컴파일러에서는 이 옵션은 컴파일러의 동작에 아무런 영향도 미치지 않습니다."
#define _S_JAEYEONG_HELP_ENGLISH_KR "컴파일러의 표시 언어를 영어로 변경합니다(기본값)."
#define _S_JAEYEONG_HELP_UKRAINIAN_KR "컴파일러의 표시 언어를 우크라이나어로 변경합니다."
#define _S_JAEYEONG_HELP_KOREAN_KR "컴파일러의 표시 언어를 한국어로 변경합니다."
#endif /* JAEYEONG_NO_KOREAN */

#endif /* __JAEYEONG_STRINGS_H__ */