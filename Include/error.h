#ifndef __JAEYEONG_ERROR_H__
#define __JAEYEONG_ERROR_H__
#include "apua.h"

//! @fn void panic(string s, char* file, int line, char* func)
//! \~english @brief Prints an error message and terminates the program.
//!
//! This function prints an error message and terminates the program. 
//! The error message, the file name, the line number, and the function name are given as arguments.
//!
//! @param s The error message to be printed.
//! @param file The name of the file where the error occurred.
//! @param line The line number where the error occurred.
//! @param func The name of the function where the error occurred.
void panic(string s, char* file, int line, char* func);
//! @def __panic(s)
//! @brief Triggers a panic with a message and the location in the code.
//!
//! This macro triggers a panic with a message s and the location in the code 
//! where the panic was triggered (file name, line number, and function name).
//! This is typically called when an unrecoverable error is encountered in the program.
//!
//! @param s The panic message.
#define __panic(s) panic(s, __FILE__, __LINE__, (char*)__func__)
#endif /* __JAEYEONG_ERROR_H__ */