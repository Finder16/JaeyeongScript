#ifndef __JAEYEONG_ERROR_H__
#define __JAEYEONG_ERROR_H__
#include "apua.h"
#include "compiler.h"

struct MessageError {
  string msg;
  int code;
};

#define ERRINTFACE_T_DATA 0
#define ERRINTFACE_T_DATA_PTR ERRINTFACE_T_DATA+1
#define ERRINTFACE_T_ERROR    ERRINTFACE_T_DATA_PTR+1
#define ERRINTFACE_T_MESGERR  ERRINTFACE_T_ERROR+1

#define ETYPE_IDK 0
#define ETYPE_EOF 1

struct ErrorInterface {
  union {
    void* _data;
    void** _data_ptr;
    Error* _error;
    MessageError* _MessageError;
  };
  int _typ;
  string* msg;
  int errcode;
};

ErrorInterface jerror(string msg, int errcode);
ErrorInterface __error(string msg);

//! @brief 프로그램의 치명적인 오류를 처리하고 프로그램을 종료하는 함수입니다.
//! @details 이 함수는 프로그램에서 치명적인 오류가 발생했을 때 호출됩니다. 
//! 오류 메시지를 출력하고, 프로그램을 정상적으로 종료하기 위한 cleanup 작업을 수행한 후, 프로그램을 종료합니다.
//! @param s 출력할 오류 메시지입니다.
//! @param file 오류가 발생한 파일의 이름입니다.
//! @param line 오류가 발생한 코드의 라인 번호입니다.
//! @param func 오류가 발생한 함수의 이름입니다.
void panic(string s, char* file, int line, char* func);

//! @brief 현재 파일명, 라인 번호, 함수명을 자동으로 채워서 `panic` 함수를 호출하는 매크로입니다.
//! @details 이 매크로는 `panic` 함수를 더 쉽게 사용할 수 있도록 도와줍니다. 
//! `__FILE__`, `__LINE__`, `__func__`을 사용하여 오류가 발생한 위치를 자동으로 파악하고, 
//! 이 정보를 `panic` 함수에 전달합니다.
//! @param s 출력할 오류 메시지입니다.
#define __panic(s) panic(s, __FILE__, __LINE__, (char*)__func__)

string format_err(string kind, string omsg, string filepath, tokpos pos);

#define JAEYEONG_ERR_FILEOPEN "Error: Failed to open file %s."
#define JAEYEONG_ERR_DOUBLE_FREE "Error: Attempted to free a %s that has already been freed."
#define JAEYEONG_ERR_PROBE_OVERFLOW  "Probe overflow"
#define JAEYEONG_ERR_ARR_ENSURE_CAP_NOGROW "array.ensure_cap: array with the flag `.nogrow` cannot grow in size, array required new size: "
#define JAEYEONG_ERR_ARR_REPEAT_COUNT_NEG "array.repeat: count is negative: "
#define JAEYEONG_ERR_OOR "index out of range (i == "
#define JAEYEONG_ERR_ARR_INSERT_OOR "array.insert: " JAEYEONG_ERR_OOR
#define JAEYEONG_ERR_ARR_INSERT_MANY_OOR "array.insert_many: " JAEYEONG_ERR_OOR
#define JAEYEONG_ERR_ARR_DELETE_OOR "array.delete: " JAEYEONG_ERR_OOR
#define JAEYEONG_ERR_ARR_GET_OOR "array.get: " JAEYEONG_ERR_OOR
#define JAEYEONG_ERR_ARR_SET_OOR "array.set: " JAEYEONG_ERR_OOR
#define JAEYEONG_ERR_ARR_EMPTY "array is empty"
#define JAEYEONG_ERR_ARR_FIRST_EMPTY "array.first: " JAEYEONG_ERR_ARR_EMPTY
#define JAEYEONG_ERR_ARR_LAST_EMPTY "array.last: " JAEYEONG_ERR_ARR_EMPTY
#define JAEYEONG_ERR_ARR_POP_EMPTY "array.pop: " JAEYEONG_ERR_ARR_EMPTY
#define JAEYEONG_ERR_ARR_SLICE_INV_INDEX "array.slice: invalid slice index ("
#define JAEYEONG_ERR_SLICE_BOOR "slice bounds out of range ("
#define JAEYEONG_ERR_ARR_SLICE_BOOR "array.slice: " JAEYEONG_ERR_SLICE_BOOR
#define JAEYEONG_ERR_FREE_NOFREE "array.free: array with the flag `.nofree` cannot be freed"
#define JAEYEONG_ERR_BIN_WRONG_START "binary number cannot start with 0b_"
#define JAEYEONG_ERR_HEX_WRONG_START "hex number cannot start with 0x_"
#define JAEYEONG_ERR_DEC_WRONG_START "decimal number cannot start with _"

