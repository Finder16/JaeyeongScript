#include "jaeyeong.h"

const char* const _woojinC_TokenName[] = {
  "ENDMARKER",
  "NAME",
  "INTEGER",
  "FLOAT",
  "STRING",
  "TRUE_LIT",
  "FALSE_LIT",
  "NEWLINE",
  "LPAREN",
  "RPAREN",
  "LSQB",
  "RSQB",
  "LBRACE",
  "RBRACE",
  "ARROW",
  "PERCENT",
  "PLUS",
  "MINUS",
  "MUL",
  "DIV",
  "PIPE",
  "OR",
  "AND",
  "ANDAND",
  "NOT",
  "DOLLAR",
  "COLON",
  "SEMI",
  "COMMA",
  "QUESTION",
  "EQ",
  "EQEQ",
  "NE",
  "GT",
  "GE",
  "LT",
  "LE",
  "AT",
  "TILDE",
  "NOTEQ",
  "PERCENTEQ",
  "ANDEQ",
  "MULEQ",
  "DOUBLEMULEQ",
  "PLUSEQ",
  "MINUSEQ",
  "DIVEQ",
  "CIRCUMFLEXEQ",
  "PIPEEQ",
  "RSHIFTEQ",
  "LSHIFTEQ",
  "LSHIFT",
  "RSHIFT",
  "COMMENT",
  "DOT",
  "DOTDOT",
  "ELLIPSIS",
  "IDONNO",
  ((void *)0)
};

void token_free(token *t)
{
  if (t->lineno == -98761234 && t->end_lineno == -98761234) __panic(_SLIT("double token_free() detected"));
  t->lineno = -98761234;
  t->end_lineno = -98761234;
  jfree((void*)t->start);
  jfree((void*)t->end);
  jfree(t);
}

int token_one_char(wchar_t wc1)
{
  switch (wc1) {
    case L'!': return NOT;
    case L'%': return PERCENT;
    case L'&': return AND;
    case L'(': return LPAREN;
    case L')': return RPAREN;
    case L'*': return MUL;
    case L'+': return PLUS;
    case L',': return COMMA;
    case L'-': return MINUS;
    case L'.': return DOT;
    case L'/': return DIV;
    case L':': return COLON;
    case L';': return SEMI;
    case L'<': return LT;
    case L'=': return EQ;
    case L'>': return GT;
    case L'@': return AT;
    case L'[': return LSQB;
    case L']': return RSQB;
    case L'^': return ARROW;
    case L'{': return LBRACE;
    case L'|': return PIPE;
    case L'}': return RBRACE;
    case L'~': return TILDE;
    default: return IDONNO;
  }
}

int token_two_char(wchar_t wc1, wchar_t wc2)
{
  switch(wc1) {
    case L'!': return wc2 == L'=' ? NE : IDONNO;
    case L'%': return wc2 == L'=' ? PERCENTEQ : IDONNO;
    case L'&': return wc2 == L'&' ? ANDAND : wc2 == L'=' ? EQ : IDONNO;
    case L'*': return wc2 == L'*' ? MUL : wc2 == L'=' ? ANDEQ : IDONNO;
    case L'+': return wc2 == L'=' ? PLUSEQ : IDONNO;
    case L'-': return wc2 == L'=' ? MINUSEQ : wc2 == L'>' ? ARROW : IDONNO;
    case L'/': return wc2 == L'=' ? DIVEQ : wc2 == L'/' ? COMMENT : IDONNO;
    case L'<': return wc2 == L'=' ? LE : wc2 == L'<' ? LSHIFT : IDONNO;
    case L'=': return wc2 == L'=' ? EQEQ : IDONNO;
    case L'>': return wc2 == L'=' ? GE : wc2 == L'>' ? RSHIFT : IDONNO;
    case L'^': return wc2 == L'=' ? CIRCUMFLEXEQ : IDONNO;
    case L'|': return wc2 == L'|' ? OR : wc2 == L'=' ? PIPEEQ : IDONNO;
    case L'.': return wc2 == L'.' ? DOTDOT : IDONNO;
    default: return IDONNO;
  }
}

int token_three_char(wchar_t wc1, wchar_t wc2, wchar_t wc3)
{
  switch(wc1) {
    case L'*': return wc2 == L'*' && wc3 == L'=' ? DOUBLEMULEQ : IDONNO;
    case L'<': return wc2 == L'<' && wc3 == L'=' ? LSHIFTEQ : IDONNO;
    case L'>': return wc2 == L'>' && wc3 == L'=' ? RSHIFTEQ : IDONNO;
    case L'.': return wc2 == L'.' && wc3 == L'.' ? ELLIPSIS : IDONNO;
    default: return IDONNO;
  }
}