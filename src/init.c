#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <Windows.h>
#include <io.h>
#include "jaeyeong.h"

u32 g_original_codepage = ((u32)(0U));

int is_terminal(int fd) {
  u32 mode = ((u32)(0U));
  void* osfh = ((void*)(_get_osfhandle(fd)));
  GetConsoleMode(osfh, ((void*)(&mode)));
  return ((int)(mode));
}

void restore_codepage(void) {
  SetConsoleOutputCP(g_original_codepage);
}

void builtin_init(void) {
  g_original_codepage = GetConsoleOutputCP();
  SetConsoleOutputCP(_const_cp_utf8);
  atexit((void*)restore_codepage);
  if (is_terminal(1) > 0) {
    SetConsoleMode(GetStdHandle(_const_std_output_handle), ((_const_enable_processed_output | _const_enable_wrap_at_eol_output) | _const_evable_virtual_terminal_processing));
    SetConsoleMode(GetStdHandle(_const_std_error_handle), ((_const_enable_processed_output | _const_enable_wrap_at_eol_output) | _const_evable_virtual_terminal_processing));
    { // Unsafe block
      setbuf(stdout, 0);
      setbuf(stderr, 0);
    }
  }
  #if !defined(_JAEYEONG_DEV_NO_BACKTRACE)
  {
    // add_unhandled_exception_handler();
  }
  #endif
}

Option some(void* value, size_t size) {
  Option option;
  option.is_some = true;
  option.value = value;
  option.size = size;
  option.state = 0;
  return option;
}

Option none(void) {
  Option option;
  option.is_some = false;
  option.value = _jNULL;
  option.size = 0;
  option.state = -1;
  return option;
}