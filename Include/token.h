#ifndef __WOOJINC_INTERNAL_CORE_TOKEN_H__
#define __WOOJINC_INTERNAL_CORE_TOKEN_H__
#include "apua.h"

struct token {
  int lineno, col_offset, end_lineno, end_col_offset;
  const char *start, *end;
};

struct tokpos {
  int len, line_nr, pos, col, last_line;
};

void token_free(struct token *t);

#define ENDMARKER       0
#define NAME            ENDMARKER + 1
#define INTEGER         NAME + 1
#define FLOAT           INTEGER + 1
#define STRING          FLOAT + 1
#define TRUE_LIT        STRING + 1
#define FALSE_LIT       TRUE_LIT + 1
#define NEWLINE         FALSE_LIT + 1
#define LPAREN          NEWLINE + 1
#define RPAREN          LPAREN + 1
#define LSQB            RPAREN + 1
#define RSQB            LSQB + 1
#define LBRACE          RSQB + 1
#define RBRACE          LBRACE + 1
#define ARROW           RBRACE + 1
#define PERCENT         ARROW + 1
#define PLUS            PERCENT + 1
#define MINUS           PLUS + 1
#define MUL             MINUS + 1
#define DIV             MUL + 1
#define PIPE            DIV + 1
#define OR              PIPE + 1
#define AND             OR + 1
#define ANDAND          AND + 1
#define NOT             ANDAND + 1
#define DOLLAR          NOT + 1
#define COLON           DOLLAR + 1
#define SEMI            COLON + 1
#define COMMA           SEMI + 1
#define QUESTION        COMMA + 1
#define EQ              QUESTION + 1
#define EQEQ            EQ + 1
#define NE              EQEQ + 1
#define GT              NE + 1
#define GE              GT + 1
#define LT              GE + 1
#define LE              LT + 1
#define AT              LE + 1
#define TILDE           AT + 1
#define NOTEQ           TILDE + 1
#define PERCENTEQ       NOTEQ + 1
#define ANDEQ           PERCENTEQ + 1
#define MULEQ           ANDEQ + 1
#define DOUBLEMULEQ     MULEQ + 1
#define PLUSEQ          DOUBLEMULEQ + 1
#define MINUSEQ         PLUSEQ + 1
#define DIVEQ           MINUSEQ + 1
#define CIRCUMFLEXEQ    DIVEQ + 1
#define PIPEEQ          CIRCUMFLEXEQ + 1
#define RSHIFTEQ        PIPEEQ + 1
#define LSHIFTEQ        RSHIFTEQ + 1
#define LSHIFT          LSHIFTEQ + 1
#define RSHIFT          LSHIFT + 1
#define COMMENT         RSHIFT + 1
#define DOT             COMMENT + 1
#define DOTDOT          DOT + 1
#define ELLIPSIS        DOTDOT + 1
#define IDONNO          ELLIPSIS + 1

#define ISWHITESPACE(x) (x == NEWLINE)
int token_one_char(wchar_t c1);
int token_two_char(wchar_t c1, wchar_t c2);
int token_three_char(wchar_t c1, wchar_t c2, wchar_t c3);
#endif