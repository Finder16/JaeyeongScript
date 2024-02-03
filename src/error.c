#include <stdio.h>
#include <stdlib.h>
#include "jaeyeong.h"

ErrorInterface __error(string msg) {
  return jerror(msg, 0);
}

ErrorInterface jerror(string s, int errcode) {
  MessageError* x = ((MessageError*)memdup(&(MessageError){.msg = s, .code = errcode}, sizeof(MessageError)));
  return (ErrorInterface) {
    ._MessageError = x,
    ._typ = (ERRINTFACE_T_MESGERR),
    .msg = (string*)((char*)x + __offsetof_ptr(x, MessageError, msg)),
    .errcode = *(int*)((char*)x + __offsetof_ptr(x, MessageError, code)),
  };
}

void panic(string s, char* file, int line, char* func) {
  eprint(str_intp(3, _MOV(StrIntpData[]){{red(_SLITW("функція ")), 0x10, { .d_s =  bright_white(tos((u8*)func, strlen(func))) }}, {red(_SLITW(" викинула виняток у ")), 0x10, { .d_s = red(tos((u8*)file, strlen(file))) }}, {_SLIT(":"), 0x7, { .d_c = line }}}));
  eprint(_SLIT("\n  "));
  eprintln(bright_white(s));
  bulitin_cleanup();
  exit(0);
}