#ifndef JAYEONG_NO_UKRANIAN
#define JAEYEONG_ERR_FILEOPEN_UA "Помилка: Не вдалося відкрити файл %s."
#define JAEYEONG_ERR_DOUBLE_FREE_UA "Помилка: Спроба звільнити %s, який вже був звільнений."
#define JAEYEONG_ERR_PROBE_OVERFLOW_UA "Переповнення проби"
#define JAEYEONG_ERR_ARR_ENSURE_CAP_NOGROW_UA "array.ensure_cap: масив з прапорцем `.nogrow` не може збільшуватися, потрібен новий розмір масиву: "
#define JAEYEONG_ERR_ARR_REPEAT_COUNT_NEG_UA "array.repeat: кількість негативна: "
#define JAEYEONG_ERR_OOR_UA "індекс поза діапазоном (i == "
#define JAEYEONG_ERR_ARR_INSERT_OOR_UA "array.insert: " JAEYEONG_ERR_OOR_UA
#define JAEYEONG_ERR_ARR_INSERT_MANY_OOR_UA "array.insert_many: " JAEYEONG_ERR_OOR_UA
#define JAEYEONG_ERR_ARR_DELETE_OOR_UA "array.delete: " JAEYEONG_ERR_OOR_UA
#define JAEYEONG_ERR_ARR_GET_OOR_UA "array.get: " JAEYEONG_ERR_OOR_UA
#define JAEYEONG_ERR_ARR_SET_OOR_UA "array.set: " JAEYEONG_ERR_OOR_UA
#define JAEYEONG_ERR_ARR_EMPTY_UA "масив порожній"
#define JAEYEONG_ERR_ARR_FIRST_EMPTY_UA "array.first: " JAEYEONG_ERR_ARR_EMPTY_UA
#define JAEYEONG_ERR_ARR_LAST_EMPTY_UA "array.last: " JAEYEONG_ERR_ARR_EMPTY_UA
#define JAEYEONG_ERR_ARR_POP_EMPTY_UA "array.pop: " JAEYEONG_ERR_ARR_EMPTY_UA
#define JAEYEONG_ERR_ARR_SLICE_INV_INDEX_UA "array.slice: недійсний індекс зрізу ("
#define JAEYEONG_ERR_SLICE_BOOR_UA "межі зрізу поза діапазоном ("
#define JAEYEONG_ERR_ARR_SLICE_BOOR_UA "array.slice: " JAEYEONG_ERR_SLICE_BOOR_UA
#define JAEYEONG_ERR_FREE_NOFREE_UA "array.free: масив з прапорцем `.nofree` не може бути звільнений"
#define JAEYEONG_ERR_BIN_WRONG_START_UA "двійкове число не може починатися з 0b_"
#define JAEYEONG_ERR_HEX_WRONG_START_UA "шістнадцяткове число не може починатися з 0x_"
#define JAEYEONG_ERR_DEC_WRONG_START_UA "десяткове число не може починатися з _"
#endif /* JAYEONG_NO_UKRANIAN */

#ifndef JAEYEONG_NO_KOREAN
#define JAEYEONG_ERR_FILEOPEN_KR "오류: 파일 %s을(를) 열 수 없습니다."
#define JAEYEONG_ERR_DOUBLE_FREE_KR "오류: 이미 해제된 %s을(를) 해제하려고 시도했습니다."
#define JAEYEONG_ERR_PROBE_OVERFLOW_KR "Probe 오버플로우"
#define JAEYEONG_ERR_ARR_ENSURE_CAP_NOGROW_KR "array.ensure_cap: `.nogrow` 플래그가 있는 배열은 크기를 늘릴 수 없습니다. 배열이 필요한 새 크기: "
#define JAEYEONG_ERR_ARR_REPEAT_COUNT_NEG_KR "array.repeat: count가 음수입니다: "
#define JAEYEONG_ERR_OOR_KR "인덱스가 범위를 벗어났습니다 (i == "
#define JAEYEONG_ERR_ARR_INSERT_OOR_KR "array.insert: " JAEYEONG_ERR_OOR_KR
#define JAEYEONG_ERR_ARR_INSERT_MANY_OOR_KR "array.insert_many: " JAEYEONG_ERR_OOR_KR
#define JAEYEONG_ERR_ARR_DELETE_OOR_KR "array.delete: " JAEYEONG_ERR_OOR_KR
#define JAEYEONG_ERR_ARR_GET_OOR_KR "array.get: " JAEYEONG_ERR_OOR_KR
#define JAEYEONG_ERR_ARR_SET_OOR_KR "array.set: " JAEYEONG_ERR_OOR_KR
#define JAEYEONG_ERR_ARR_EMPTY_KR "배열이 비어있습니다"
#define JAEYEONG_ERR_ARR_FIRST_EMPTY_KR "array.first: " JAEYEONG_ERR_ARR_EMPTY_KR
#define JAEYEONG_ERR_ARR_LAST_EMPTY_KR "array.last: " JAEYEONG_ERR_ARR_EMPTY_KR
#define JAEYEONG_ERR_ARR_POP_EMPTY_KR "array.pop: " JAEYEONG_ERR_ARR_EMPTY_KR
#define JAEYEONG_ERR_ARR_SLICE_INV_INDEX_KR "array.slice: 잘못된 슬라이스 인덱스 ("
#define JAEYEONG_ERR_SLICE_BOOR_KR "슬라이스 경계가 범위를 벗어났습니다 ("
#define JAEYEONG_ERR_ARR_SLICE_BOOR_KR "array.slice: " JAEYEONG_ERR_SLICE_BOOR_KR
#define JAEYEONG_ERR_FREE_NOFREE_KR "array.free: `.nofree` 플래그가 있는 배열은 해제할 수 없습니다"
#define JAEYEONG_ERR_BIN_WRONG_START_KR "2진수 숫자는 0b_로 시작할 수 없습니다"
#define JAEYEONG_ERR_HEX_WRONG_START_KR "16진수 숫자는 0x_로 시작할 수 없습니다"
#define JAEYEONG_ERR_DEC_WRONG_START_KR "10진수 숫자는 _로 시작할 수 없습니다"
#endif /* JAEYEONG_NO_KOREAN */

#endif /* __JAEYEONG_ERROR_H__ */