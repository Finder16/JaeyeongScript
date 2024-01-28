#ifndef __JAEYEONG_OPTIONS_H__
#define __JAEYEONG_OPTIONS_H__
#include <stdint.h>
#include <stdbool.h>
#include "apua.h"
#include "language.h"
#include "edition.h"

//! @struct CompilerOptions
//! @brief Represents the options for the compiler.
//!
//! This structure represents the options that can be set for the compiler.
//! It contains the language, the edition of the compiler, the input file, and flags for verbose output, debugging, and help.
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