#ifndef __JAEYEONG_LANGUAGE_H__
#define __JAEYEONG_LANGUAGE_H__
#include "jstrings.h"

//! @enum Language
//! \~english @brief Represents a language.
//! This enumeration is used to distinguish between different languages.
//! Currently, English, Ukrainian, and Korean are defined.
//!
//! \~korean @brief 언어를 나타냅니다.
//! 이 열거형은 서로 다른 언어를 구분하기 위해 사용됩니다.
//! 현재 영어, 우크라이나어, 한국어가 정의되어 있습니다.
enum Language {
  English,
  Ukrainian,
  Korean
};

//! @def LANG(x, y)
//! \~english @brief Returns a string literal based on the specified language.
//! This macro returns a string literal based on the language y.
//! If y is English, the string literal x is returned.
//! If y is Ukrainian, the string literal x_UA is returned.
//! Otherwise, the string literal x_KR is returned.
//!
//! \~korean @brief 지정된 언어를 기반으로 문자열 리터럴을 반환합니다.
//! 이 매크로는 언어 y를 기반으로 문자열 리터럴 x를 반환합니다.
//! y가 `English`인 경우 문자열 리터럴 `x`가 반환됩니다.
//! y가 `Ukrainian`인 경우 문자열 리터럴 `x ## UA`가 반환됩니다.
//! 그렇지 않으면 문자열 리터럴 `x ## KR`이 반환됩니다.
//!
//! \~english @param x The base name of the string literal.
//! \~english @param y The language.
#define LANG(x, y) (y == English ? _SLIT(x) : y == Ukrainian ? _SLIT(x ## _UA) : _SLIT(x ## _KR))
#endif