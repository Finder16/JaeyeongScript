#ifndef __JAEYEONG_UTILS_H__
#define __JAEYEONG_UTILS_H__
#include "apua.h"
#include "jstrings.h"
#include "jarray.h"
#include "map.h"
#include "error.h"

struct LinesCache {
  Map_string_Array_string lines;
};

Array_string cached_file_to_sourcelines(string path);

ResultString util_read_file(string path);

string util_color(string kind, string msg);

string util_skip_bom(string file_content);
#endif /* __JAEYEONG_UTILS_H__ */