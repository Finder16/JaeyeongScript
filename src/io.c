#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "jaeyeong.h"

void _write_buf_to_fd(int fd, u8* buf, int buf_len){
	if (buf_len <= 0) return;
	u8* ptr = buf;
	isize remaining_bytes = ((isize)(buf_len));
	isize x = ((isize)(0));
  void* stream = ((void*)(stdout));
	if (fd == 2) stream = ((void*)(stderr));
	for (;;) {
		if (!(remaining_bytes > 0)) break;
		x = ((isize)(fwrite(ptr, 1, remaining_bytes, stream)));
		ptr += x;
		remaining_bytes -= x;
	}
}

void _writeln_to_fd(int fd, string s) {
	bool _writeln_to_fd_defer_0 = false;
	u8* buf;
	u8 lf = ((u8)('\n'));
	_write_buf_to_fd(fd, s.str, s.len);
	_write_buf_to_fd(fd, &lf, 1);
	return;
	int buf_len = (int)(s.len + 1);
	buf = jmalloc(buf_len);
	_writeln_to_fd_defer_0 = true;
	memcpy(buf, s.str, s.len);
	buf[s.len] = '\n';
	_write_buf_to_fd(fd, buf, buf_len);
	// Defer begin
	if (_writeln_to_fd_defer_0) {
		jfree(buf);
	}
	// Defer end
}

void eprint(string s) {
	if (s.str == 0) {
		eprint(_SLIT("eprint(NIL)"));
		return;
	}
  fflush(stdout);
  fflush(stderr);
	_write_buf_to_fd(2, s.str, s.len);
	fflush(stderr);
}

void eprintln(string s) {
	if (s.str == 0) {
		eprintln(_SLIT("eprintln(NIL)"));
		return;
	}
  fflush(stdout);
  fflush(stderr);
	_writeln_to_fd(2, s);
	fflush(stderr);
}

void print(string s) {
  if (s.str == 0) {
    print(_SLIT("print(NIL)"));
    return;
  }
  fflush(stdout);
  fflush(stderr);
  _write_buf_to_fd(1, s.str, s.len);
  fflush(stdout);
}

void println(string s) {
  if (s.str == 0) {
    println(_SLIT("println(NIL)"));
    return;
  }
  fflush(stdout);
  fflush(stderr);
  _writeln_to_fd(1, s);
  fflush(stdout);
}