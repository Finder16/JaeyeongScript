#ifndef __JAEYEONG_FILE_H__
#define __JAEYEONG_FILE_H__
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "apua.h"
#include "jstrings.h"

//! @brief 파일을 안전하게 관리하기 위한 구조체입니다.
//! @details 이 구조체는 파일을 안전하게 관리하기 위해 사용됩니다. 
//! `file_ptr`는 파일 포인터를, `path`는 파일 경로를, `safe`는 파일의 상태를 나타냅니다.
//! @param file_ptr 파일 포인터입니다. `fopen` 함수를 통해 얻은 파일 포인터를 저장합니다.
//! @param path 파일의 경로입니다. 파일을 열 때 사용한 경로를 저장합니다.
//! @param safe 파일의 상태를 나타냅니다. 파일이 안전하게 닫혔는지 여부를 확인하는 데 사용됩니다.
typedef struct {
  FILE *file_ptr; //! @brief 파일 포인터입니다.
  string path; //! @brief 파일의 경로입니다.
  int safe; //! @brief 파일의 상태를 나타냅니다. 파일이 안전하게 닫혔는지 여부를 확인하는 데 사용됩니다.
} ApuaFile;

//! @brief 파일을 열고, 그 결과를 `OptionApuaFile` 형태로 반환하는 함수입니다.
//! @details 이 함수는 주어진 경로와 모드로 파일을 열고, 그 결과를 `OptionApuaFile` 형태로 반환합니다. 
//! 파일 열기가 성공하면 `some`을 반환하고, 실패하면 `none`을 반환합니다.
//! @param path 열고자 하는 파일의 경로입니다.
//! @param mode 파일을 열 때 사용할 모드입니다. 예를 들어, "r"은 읽기 모드, "w"은 쓰기 모드를 의미합니다.
//! @return 파일 열기의 결과를 나타내는 `OptionApuaFile`입니다. 파일 열기가 성공하면 `some`을 반환하고, 실패하면 `none`을 반환합니다.
OptionApuaFile apua_file_open(string path, string mode);

//! @brief `ApuaFile` 구조체를 안전하게 닫는 함수입니다.
//! @details 이 함수는 `ApuaFile` 구조체를 안전하게 닫습니다. 
//! `ApuaFile`이 이미 닫혀있는 경우, 즉 `safe` 필드가 -98761234인 경우에는 이중 해제 오류 메시지를 출력하고 프로그램을 종료합니다. 
//! 그렇지 않은 경우에는 파일을 닫고, `file_ptr` 필드를 NULL로 설정하고, `safe` 필드를 -98761234로 설정합니다.
//! @param safe_file 닫을 `ApuaFile` 구조체의 포인터입니다.
void close_apua_file(ApuaFile *safe_file);
#endif