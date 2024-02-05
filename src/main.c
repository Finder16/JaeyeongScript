#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include "jaeyeong.h"

CompilerOptions options;
lexer* lex = _jNULL;
LinesCache* lines_cache = _jNULL;

//! @since 0.1.0
//! @date 2024-01-28 19:22:00 KST
//! @brief Prints the usage message and exits.
void usage(void) {
  eprintln(LANG(_S_JAEYEONG_USAGE/*, options.language*/));
  exit(1);
}

void parse_option(CompilerOptions* opt, int argc, const wchar_t* argv[]) {
  wchar_t* allowedExtensions[] = {L".jy", L".jaeyeong", NULL};
  for (int i = 1; i < argc; i++) {
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
        if (endsWithW(argv[i], allowedExtensions[j])) {
          OptionApuaFile file = apua_file_open(wchar_to_string(argv[i]), _SLIT("r"));
          if (!file.is_some) {
            eprintln(format_string(LANG(JAEYEONG_ERR_FILEOPEN/*, opt->language*/), (char*)wchar_to_string(argv[i]).str));
            exit(1);
          }
          opt->input_file = (ApuaFile*)file.value;
          break;
        }
      }
    }
  }
}

char* read_file(FILE* file) {
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = (char*)jmalloc(length + 1);
    if (buffer == NULL) {
        printf("Cannot allocate memory for file contents\n");
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, length, file);
    buffer[length] = '\0';

    fclose(file);
    return buffer;
}

int wmain(int argc, wchar_t* argv[]/*, wchar_t envp[]*/) {
  builtin_init();
  options = default_options();
  parse_option(&options, argc, (const wchar_t**)argv);
  printf("%d\n", sizeof(void*));
  lines_cache = ((LinesCache*)memdup(&(LinesCache){.lines = new_map(sizeof(string), sizeof(Array_string), &map_hash_string, &map_eq_string, &map_clone_string, &map_free_string),}, sizeof(LinesCache))); // 3global
  if (options.input_file == NULL) usage();
  // read text from file
  char* file = read_file(options.input_file->file_ptr);
  lex = new_lexer(string_with_len((u8*)file, strlen(file)), string_clone(options.input_file->path));
  lexer_scan_all(lex);
  bulitin_cleanup();
  return 0;
}

void bulitin_cleanup(void) {
  free_options(&options);
}