#ifndef __JAEYEONG_OPTIONS_H__
#define __JAEYEONG_OPTIONS_H__
#include <stdint.h>
#include <stdbool.h>
#include "apua.h"
#include "language.h"
#include "edition.h"

//! @struct CompilerOptions
//! \~english @brief Represents the options for the compiler.
//! This structure represents the options that can be set for the compiler.
//! It contains the language, the edition of the compiler, the input file, and flags for verbose output, debugging, and help.
//! \~korean @brief 컴파일러의 옵션을 나타냅니다.
//! 이 구조체는 컴파일러에 설정할 수 있는 옵션을 나타냅니다.
//! 언어, 컴파일러의 에디션, 입력 파일, 그리고 자세한 출력, 디버깅, 도움말에 대한 플래그를 포함합니다.
struct CompilerOptions {
  Language language;
  Edition edition;
  wchar_t *input_file;
  bool verbose;
  bool debug;
  bool help;
};

//! @fn CompilerOptions default_options(void)
//! \~english @brief Returns the default compiler options.
//! This function returns a CompilerOptions structure with default values.
//! The default values are: English language, 2024 edition, no input file, and no verbose output, debugging, or help.
//! \~korean @brief 기본 컴파일러 옵션을 반환합니다.
//! 이 함수는 기본값으로 CompilerOptions 구조체를 반환합니다.
//! 기본값은 다음과 같습니다: 영어 언어, 2024 에디션, 입력 파일 없음, 자세한 출력, 디버깅, 도움말 없음.
//! \~english @return Returns a CompilerOptions structure with default values.
//! \~korean @return 기본값으로 설정된 CompilerOptions 구조체를 반환합니다.
CompilerOptions default_options(void);
#endif