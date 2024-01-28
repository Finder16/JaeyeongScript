#ifndef __JAEYEONG_LANGUAGE_H__
#define __JAEYEONG_LANGUAGE_H__
#include "jstrings.h"

enum Language {
  English,
  Ukrainian,
  Korean
};

#define LANG(x, y) (y == English ? _SLIT(x) : y == Ukrainian ? _SLIT(x ## _UA) : _SLIT(x ## _KR))
#endif