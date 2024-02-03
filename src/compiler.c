#include <stdio.h>
#include <stdlib.h>
#include "jaeyeong.h"

#define _error_context_before 2
#define _error_context_after 2

int math_min_t_int(int a, int b);
int math_max_t_int(int a, int b);

inline int math_min_t_int(int a, int b) { return (int)(a < b ? (a) : (b)); }
inline int math_max_t_int(int a, int b) { return (int)(a > b ? (a) : (b)); }

string util_color(string kind, string msg) {
  return string_contains(kind, _SLIT("error")) ? red(msg) : (string_contains(kind, _SLIT("warning")) ? yellow(msg) : (string_contains(kind, _SLIT("details")) ? bright_blue(msg) : magenta(msg)));
}

Array_string source_file_context(string kind, string filepath, tokpos pos) {
  Array_string clines = __new_array_with_default(0, 0, sizeof(string), 0);
  Array_string source_lines = cached_file_to_sourcelines(filepath);
  if (source_lines.len == 0) return clines;
  int bline = math_max_t_int(0, (int)(pos.line_nr - _error_context_before));
  int aline = math_max_t_int(0, math_min_t_int((int)(source_lines.len - 1), (int)(pos.line_nr + _error_context_after)));
  string tab_spaces = _SLIT("    ");
  for (int iline = bline; iline <= aline; iline++) {
    string sline = (*(string*)array_get(source_lines, iline));
    int start_column = math_max_t_int(0, math_min_t_int(pos.col, sline.len));
    int end_column = math_max_t_int(0, math_min_t_int((int)(pos.col + math_max_t_int(0, pos.len)), sline.len));
    string cline = (iline == pos.line_nr ? (string__plus(string__plus(string_substr(sline, 0, start_column), util_color(kind, string_substr(sline, start_column, end_column))), string_substr(sline, end_column, 2147483647))) : (sline));
    array_push((array*)&clines, _MOV((string[]){ string_clone(string__plus( str_intp(2, _MOV((StrIntpData[]){/*{_SLIT0, note: (0xafe27 &int)0x7, {.d_i32 = (int)(iline + 1)}}*/{_SLIT0, /*0xafe27 &int*/0x10, {.d_s = format_string(_SLIT("%5d"), (int)(iline + 1))}}, {_SLIT(" | "), 0, { .d_c = 0 }}})), string_replace(cline, _SLIT("\t"), tab_spaces))) }));
    if (iline == pos.line_nr) {
      strings__Builder pointerline_builder = strings__new_builder(sline.len);
      for (int i = 0; i < start_column; ) {
        if (u8_is_space(string_at(sline, i))) {
          array_push((array*)&pointerline_builder, _MOV((u8[]){ string_at(sline, i) }));
          i++;
        } else {
          int char_len = (int_literal)(((((0xe5000000 >> (((((string_at(sline, i) >> 3)) & 0x1e)))) & 3)) + 1));
          string spaces = string_repeat(_SLIT(" "), utf8_str_visible_length(string_substr(sline, i, (int)(i + char_len))));
          strings__Builder_write_string(&pointerline_builder, spaces);
          i += char_len;
        }
      }
      int underline_len = utf8_str_visible_length(string_substr(sline, start_column, end_column));
      string underline = (underline_len > 1 ? (string_repeat(_SLIT("~"), underline_len)) : (_SLIT("^")));
      strings__Builder_write_string(&pointerline_builder, bold(util_color(kind, underline)));
      array_push((array*)&clines, _MOV((string[]){ string_clone(string__plus(_SLIT("      | "), string_replace(strings__Builder_str(&pointerline_builder), _SLIT("\t"), tab_spaces))) }));
    }
  }
  return clines;
}

string format_err(string kind, string omsg, string filepath, tokpos pos) {
  string emsg = string_replace(omsg, _SLIT("main."), _SLIT(""));
  string path = filepath;
  string position = (filepath.len > 0 ? ( str_intp(4, _MOV((StrIntpData[]){{_SLIT0, 0x10, {.d_s = path}}, {_SLIT(":"), 0x7, {.d_i32 = (int)(pos.line_nr + 1)}}, {_SLIT(":"), 0x7, {.d_i32 = (1 > (int)(pos.col + 1) ? (1) : ((int)(pos.col + 1))) }}, {_SLIT(":"), 0, { .d_c = 0 }}}))) : (_SLIT("")));
  string scontext = Array_string_join(source_file_context(kind, filepath, pos), _SLIT("\n"));
  string final_position = bold(position);
  string final_kind = bold(util_color(kind, kind));
  string final_msg = emsg;
  string final_context = (scontext.len > 0 ? ( str_intp(2, _MOV((StrIntpData[]){{_SLIT("\n"), /*115 &string*/0x10, {.d_s = scontext}}, {_SLIT0, 0, { .d_c = 0 }}}))) : (_SLIT("")));
  string _t1 = string_trim( str_intp(5, _MOV((StrIntpData[]){{_SLIT0, /*115 &string*/0x10, {.d_s = final_position}}, {_SLIT(" "), /*115 &string*/0x10, {.d_s = final_kind}}, {_SLIT(" "), /*115 &string*/0x10, {.d_s = final_msg}}, {_SLIT0, /*115 &string*/0x10, {.d_s = final_context}}, {_SLIT0, 0, { .d_c = 0 }}})), _SLIT(" \n\t\v\f\r"));
  return _t1;
}