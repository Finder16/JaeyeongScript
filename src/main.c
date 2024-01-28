#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include "jaeyeong.h"

CompilerOptions options;

//! @since 0.1.0
//! @date 2024-01-28 19:22:00 KST
//! @brief Prints the usage message and exits.
void usage(void) {
  eprintln(LANG(_S_JAEYEONG_USAGE, options.language));
  exit(1);
}

void parse_option(CompilerOptions* opt, const wchar_t* argv[]) {
  wchar_t* allowedExtensions[] = {L".jy", L".jaeyeong", NULL};
  for (int i = 1; argv[i] != NULL; i++) {
    if (wcscmp(argv[i], L"--help") == 0) {
      opt->help = true;
    } else if (wcscmp(argv[i], L"--english") == 0) {
      opt->language = opt->language;
    } else if (wcscmp(argv[i], L"--korean") == 0) {
      opt->language = (opt->language != English) ? opt->language : Korean;
    } else if (wcscmp(argv[i], L"--ukrainian") == 0) {
      opt->language = (opt->language != English) ? opt->language : Ukrainian;
    } else {
      for (int j = 0; allowedExtensions[j] != NULL; j++) {
        if (wcsstr(argv[i], allowedExtensions[j]) != NULL) {
          opt->input_file = argv[i];
          break;
        }
      }
    }
  }
}

int wmain(int argc, wchar_t argv[]/*, wchar_t envp[]*/) {
  builtin_init();
  options = default_options();
  parse_option(&options, argv);
  if (options.input_file == NULL) usage();
  return 0;
}