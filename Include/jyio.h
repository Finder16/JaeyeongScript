#ifndef __JAEYEONG_JYIO_H__
#define __JAEYEONG_JYIO_H__
#include "apua.h"
#include "jstrings.h"

//! @copyright Alexander Medvednikov
//! @brief 버퍼의 내용을 파일 디스크립터에 씁니다.
//! 이 함수는 버퍼의 내용을 주어진 파일 디스크립터에 씁니다.
//! 버퍼의 길이가 0보다 작거나 같으면 함수는 아무것도 하지 않고 반환합니다.
//! 파일 디스크립터가 2인 경우 출력은 stderr에 쓰여지고, 그렇지 않으면 stdout에 쓰여집니다.
//! @param fd The file descriptor to write to. If 2, writes to stderr, otherwise writes to stdout.
//! @param buf A pointer to the buffer that contains the data to be written.
//! @param buf_len The length of the buffer. If less than or equal to 0, the function returns without writing anything.
//! @return void
void _write_buf_to_fd(int fd, u8* buf, int buf_len);

//! @copyright Alexander Medvednikov
//! @brief 문자열을 파일 디스크립터에 쓰고, 줄바꿈 문자를 씁니다.
//! 이 함수는 주어진 문자열을 파일 디스크립터에 쓰고, 줄바꿈 문자(`\\n`)를 씁니다.
//! 함수는 _write_buf_to_fd라는 헬퍼 함수를 사용합니다.
//! 버퍼의 메모리는 jmalloc으로 할당되고, jfree로 해제됩니다.
//! @param fd The file descriptor to write to.
//! @param s The string to write. The function will write the contents of this string, followed by a newline, to the file descriptor.
//! @return void
void _writeln_to_fd(int fd, string s);

//! @copyright Alexander Medvednikov
//! @brief 문자열을 표준 오류에 출력합니다.
//! 이 함수는 주어진 문자열을 표준 오류에 _write_buf_to_fd라는 헬퍼 함수를 사용하여 출력합니다.
//! 문자열 포인터가 null인 경우 함수는 표준 오류에 "eprint(NIL)"을 출력합니다.
//! 문자열을 쓰기 전과 후에 함수는 출력이 즉시 기록되도록 stdout과 stderr를 플러시합니다.
//! @param s The string to print to standard error. If the string pointer is null, the function prints "eprint(NIL)".
//! @return void
void eprint(string s);

//! @copyright Alexander Medvednikov
//! @brief 문자열을 표준 오류에 출력하고, 줄바꿈 문자를 출력합니다.
//! 이 함수는 주어진 문자열을 표준 오류에 _writeln_to_fd라는 헬퍼 함수를 사용하여 출력합니다.
//! 문자열 포인터가 null인 경우 함수는 표준 오류에 "eprintln(NIL)"을 출력합니다.
//! 문자열을 쓰기 전과 후에 함수는 출력이 즉시 기록되도록 stdout과 stderr를 플러시합니다.
//! @param s The string to print to standard error. If the string pointer is null, the function prints "eprintln(NIL)".
//! @return void
void eprintln(string s);

//! @copyright Alexander Medvednikov
//! @brief 문자열을 표준 출력에 출력합니다.
//! 이 함수는 주어진 문자열을 표준 출력에 _write_buf_to_fd라는 헬퍼 함수를 사용하여 출력합니다.
//! 문자열 포인터가 null인 경우 함수는 표준 출력에 "print(NIL)"을 출력합니다.
//! 문자열을 쓰기 전과 후에 함수는 출력이 즉시 기록되도록 stdout과 stderr를 플러시합니다.
//! @param s The string to print to standard output. If the string pointer is null, the function prints "print(NIL)".
//! @return void
void print(string s);

//! @copyright Alexander Medvednikov
//! @brief 문자열을 표준 출력에 출력하고, 줄바꿈 문자를 출력합니다.
//! 이 함수는 주어진 문자열을 표준 출력에 _writeln_to_fd라는 헬퍼 함수를 사용하여 출력합니다.
//! 문자열 포인터가 null인 경우 함수는 표준 출력에 "println(NIL)"을 출력합니다.
//! 문자열을 쓰기 전과 후에 함수는 출력이 즉시 기록되도록 stdout과 stderr를 플러시합니다.
//! @param s The string to print to standard output. If the string pointer is null, the function prints "println(NIL)".
//! @return void
void println(string s);
#endif /* __JAEYEONG_JYIO_H__ */