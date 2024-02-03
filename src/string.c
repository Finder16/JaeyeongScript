#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "jaeyeong.h"

extern void ArrayFlags_set(ArrayFlags *e, ArrayFlags flag);
extern void strings__Builder_write_string(strings__Builder* b, string s);
extern i64 _const_min_i64;
const string _const_digit_pairs = _SLIT("00102030405060708090011121314151617181910212223242526272829203132333435363738393041424344454647484940515253545556575859506162636465666768696071727374757677787970818283848586878889809192939495969798999");
extern const u32 _const_strconv__single_minus_zero;
extern const u32 _const_strconv__single_plus_zero;

string make_empty_string() { return _SLIT0; }

string wchar_to_string(const wchar_t* wstr) {
  return string_from_wide((u16*)wstr);
}

strings__Builder strings__new_builder(int initial_size) {
  strings__Builder res = ((__new_array_with_default(0, initial_size, sizeof(char), 0)));
  ArrayFlags_set(&res.flags, ArrayFlags__noslices);
  return res;
}

bool string_contains_u8(string s, u8 x) {
  for (int _t1 = 0; _t1 < (int)s.len; ++_t1) {
    u8 c = s.str[_t1];
    if (x == c) {
      return true;
    }
  }
  return false;
}

int string_index_kmp(string s, string p) {
  bool string_index_kmp_defer_0 = false;
  Array_int prefix;
  if (p.len > s.len) {
    return -1;
  }
  prefix = __new_array_with_default(p.len, 0, sizeof(int), 0);
  string_index_kmp_defer_0 = true;
  int j = 0;
  for (int i = 1; i < (int)p.len; i++) {
    for (;;) {
      if (!(p.str[j] != p.str[i] && j > 0)) break;
      j = ((int*)prefix.data)[(int)(j - 1)];
    }
    if (p.str[j] == p.str[i]) {
      j++;
    }
    ((int*)prefix.data)[i] = j;
  }
  j = 0;
  for (int i = 0; i < (int)s.len; ++i) {
    for (;;) {
      if (!(p.str[j] != s.str[i] && j > 0)) break;
      j = ((int*)prefix.data)[(int)(j - 1)];
    }
    if (p.str[j] == s.str[i]) {
      j++;
    }
    if (j == (int)p.len) {
      int _t2 = (int)((int)(i - p.len) + 1);
        // Defer begin
        if (string_index_kmp_defer_0) {
          array_free(&prefix);
        }
        // Defer end
      return _t2;
    }
  }
  int _t3 = -1;
    // Defer begin
    if (string_index_kmp_defer_0) {
      array_free(&prefix);
    }
    // Defer end
  return _t3;
}

int string_index_(string s, string p) {
  if (p.len > s.len || p.len == 0) {
    return -1;
  }
  if (p.len > 2) {
    return string_index_kmp(s, p);
  }
  int i = 0;
  for (;;) {
    if (!(i < (int)s.len)) break;
    int j = 0;
    for (;;) {
      if (!(j < (int)p.len && s.str[(int)(i + j)] == p.str[j])) break;
      j++;
    }
    if (j == (int)p.len) {
      return i;
    }
    i++;
  }
  return -1;
}

bool string_contains(string s, string substr) {
  if (substr.len == 0) {
    return true;
  }
  if (substr.len == 1) {
    return string_contains_u8(s, substr.str[0]);
  }
  return string_index_(s, substr) != -1;
}

bool string_contains_any(string s, string chars) {
  for (int _t1 = 0; _t1 < (int)chars.len; ++_t1) {
    u8 c = chars.str[_t1];
    if (string_contains_u8(s, c)) {
      return true;
    }
  }
  return false;
}

bool string_contains_only(string s, string chars) {
  if (chars.len == 0) {
    return false;
  }
  for (int _t2 = 0; _t2 < (int)s.len; ++_t2) {
    u8 ch = s.str[_t2];
    int res = 0;
    for (int i = 0; i < (int)chars.len && res == 0; i++) {
      res += (int[]){(ch == chars.str[i])?1:0}[0];
    }
    if (res == 0) {
      return false;
    }
  }
  return true;
}

bool string_contains_any_substr(string s, Array_string substrs) {
  if (substrs.len == 0) {
    return true;
  }
  for (int _t2 = 0; _t2 < substrs.len; ++_t2) {
    string sub = ((string*)substrs.data)[_t2];
    if (string_contains(s, sub)) {
      return true;
    }
  }
  return false;
}

