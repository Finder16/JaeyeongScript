#ifndef __JAEYEONG_INIT_H__
#define __JAEYEONG_INIT_H__
#include "apua.h"

//! @brief 표준 출력 핸들을 나타내는 상수입니다.
#define _const_std_output_handle -11
//! @brief 표준 오류 핸들을 나타내는 상수입니다.
#define _const_std_error_handle -12
//! @brief 처리된 출력을 활성화하는 상수입니다.
#define _const_enable_processed_output 1
//! @brief EOL에서 자동 줄 바꿈을 활성화하는 상수입니다.
#define _const_enable_wrap_at_eol_output 2
//! @brief UTF-8 코드 페이지를 나타내는 상수입니다.
#define _const_cp_utf8 65001
//! @brief 가상 터미널 처리를 활성화하는 상수입니다.
#define _const_evable_virtual_terminal_processing 4

//! @brief 주어진 파일 디스크립터가 터미널인지 확인합니다.
//! 이 함수는 주어진 파일 디스크립터가 터미널인지 확인하기 위해 Windows API를 사용합니다.
//! _get_osfhandle 함수를 사용하여 파일 디스크립터를 OS 파일 핸들로 변환하고,
//! GetConsoleMode 함수를 사용하여 해당 핸들이 콘솔 모드인지 확인합니다.
//! @param fd 확인할 파일 디스크립터입니다.
//! @return 터미널이면 콘솔 모드 값을, 그렇지 않으면 0을 반환합니다.
int is_terminal(int fd);

//! @brief 원래의 코드 페이지로 복원합니다.
//! 이 함수는 SetConsoleOutputCP 함수를 사용하여 콘솔 출력의 코드 페이지를
//! 이전에 저장된 원래의 코드 페이지(g_original_codepage)로 복원합니다.
//! @note 이 함수는 g_original_codepage 전역 변수를 사용합니다.
void restore_codepage(void);

//! @brief 내장 초기화 함수입니다.
//! 이 함수는 콘솔 출력의 코드 페이지를 UTF-8로 설정하고, 프로그램 종료 시 원래의 코드 페이지로 복원하도록 설정합니다.
//! 또한, 표준 출력과 표준 오류가 터미널로 리디렉션되는 경우, 콘솔 모드를 설정하고 버퍼링을 비활성화합니다.
//! 마지막으로, `_JAEYEONG_DEV_NO_BACKTRACE`가 정의되지 않은 경우, 처리되지 않은 예외 핸들러를 추가합니다.
//! @note 이 함수는 `g_original_codepage` 전역 변수를 사용합니다.
void builtin_init(void);

//! @brief 컴파일러 옵션을 파싱하는 함수입니다.
//! 이 함수는 주어진 명령줄 인수를 파싱하여 CompilerOptions 구조체를 설정합니다.
//! --help, --english, --korean, --ukrainian 옵션을 인식하며, .jy 또는 .jaeyeong 확장자를 가진 파일을 입력 파일로 인식합니다.
//! @param[out] opt 설정할 CompilerOptions 구조체의 포인터입니다.
//! @param[in] argc 명령줄 인수의 개수입니다.
//! @param[in] argv 명령줄 인수의 배열입니다.
void parse_option(CompilerOptions* opt, int argc, const wchar_t* argv[]);

//!
void bulitin_cleanup(void);
#endif