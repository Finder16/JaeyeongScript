#ifndef __JAEYEONG_INIT_H__
#define __JAEYEONG_INIT_H__
#include "apua.h"

#define _const_std_output_handle -11
#define _const_std_error_handle -12
#define _const_enable_processed_output 1
#define _const_enable_wrap_at_eol_output 2
#define _const_cp_utf8 65001
#define _const_evable_virtual_terminal_processing 4

//! @date 2024-01-28 19:22:00 KST
//! @since 0.1.0
//! @brief Checks if a file descriptor is associated with a terminal.
//! This function checks if the given file descriptor is associated with a terminal (console) in a Windows environment.
//! It uses the Microsoft-specific function `_get_osfhandle` to retrieve the operating system file handle associated with the file descriptor,
//! and then uses `GetConsoleMode` to get the console mode. If the file descriptor is associated with a console, `GetConsoleMode` will succeed and the function will return a non-zero value.
//! If the file descriptor is not associated with a console, `GetConsoleMode` will fail and the function will return zero. 
//! @param fd The file descriptor to check.
//! @return Non-zero if the file descriptor is associated with a terminal, zero otherwise.
int is_terminal(int fd);
//! @brief Restores the original code page of the console output.
//! This function restores the original code page that was active when the program started. 
//! It uses the global variable `g_original_codepage` which should hold the original code page.
//! @date 2024-01-28 19:22:00 KST
//! @since 0.1.0
void restore_codepage(void);
//! @brief Initializes the console environment for the application.
//! This function sets the console output code page to UTF-8, registers a function to restore the original code page at exit,
//! and configures the console modes for standard output and standard error if they are associated with a terminal.
//! It also disables buffering for standard output and standard error.
//! If the `_JAEYEONG_DEV_NO_BACKTRACE` macro is not defined, it also registers an unhandled exception handler.
//! @since 0.1.0
//! @date 2024-01-28 19:22:00 KST
void builtin_init(void);
//! @since 0.1.0
//! @date 2024-01-28 19:22:00 KST
//! @brief Parses command line options and sets the corresponding fields in the CompilerOptions structure.
//!  
//! This function parses the command line options given in argv. It recognizes the following options:  
//! --help, --english, --korean, --ukrainian, and file extensions .jy and .jaeyeong. If an option is recognized,
//! the corresponding field in the CompilerOptions structure is set. If a file extension is recognized, the input_file
//! field in the CompilerOptions structure is set to the argument containing the file extension.
//! 
//! @param opt A pointer to a CompilerOptions structure where the parsed options will be stored.
//! @param argv An array of wide string command line arguments. This array must be NULL-terminated.
void parse_option(CompilerOptions* opt, const wchar_t* argv[]);
#endif