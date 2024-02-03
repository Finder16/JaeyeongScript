#ifndef __JAEYEONG_LEX_H__
#define __JAEYEONG_LEX_H__
#include <stdbool.h>
#include "apua.h"
#include "jstrings.h"

struct lexer {
  int last_nl_pos, line_nr;
  int pos, line, nr_lines;
  string source, file_path;
  bool inside_string, is_crlf;
  Array_token tokens;
  Array_string error_details;
  Preferences* pref;
};

lexer* new_lexer(string source, string path);
void free_lexer(lexer* lex);
void lexer_scan_all(lexer* lex);
#endif