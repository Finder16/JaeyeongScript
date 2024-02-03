#include <stdio.h>
#include <stdlib.h>
#include "jaeyeong.h"

extern CompilerOptions options;

OptionApuaFile apua_file_open(string path, string mode) {
  ApuaFile* file = (ApuaFile*)jcalloc(sizeof(ApuaFile));
  file->path = path;
  file->safe = 0;
  file->file_ptr = fopen((char*)path.str, (char*)mode.str);
  if (file->file_ptr == _jNULL) {
    jfree(file);
    return none();
  }
  return some((void*)file, sizeof(ApuaFile));
}

void close_apua_file(ApuaFile *safe_file) {
  if (safe_file->safe == -98761234) {
    __panic(format_string(LANG(JAEYEONG_ERR_DOUBLE_FREE/*, options.language*/), (char*)_SLIT("ApuaFile").str));
    UNREACHABLE();
  }
  if (safe_file->file_ptr != NULL) {
    fclose(safe_file->file_ptr);
    safe_file->file_ptr = NULL;
  }
  safe_file->safe = -98761234;
}