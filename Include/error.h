#ifndef __JAEYEONG_ERROR_H__
#define __JAEYEONG_ERROR_H__
#include "apua.h"

void panic(string s, char* file, int line, char* func);
#define __panic(s) panic(s, __FILE__, __LINE__, (char*)__func__)
#endif /* __JAEYEONG_ERROR_H__ */