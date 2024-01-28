#ifndef __JAEYEONG_OPTIONS_H__
#define __JAEYEONG_OPTIONS_H__
#include <stdint.h>
#include <stdbool.h>
#include "apua.h"
#include "language.h"
#include "edition.h"

struct CompilerOptions {
  Language language;
  Edition edition;
  wchar_t *input_file;
  bool verbose;
  bool debug;
  bool help;
};

CompilerOptions default_options(void);
#endif