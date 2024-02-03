#include "jaeyeong.h"

extern LinesCache*  lines_cache;
extern const i32 _const_max_int;

typedef struct {
  Map_String_String sources;
} SourceCache;

ResultString util_read_file(string path) {
  SourceCache* cache = ((SourceCache*)(((void*)0)));
  if (cache == ((void*)0))
    cache = ((SourceCache*)memdup(&(SourceCache){.sources = new_map(sizeof(string), sizeof(string), &map_hash_string, &map_eq_string, &map_clone_string, &map_free_string),}, sizeof(SourceCache)));
  if (path.len == 0) {
    map_free(&cache->sources);
    free(cache);
    cache = ((SourceCache*)(((void*)0)));
    return (ResultString)Err(__error(_SLIT("memory source file cache cleared")));
  }
  string* _t4 = (string*)(map_get_check(ADDR(map, cache->sources), &(string[]){path}));
  OptionString _t3 = {0};
  if (_t4) {
    *((string*)&_t3.value) = *((string*)_t4);
  } else {
    _t3.state = 2; _t3.error = __error(_SLIT("array index out of range"));
  }
  if (_t3.state == 0) {
    string res = (*(string*)_t3.value);
    ResultString _t6 = Ok(&(string[]) { res }, sizeof(string));
    return _t6;
  }
  ResultString _t8 = os_readfile(path);
  if (_t8.is_err) {
    // ErrorInterface err = _t8.err;
    return Err(__error(str_intp(2, _MOV((StrIntpData[]){{_SLIT("failed to open "), /*115 &string*/0x10, {.d_s = path}}, {_SLIT0, 0, { .d_c = 0 }}}))));
  }
  string raw_text = (*(string*)_t8.data);
  string res = util_skip_bom(raw_text);
  map_set(&cache->sources, &(string[]){path}, &(string[]) { res });
  ResultString _t10 = Ok(&(string[]) { res }, sizeof(string));
  return _t10;
}

string string_substr(string s, int start, int _end) {
  int end = (_end == _const_max_int ? (s.len) : (_end));
  #if !defined(CUSTOM_DEFINE_no_bounds_checking)
  {
    if (start > end || start > (int)s.len || end > (int)s.len || start < 0 || end < 0) {
      __panic( str_intp(4, _MOV((StrIntpData[]){{_SLIT("substr("), /*100 &int*/0x7, {.d_i32 = start}}, {_SLIT(", "), /*100 &int*/0x7, {.d_i32 = end}}, {_SLIT(") out of bounds (len="), /*100 &int*/0x7, {.d_i32 = s.len}}, {_SLIT(")"), 0, { .d_c = 0 }}})));
      UNREACHABLE();
    }
  }
  #endif
  int len = (int)(end - start);
  if (len == (int)s.len) {
    return string_clone(s);
  }
  string res = ((string){.str = malloc_noscan((int)(len + 1)), .len = len});
  { // Unsafe block
    memcpy(res.str, s.str + start, len);
    res.str[len] = 0;
  }
  return res;
}

Array_string string_split_into_lines(string s) {
  Array_string res = __new_array_with_default(0, 0, sizeof(string), 0);
  if (s.len == 0) {
    return res;
  }
  rune cr = '\r';
  rune lf = '\n';
  int line_start = 0;
  for (int i = 0; i < (int)s.len; i++) {
    if (line_start <= i) {
      if (s.str[ i] == lf) {
        array_push((array*)&res, _MOV((string[]){ (line_start == i ? (_SLIT("")) : (string_substr(s, line_start, i))) }));
        line_start = (int)(i + 1);
      } else if (s.str[ i] == cr) {
        array_push((array*)&res, _MOV((string[]){ (line_start == i ? (_SLIT("")) : (string_substr(s, line_start, i))) }));
        if (((int)(i + 1)) < (int)s.len && s.str[ (int)(i + 1)] == lf) {
          line_start = (int)(i + 2);
        } else {
          line_start = (int)(i + 1);
        }
      }
    }
  }
  if (line_start < (int)s.len) array_push((array*)&res, _MOV((string[]){ string_substr(s, line_start, 2147483647) }));
  return res;
}

Array_string cached_file_to_sourcelines(string path) {
  Array_string* _t2 = (Array_string*)(map_get_check(ADDR(map, lines_cache->lines), &(string[]){path}));
  OptionArrayString t3 = none();
  if (_t2 != _jNULL) {
    t3 = some((void*)_t2, sizeof(Array_string));
  } else  t3.state=2;t3.error = __error(_SLIT("array index out of range"));
  if (t3.state == 0) return (Array_string)(*(Array_string*)t3.value);
  ResultString _t4 = util_read_file(path);
  if (_t4.is_err) {
    // ErrorInterface err = _t4.err;
    *(string*) _t4.data = _SLIT("");
  }
  string source =  (*((string*)_t4.data));
  Array_string lines = string_split_into_lines(source);
  (*(Array_string*)map_get_and_set((map*)&lines_cache->lines, &(string[]){path}, &(Array_string[]){ __new_array(0, 0, sizeof(string)) })) = lines;
  return lines;
}

string util_skip_bom(string file_content) {
  string raw_text = file_content;
  if (raw_text.len >= 3) {
    u8* c_text = raw_text.str;
    if (c_text[0] == 0xEF && c_text[1] == 0xBB && c_text[2] == 0xBF) {
      int offset_from_begin = 3;
      raw_text = tos((void*)&/*qq*/c_text[offset_from_begin], (int)(strlen(((char*)(c_text))) - offset_from_begin));
    }
  }
  return raw_text;
}