#include <stdio.h>
#include <stdlib.h>
#include "jaeyeong.h"

lexer* new_lexer(string source, string path) {
  lexer* lex = (lexer*)jcalloc(sizeof(lexer));
  lex->pos = 0;
  lex->line = 0;
  lex->last_nl_pos = 0;
  lex->line_nr = 0;
  lex->source = source;
  lex->inside_string = false;
  lex->tokens = __new_array(0, 1, sizeof(token));
  lex->error_details = __new_array(0, 1, sizeof(string));
  lex->pref = _new_preferences();
  lex->file_path = path;
  lex->nr_lines = 0;
  return lex;
}

void free_lexer(lexer* lex) {
  if (lex->pos == -98761234) {
    __panic(format_string(LANG(JAEYEONG_ERR_DOUBLE_FREE/*, options.language*/), (char*)_SLIT("lexer").str));
    UNREACHABLE();
  }
  lex->pos = -98761234;
  array_free(&lex->tokens);
  array_free(&lex->error_details);
  jfree(lex);
}

int lex_current_column(lexer* lex) {
  int _t1 = (int)(lex->pos - lex->last_nl_pos);
  return _t1;
}

tokpos lex_current_pos(lexer* lex) {
  tokpos _t1 = ((tokpos){.len = 0,.line_nr = lex->line_nr,.pos = lex->pos,.col = (int)(lex_current_column(lex) - 1),.last_line = 0,});
  return _t1;
}

void lexer_error_with_pos(lexer* lex, string msg, tokpos pos) {
  string details = _SLIT("");
  if (lex->error_details.len > 0) {
    details = string__plus(_SLIT("\n"), Array_string_join(lex->error_details, _SLIT("\n")));
    lex->error_details = __new_array_with_default(0, 0, sizeof(string), 0);
  }

  if (lex->pref->output_mode == PREF_OUTPUTMODE_STDOUT && !lex->pref->check_only) {
    CompilerMessage err = ((CompilerMessage){.message = msg,.details = details,.file_path = lex->file_path,.pos = pos,.reporter = 0,});
    string ferror = format_err(_SLIT("error:"), err.message, err.file_path, err.pos);
    eprintln(ferror);
    if (err.details.len > 0)
      eprintln(string__plus(bold(_SLIT("Details: ")), util_color(_SLIT("details"), err.details)));
    exit(0);
  }
}

void lexer_error(lexer* lex, string msg) {
  lexer_error_with_pos(lex, msg, lex_current_pos(lex));
}

string lexer_numlit(lexer* lex, int start, int end) {
  u8* txt = lex->source.str;
  u8* b = malloc_noscan((int)((int)(end - start) + 1));
  int i_no_sep = 0;
  for (int i = start; i < end; ++i) {
    if (txt[i] != '_') {
      b[i_no_sep] = txt[i];
      i_no_sep++;
    }
  }
  b[i_no_sep] = 0;
  string _t2 = ((string){.str = b, .len = i_no_sep, .is_lit = 0});
  return _t2;
}

string lexer_ident_bin_number(lexer* lex) {
  // bool wrong = false;
  size_t start_pos = (size_t)lex->pos;
  lex->pos += 2;
  if (lex->source.str[lex->pos] == '_') { __panic(LANG(JAEYEONG_ERR_BIN_WRONG_START)); }
  for (;;) {
    if (!((size_t)lex->pos < lex->source.len)) break;
    u8 c = lex->source.str[lex->pos];
    if (lex->source.str[lex->pos] == '_' && lex->source.str[lex->pos+1] == '_') { __panic(_SLIT("cannot use `_` consecutively")); }
    if (!(c == '0' || c == '1' || c == '_')) break;
    lex->pos++;
  }
  string number = lexer_numlit(lex, start_pos, lex->pos);
  return number;
}

