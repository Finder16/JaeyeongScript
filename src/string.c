#include <stdio.h>
#include <stdlib.h>
#include "jaeyeong.h"

extern void ArrayFlags_set(ArrayFlags *e, ArrayFlags flag);
extern void strings__Builder_write_string(strings__Builder* b, string s);
extern i64 _const_min_i64;
const string _const_digit_pairs = _SLIT("00102030405060708090011121314151617181910212223242526272829203132333435363738393041424344454647484940515253545556575859506162636465666768696071727374757677787970818283848586878889809192939495969798999");
extern const u32 _const_strconv__single_minus_zero;
extern const u32 _const_strconv__single_plus_zero;

string make_empty_string() { return _SLIT0; }

string wchar_to_string(wchar_t* wstr) {
	return string_from_wide(wstr);
	// size_t len = wcslen(wstr);
  // string new_string = ((string){.str = jmalloc((int)(len + 1)), .len = len});
  // new_string.str = (wchar_t*)jmalloc((len + 1) * sizeof(wchar_t));
  // if(new_string.str == NULL) {
	// 	__panic(_SLIT("Memory allocation failed\n"));
	// 	UNREACHABLE();
	// }
  // for(size_t i = 0; i < len; i++) 
	// 	new_string.str[i] = wstr[i];
  // new_string.str[len] = L'\0';  // Null-terminated
  // new_string.len = len;
  // return new_string;
}

strings__Builder strings__new_builder(int initial_size) {
	strings__Builder res = ((__new_array_with_default(0, initial_size, sizeof(char), 0)));
	ArrayFlags_set(&res.flags, ArrayFlags__noslices);
	return res;
}

string string__plus(string s, string a) {
  size_t new_len = (size_t)(a.len + s.len);
  string res = ((string){.str = jmalloc((new_len + 1) * sizeof(char)), .len = new_len});
  memcpy(res.str, s.str, s.len * sizeof(char));
  memcpy(res.str + s.len, a.str, a.len * sizeof(char));
  res.str[new_len] = '\0';
  return res;
}

string string_with_len(u8* bp, int len) {
	return ((string){.str = bp, .len = len, .is_lit = 0});
}

string u8_string_with_len(u8* bp, int len) {
	return ((string){.str = bp, .len = len, .is_lit = 0});
}

string strings__Builder_str(strings__Builder* b) {
	array_push((array*)b, _MOV((u8[]){ ((u8)(0)) }));
	u8* bcopy = ((u8*)(memdup_noscan(b->data, b->len)));
	string s = u8_string_with_len(bcopy, (int)(b->len - 1));
	array_trim(b, 0);
	return s;
}

void strings__Builder_free(strings__Builder* b) {
	if (b->data != 0) {
		jfree(b->data);
		b->data = ((void*)0);
	}
}

string string_to_upper(string s) {
	{ // Unsafe block
		u8* b = malloc_noscan((int)(s.len + 1));
		for (size_t i = 0; i < s.len; ++i) {
			if (s.str[i] >= 'a' && s.str[i] <= 'z') {
				b[i] = (u8)(s.str[i] - 32);
			} else {
				b[i] = s.str[i];
			}
		}
		b[s.len] = 0;
		return tos(b, s.len);
	}
	return (string){.str=(byte*)"", .is_lit=1};
}

string string_clone(string a) {
	if (a.len == 0) return _SLIT("");
	string b = ((string){.str = jmalloc((int)(a.len + 1)), .len = a.len});
	memcpy(b.str, a.str, a.len);
	b.str[a.len] = 0;
	return b;
}

string tos(u8* s, int len) {
	if (s == 0) {
		// __panic(_SLIT("tos(): nil string"));
		__panic(_SLITW("tos(): порожній рядок"));
		UNREACHABLE();
	}
	return ((string){.str = s, .len = len});
}

string str_intp(int data_len, StrIntpData* input_base) {
  string result = _SLIT0;
  for (int i = 0; i < data_len; i++) {
    StrIntpData data = input_base[i];
    bool uppercase  = data.fmt & StrIntFlag__UpperCase;
    StrIntpType type = _CLRFlag(data.fmt);
    string str = data.str;
		switch (type) {
			case StrIntpType__si_no_str:
				break;
			case StrIntpType__si_u8:
				str = string__plus(str, strconv__format_uint((u64)data.d.d_u8, 10));
				break;
			case StrIntpType__si_u16:
				str = string__plus(str, strconv__format_uint((u64)data.d.d_u16, 10));
				break;
			case StrIntpType__si_u32:
				str = string__plus(str, strconv__format_uint((u64)data.d.d_u32, 10));
				break;
			case StrIntpType__si_u64:
				str = string__plus(str, strconv__format_uint((u64)data.d.d_u64, 10));
				break;
			case StrIntpType__si_i8:
				str = string__plus(str, strconv__format_int((i64)data.d.d_i8, 10));
				break;
			case StrIntpType__si_i16:
				str = string__plus(str, strconv__format_int((i64)data.d.d_i16, 10));
				break;
			case StrIntpType__si_i32:
				str = string__plus(str, strconv__format_int((i64)data.d.d_i32, 10));
				break;
			case StrIntpType__si_i64:
				str = string__plus(str, strconv__format_int((i64)data.d.d_i64, 10));
				break;
			case StrIntpType__si_s:
				str = (str.len < 1)?data.d.d_s:string__plus(str, data.d.d_s);
				break;
			default:
				break;
		}
		if (uppercase) str = string_to_upper(str);
		result = (result.len == 0)?str:string__plus(result, str);
  }
	if (result.str != NULL) result.str[result.len] = L'\0';
  return result;
}

void string_free(string* s) {
	if (s->is_lit == -98761234) {
		u8* double_free_msg = ((u8*)("double string.free() detected\n"));
		int double_free_msg_len = strlen((char*)double_free_msg);
		_write_buf_to_fd(1, double_free_msg, double_free_msg_len);
		return;
	}
	if (s->is_lit == 1 || s->str == 0) return;
	jfree(s->str);
	s->str = ((void*)0);
	s->is_lit = -98761234;
}

bool endsWithW(const wchar_t *wstr, const wchar_t *wsuffix) {
    if (!wstr || !wsuffix)
        return false;
    size_t lenwstr = wcslen(wstr);
    size_t lenwsuffix = wcslen(wsuffix);
    if (lenwsuffix >  lenwstr)
        return false;
    return wcsncmp(wstr + lenwstr - lenwsuffix, wsuffix, lenwsuffix) == 0;
}