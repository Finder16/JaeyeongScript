#ifndef __JAEYEONG_LANGUAGE_H__
#define __JAEYEONG_LANGUAGE_H__
#include "jstrings.h"

//! @enum Language
//! @brief Represents a language.
//!
//! This enumeration is used to distinguish between different languages.
//! Currently, English, Ukrainian, and Korean are defined.
enum Language {
  English,
  Ukrainian,
  Korean
};

//! @def LANG(x, y)
//! @brief Returns a string literal based on the specified language.
//!
//! This macro returns a string literal based on the language y.
//! If y is English, the string literal x is returned.
//! If y is Ukrainian, the string literal x_UA is returned.
//! Otherwise, the string literal x_KR is returned.
//!
//! @param x The base name of the string literal.
//! @param y The language.
#define LANG(x, y) (y == English ? _SLIT(x) : y == Ukrainian ? _SLIT(x ## _UA) : _SLIT(x ## _KR))
#endif