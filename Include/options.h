#ifndef __JAEYEONG_OPTIONS_H__
#define __JAEYEONG_OPTIONS_H__
#include <stdint.h>
#include <stdbool.h>
#include "apua.h"
#include "language.h"
#include "edition.h"
#include "file.h"
#include "error.h"

//! @struct Option 타입입니다.
//! @details 값이 있을 수도 있고 없을 수도 있는 상황을 나타내는 타입입니다.
struct Option {
  bool is_some; //! @brief 값이 있는지 없는지를 나타내는 불리언입니다.
  void* value; //! @brief 실제 값입니다. 값이 없는 경우 NULL입니다.
  size_t size; //! @brief 값의 크기입니다.
  int state;
  ErrorInterface error; //! @brief 에러가 발생했을 경우의 에러입니다.
};

//! @brief value를 Option으로 감싸서 반환합니다.
//! @param value Option으로 감쌀 값입니다. 꼭 `void*`로 타입캐스팅 후 전달해야 합니다
//! @param size value의 크기입니다. 일반적으로 `sizeof(value)`로 전달합니다.
//! @return value를 감싼 Option입니다.
Option some(void* value, size_t size);

//! @brief Option의 None 값을 반환합니다. 이 반환값은 값이 없다는 것을 의미합니다.
//! @return Option의 None값입니다.
Option none(void);
#endif