#ifndef __JAEYEONG_LANGUAGE_H__
#define __JAEYEONG_LANGUAGE_H__
#include "jstrings.h"
//! @enum Language
//! @brief 언어를 나타냅니다.
//! 이 열거형은 서로 다른 언어를 구분하기 위해 사용됩니다.
//! 현재 영어, 우크라이나어, 한국어가 정의되어 있습니다.
//! 또한 컴파일시 `-DJAEYEONG_NO_UKRANIAN` 또는 `-DJAEYEONG_NO_KOREAN` 옵션을 사용하여 우크라이나어 또는 한국어를 제외할 수 있습니다.
enum Language {
  English,
#ifndef JAEYEONG_NO_UKRANIAN
  Ukrainian,
#endif
#ifndef JAEYEONG_NO_KOREAN
  Korean,
#endif
};

extern CompilerOptions options;

//! @brief 다국어 지원을 위한 매크로입니다.
//! @details 이 매크로는 `options`의 언어 설정에 따라 다른 문자열을 반환합니다. 
//! `IS_UKRANIAN(options)`가 참이면, `_SLIT(x ## _UA)`를 반환하고, 
//! `IS_KOREAN(options)`가 참이면, `_SLIT(x ## _KR)`를 반환합니다. 
//! 두 조건 모두 만족하지 않으면 `_SLIT(x)`를 반환합니다.
//! @param x 반환할 기본 문자열입니다. 언어 설정에 따라 `x_UA` 또는 `x_KR` 문자열이 반환될 수 있습니다.
#define LANG(x) (IS_UKRANIAN(options) ? _SLIT(x ## _UA) : IS_KOREAN(options) ? _SLIT(x ## _KR) : _SLIT(x))
#endif