#ifndef __JAEYEONG_JYIO_H__
#define __JAEYEONG_JYIO_H__
#include "apua.h"
#include "jstrings.h"

void _write_buf_to_fd(int fd, u8* buf, int buf_len);
void _writeln_to_fd(int fd, string s);
void eprint(string s);
void eprintln(string s);
void print(string s);
void println(string s);
#endif /* __JAEYEONG_JYIO_H__ */