string lexer_ident_hex_number(lexer* lex) {
  size_t start_pos = (size_t)lex->pos;
  if ((lex->pos + 2) >= (int)lex->source.len) return _SLIT("0x");
  lex->pos += 2;
  if ((lex->pos < (int)lex->source.len) && (lex->source.str[lex->pos] == '_')) lexer_error(lex, LANG(JAEYEONG_ERR_HEX_WRONG_START));
  for(;;) {
    if (!((size_t)lex->pos < lex->source.len)) break;
    u8 c = lex->source.str[lex->pos];
    if (lex->source.str[lex->pos] == '_' && lex->source.str[lex->pos+1] == '_') { __panic(_SLIT("cannot use `_` consecutively")); }
    if (!((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F') || c == '_')) break;
    lex->pos++;
  }
  string number = lexer_numlit(lex, start_pos, lex->pos);
  println(number);
  return number;
}

string lexer_ident_dec_number(lexer* lex) {
  size_t start_pos = (size_t)lex->pos;
  if (lex->source.str[lex->pos] == '_') lexer_error(lex, LANG(JAEYEONG_ERR_DEC_WRONG_START));
  for (;;) {
    if (!((size_t)lex->pos < lex->source.len)) break;
    u8 c = lex->source.str[lex->pos];
    if (lex->source.str[lex->pos] == '_' && lex->source.str[lex->pos+1] == '_') { __panic(_SLIT("cannot use `_` consecutively")); }
    if (!((c >= '0' && c <= '9') || (c == '_'))) break;
    lex->pos++;
  }
  string number = lexer_numlit(lex, start_pos, lex->pos);
  println(number);
  return number;
}

void lex_inc_line_number(lexer* l) {
  l->last_nl_pos = (int)(l->source.len - 1);
  if (l->last_nl_pos > l->pos)
    l->last_nl_pos = l->pos;
  if (l->is_crlf) 
    l->last_nl_pos++;
  l->line_nr++;
  if (l->line_nr > l->nr_lines) 
    l->nr_lines = l->line_nr;
}

#define lex_b_cr 13
#define lex_b_lf 10

void lex_skip_whitespace(lexer* lex) {
  for (;;) {
    if (!(lex->pos < (int)lex->source.len)) break;
    u8 c = lex->source.str[lex->pos];
    if (c == 9) {
      lex->pos++;
      continue;
    }
    if (!(c == 32 || (c > 8 && c < 14) || c == 0x85 || c == 0xa0)) return;
    bool c_is_nl = c == lex_b_cr || c == lex_b_lf;
    if (c_is_nl && false/*lex->is_vh*/) return;
    if ((int)(lex->pos + 1) < (int)lex->source.len && c == lex_b_cr && lex->source.str[ (int)(lex->pos + 1)] == lex_b_lf) lex->is_crlf = true;
    if (c_is_nl && !(lex->pos > 0 && lex->source.str[ (int)(lex->pos - 1)] == lex_b_cr && c == lex_b_lf)) lex_inc_line_number(lex);
    lex->pos++;
  }
}

#define IS_NAME_CHAR(c) ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
#define IS_FUNC_CHAR(c) ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' || (c >= '0' && c <= '9'))

u8 lexer_look_ahead(lexer* lex, int n) {
  return ((int)(lex->pos + n) < (int)lex->source.len) ? (u8)lex->source.str[ (int)(lex->pos + n)] : (u8)'\0';
}

void lexer_scan_all(lexer* lex) {
  for (;;) {
    if (!((size_t)lex->pos < lex->source.len)) break;
    if (lex->source.str[lex->pos] == ' ' || lex->source.str[lex->pos] == '\t') {
      lex->pos++;
      continue;
    }
    lex_skip_whitespace(lex);
    u8 c = lex->source.str[lex->pos];
    u8 c1 = lexer_look_ahead(lex, 1);
    if (lex->source.str[lex->pos] == '0') {
      if (lex->source.str[lex->pos+1] == 'x') {
        string number = lexer_ident_hex_number(lex);
        continue;
      }
      if (lex->source.str[lex->pos+1] == 'b') {
        string number = lexer_ident_bin_number(lex);
        continue;
      }
    } else if (isdigit(lex->source.str[lex->pos])) {
      string number = lexer_ident_dec_number(lex);
      continue;
    }
  }
}