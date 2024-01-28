#include <stdio.h>
#include <stdlib.h>
#include "jaeyeong.h"

CompilerOptions default_options(void) {
  CompilerOptions options = {
    .debug = false,
    .language = (Language)English,
    .edition = (Edition)Edition2024,
    .input_file = NULL,
    .verbose = false,
    .help = false
  };
  return options;
}