int string_index_after(string s, string p, int start) {
  if (p.len > s.len) {
    return -1;
  }
  int strt = start;
  if (start < 0) {
    strt = 0;
  }
  if (start >= (int)s.len) {
    return -1;
  }
  int i = strt;
  for (;;) {
    if (!(i < (int)s.len)) break;
    int j = 0;
    int ii = i;
    for (;;) {
      if (!(j < (int)p.len && s.str[ii] == p.str[j])) break;
      j++;
      ii++;
    }
    if (j == (int)p.len) {
      return i;
    }
    i++;
  }
  return -1;
}


string string_replace(string s, string rep, string with) {
  bool string_replace_defer_0 = false;
  Array_int idxs;
  if (s.len == 0 || rep.len == 0 || rep.len > s.len) return string_clone(s);
  if (!string_contains(s, rep)) return string_clone(s);
  idxs = __new_array_with_default(0, (int)(s.len / rep.len), sizeof(int), 0);
  string_replace_defer_0 = true;
  int idx = 0;
  for (;;) {
    idx = string_index_after(s, rep, idx);
    if (idx == -1) break;
    array_push((array*)&idxs, _MOV((int[]){ idx }));
    idx += rep.len;
  }
  if (idxs.len == 0) {
    string _t4 = string_clone(s);
    if (string_replace_defer_0) array_free(&idxs);
    return _t4;
  }
  int new_len = (int)(s.len + (int)(idxs.len * ((int)(with.len - rep.len))));
  u8* b = malloc_noscan((int)(new_len + 1));
  int b_i = 0;
  int s_idx = 0;
  for (int _t5 = 0; _t5 < idxs.len; ++_t5) {
    int rep_pos = ((int*)idxs.data)[_t5];
    for (int i = s_idx; i < rep_pos; ++i) {
      b[b_i] = s.str[ i];
      b_i++;
    }
    s_idx = (int)(rep_pos + rep.len);
    for (int i = 0; i < (int)with.len; ++i) {
      b[b_i] = with.str[ i];
      b_i++;
    }
  }
  if (s_idx < (int)s.len) {
    for (int i = s_idx; i < (int)s.len; ++i) {
      b[b_i] = s.str[ i];
      b_i++;
    }
  }
  b[new_len] = 0;
  string _t6 = tos(b, new_len);
  if (string_replace_defer_0) array_free(&idxs);
  return _t6;
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

string format_string(string format, ...) {
  va_list args;
  va_start(args, format);
  int len = vsnprintf(0, 0, (char*)format.str, args);
  va_end(args);
  if (len < 0) {
    __panic(_SLIT("format_string(): vsnprintf() failed"));
    UNREACHABLE();
  }
  string buf = ((string){.str = jmalloc((len + 1) * sizeof(char)), .len = len});
  va_start(args, format);
  vsnprintf((char*)buf.str, len + 1, (char*)format.str, args);
  va_end(args);
  return buf;
}

bool fast_string_eq(string a, string b) {
  if (a.len != b.len) return false;
  return memcmp(a.str, b.str, b.len) == 0;
}

u8 string_at(string s, int idx) {
  #if !defined(JAEYEONG_NO_BOUNDS_CHECKING)
  {
    if (idx < 0 || idx >= (int)s.len) {
      __panic(str_intp(3, _MOV((StrIntpData[]){{_SLIT("string index out of range: "), 0x7, {.d_i32 = idx}}, {_SLIT(" / "), 0x7, {.d_i32 = s.len}}, {_SLIT0, 0, { .d_c = 0 }}})));
      UNREACHABLE();
    }
  }
  #endif
  return s.str[idx];
}

string string_repeat(string s, int count) {
  if (count < 0) {
    __panic( str_intp(2, _MOV((StrIntpData[]){{_SLIT("string.repeat: count is negative: "), 0x7, {.d_i32 = count}}, {_SLIT0, 0, { .d_c = 0 }}})));
    UNREACHABLE();
  } else if (count == 0) {
    return _SLIT("");
  } else if (count == 1) return string_clone(s);
  u8* ret = malloc_noscan((int)((int)(s.len * count) + 1));
  for (int i = 0; i < count; ++i) 
    memcpy(ret + (int)(i * s.len), s.str, s.len);
  int new_len = (int)(s.len * count);
  ret[new_len] = 0;
  return ((string){.str = ret, .len = new_len, .is_lit = 0});
}

string string_trim(string s, string cutset) {
  if (s.len < 1 || cutset.len < 1) {
    return string_clone(s);
  }
  multi_return_int_int mr_41487 = string_trim_indexes(s, cutset);
  int left = mr_41487.arg0;
  int right = mr_41487.arg1;
  return string_substr(s, left, right);
}

multi_return_int_int string_trim_indexes(string s, string cutset) {
  int pos_left = 0;
  int pos_right = (int)(s.len - 1);
  bool cs_match = true;
  for (;;) {
    if (!(pos_left <= (int)s.len && pos_right >= -1 && cs_match)) break;
    cs_match = false;
    for (int _t1 = 0; _t1 < (int)cutset.len; ++_t1) {
      u8 cs = cutset.str[_t1];
      if (s.str[ pos_left] == cs) {
        pos_left++;
        cs_match = true;
        break;
      }
    }
    for (int _t2 = 0; _t2 < (int)cutset.len; ++_t2) {
      u8 cs = cutset.str[_t2];
      if (s.str[ pos_right] == cs) {
        pos_right--;
        cs_match = true;
        break;
      }
    }
    if (pos_left > pos_right) {
      return (multi_return_int_int){.arg0=0, .arg1=0};
    }
  }
  return (multi_return_int_int){.arg0=pos_left, .arg1=(int)(pos_right + 1)};
}

int utf8_str_visible_length(string s) {
  int l = 0;
  int ul = 1;
  for (int i = 0; i < (int)s.len; i += ul) {
    u8 c = s.str[i];
    ul = (int_literal)(((((0xe5000000 >> ((((s.str[i] >> 3)) & 0x1e)))) & 3)) + 1);
    if ((int)(i + ul) > (int)s.len) return l;
    l++;
    if (ul == 1) continue;

    if (ul == (2)) {
      u64 r = ((u64)((((((u16)(c)) << 8U)) | s.str[(int)(i + 1)])));
      if (r >= 0xcc80U && r < 0xcdb0U) l--;
    }
    else if (ul == (3)) {
      u64 r = ((u64)((((((u32)(c)) << 16U)) | (((((u32)(s.str[(int)(i + 1)])) << 8U)) | s.str[(int)(i + 2)]))));
      if ((r >= 0xe1aab0U && r <= 0xe1ac7fU) || (r >= 0xe1b780U && r <= 0xe1b87fU) || (r >= 0xe28390U && r <= 0xe2847fU) || (r >= 0xefb8a0U && r <= 0xefb8afU)) l--;
      else if ((r >= 0xe18480U && r <= 0xe1859fU) || (r >= 0xe2ba80U && r <= 0xe2bf95U) || (r >= 0xe38080U && r <= 0xe4b77fU) || (r >= 0xe4b880U && r <= 0xea807fU) || (r >= 0xeaa5a0U && r <= 0xeaa79fU) || (r >= 0xeab080U && r <= 0xed9eafU) || (r >= 0xefa480U && r <= 0xefac7fU) || (r >= 0xefb8b8U && r <= 0xefb9afU)) l++;
    }
    else if (ul == (4)) {
      u64 r = ((u64)((((((u32)(c)) << 24U)) | ((((((u32)(s.str[(int)(i + 1)])) << 16U)) | ((((u32)(s.str[(int)(i + 2)])) << 8U))) | s.str[(int)(i + 3)]))));
      if ((r >= 0x0f9f8880U && r <= 0xf09f8a8fU) || (r >= 0xf09f8c80U && r <= 0xf09f9c90U) || (r >= 0xf09fa490U && r <= 0xf09fa7afU) || (r >= 0xf0a08080U && r <= 0xf180807fU)) l++;
    }
    else {}
  }
  return l;
}

u16* string_to_wide(string s) {
  #if defined(_WIN32)
  {
    { // Unsafe block
      int num_chars = (MultiByteToWideChar(_const_cp_utf8, 0U, ((char*)(s.str)), s.len, 0, 0));
      u16* wstr = ((u16*)(malloc_noscan((int)(((int)(num_chars + 1)) * 2))));
      if (wstr != 0) {
        MultiByteToWideChar(_const_cp_utf8, 0U, ((char*)(s.str)), s.len, wstr, num_chars);
        memset(((u8*)(wstr)) + (int)(num_chars * 2), 0, 2);
      }
      return wstr;
    }
  }
  #else
    //! todo!(jaeyeong): implement
  #endif
  return 0;
}

void strings__Builder_write_ptr(strings__Builder* b, u8* ptr, int len) {
  if (len == 0) return;
  array_push_many(b, ptr, len);
}