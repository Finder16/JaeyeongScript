#ifndef __JAEYEONG_JYIO_H__
#define __JAEYEONG_JYIO_H__
#include "apua.h"
#include "jstrings.h"

//! @fn void _write_buf_to_fd(int fd, u8* buf, int buf_len)
//! @brief Writes the content of a buffer to a file descriptor.
//! 
//! This function writes the content of a buffer to a given file descriptor.
//! If the buffer length is less than or equal to 0, the function will return without doing anything.
//! If the file descriptor is 2, the output will be written to stderr, otherwise it will be written to stdout.
//! 
//! @param fd The file descriptor to write to. If 2, writes to stderr, otherwise writes to stdout.
//! @param buf A pointer to the buffer that contains the data to be written.
//! @param buf_len The length of the buffer. If less than or equal to 0, the function returns without writing anything.
//! @return void
void _write_buf_to_fd(int fd, u8* buf, int buf_len);
//! @fn void _writeln_to_fd(int fd, string s)
//! @brief Writes a string to a file descriptor, followed by a newline.
//! 
//! This function writes a given string to a file descriptor,
//! and then writes a newline character (`\\n`). The function uses the helper function _write_buf_to_fd.
//! Memory for the buffer is allocated with jmalloc and released with jfree.
//!
//! @param fd The file descriptor to write to.
//! @param s The string to write. The function will write the contents of this string, followed by a newline, to the file descriptor.
//! @return void
void _writeln_to_fd(int fd, string s);
//! @fn void eprint(string s)
//! @brief Prints a string to standard error.
//! 
//! This function prints a given string to the standard error using the helper function _write_buf_to_fd.
//! If the string pointer is null, the function will print "eprint(NIL)" to the standard error.
//! Before and after writing the string, the function flushes stdout and stderr to ensure that the output is written immediately.
//!
//! @param s The string to print to standard error. If the string pointer is null, the function prints "eprint(NIL)".
//! @return void
void eprint(string s);
//! @fn void eprintln(string s)
//! @brief Prints a string to standard error, followed by a newline.
//! 
//! This function prints a given string to the standard error using the helper function _writeln_to_fd.
//! If the string pointer is null, the function will print "eprintln(NIL)" to the standard error.
//! Before and after writing the string, the function flushes stdout and stderr to ensure that the output is written immediately.
//!
//! @param s The string to print to standard error. If the string pointer is null, the function prints "eprintln(NIL)".
//! @return void
void eprintln(string s);
//! @fn void print(string s)
//! @brief Prints a string to standard output.\n
//! 
//! This function prints a given string to the standard output using the helper function _write_buf_to_fd. <br>
//! If the string pointer is null, the function will print "print(NIL)" to the standard output.
//! Before and after writing the string, the function flushes stdout and stderr to ensure that the output is written immediately.
//!
//! @param s The string to print to standard output. If the string pointer is null, the function prints "print(NIL)".
//! @return void
void print(string s);
//! @fn void println(string s)
//! @brief Prints a string to standard output, followed by a newline.
//!
//! This function prints a given string to the standard output using the helper function _writeln_to_fd.
//! If the string pointer is null, the function will print "println(NIL)" to the standard output.
//! Before and after writing the string, the function flushes stdout and stderr to ensure that the output is written immediately.
//!
//! @param s The string to print to standard output. If the string pointer is null, the function prints "println(NIL)".
//! @return void
void println(string s);
#endif /* __JAEYEONG_JYIO_H__ */