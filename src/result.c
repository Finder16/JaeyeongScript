#include <stdio.h>
#include <stdlib.h>
#include "jaeyeong.h"

Result Ok(void* data, size_t size) {
  Result result;
  memset(&result, 0, sizeof(Result));
  result.data = data;
  result.size = size;
  result.is_err = false;
  return result; 
}

Result Err(ErrorInterface err) {
  Result result;
  memset(&result, 0, sizeof(Result));
  result.is_err = true;
  result.err = err;
  return result;
}