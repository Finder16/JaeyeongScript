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

void free_options(CompilerOptions* options) {
  if (options->input_file->file_ptr != NULL) {
    close_apua_file(options->input_file);
    options->input_file = NULL;
  }
}