#ifndef __JAEYEONG_COMPILER_H__
#define __JAEYEONG_COMPILER_H__
#include "apua.h"
#include "jstrings.h"
#include "token.h"

//! @struct CompilerOptions
//! @brief 컴파일러의 옵션을 나타냅니다.
//! 이 구조체는 컴파일러에 설정할 수 있는 옵션을 나타냅니다.
//! 언어, 컴파일러의 에디션, 입력 파일, 그리고 자세한 출력, 디버깅, 도움말에 대한 플래그를 포함합니다.
struct CompilerOptions {
  Language language;
  Edition edition;
  ApuaFile* input_file;
  bool verbose;
  bool debug;
  bool help;
};

//! @fn CompilerOptions default_options(void)
//! @brief 기본 컴파일러 옵션을 반환합니다.
//! 이 함수는 기본값으로 CompilerOptions 구조체를 반환합니다.
//! 기본값은 다음과 같습니다: 영어 언어, 2024 에디션, 입력 파일 없음, 자세한 출력, 디버깅, 도움말 없음.
//! @return 기본값으로 설정된 CompilerOptions 구조체를 반환합니다.
CompilerOptions default_options(void);
void free_options(CompilerOptions* options);

struct CompilerMessage {
  string message;
  string details;
  string file_path;
  tokpos pos;
  int reporter;
  // lex, parser, gen, builtin type
};

struct Error { CompilerMessage msg; };
struct Warning { CompilerMessage msg; };
struct Info { CompilerMessage msg; };

void show_comp_msg(string wtf, CompilerMessage err);
#endif