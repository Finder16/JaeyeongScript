#ifndef __JAEYEONG_RESULT_H__
#define __JAEYEONG_RESULT_H__
#include "apua.h"
#include "error.h"

struct Result {
  void* data;
  size_t size;
  bool is_err;
  ErrorInterface err;
};

Result Ok(void* data, size_t size);

Result Err(ErrorInterface err);

#endif /* __JAEYEONG_RESULT_H__ */