#include <stdio.h>
#include <stdlib.h>
#include "jaeyeong.h"

void panic(string s, char* file, int line, char* func) {
	eprint(str_intp(4, _MOV(StrIntpData[]){{_SLITW("\e[0;31mфункція \e[4;31m\e[0;37m"), /*115 &string*/0x10, { .d_s =  tos((u8*)func, strlen(func)) }}, {_SLITW("\e[0;31m викинула виняток у "), 0x10, { .d_s = tos((u8*)file, strlen(file)) }}, {_SLIT(":"), 0x7, { .d_c = line }}, {_SLIT("\x1b[0m\n  \e[0;97m"), 0x0, {0}}}));
	eprintln(s);
	eprint(_SLIT("\x1b[0m"));
  exit(0);
}