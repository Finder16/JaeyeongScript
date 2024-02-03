#ifndef __JAEYEONG_OS_H__
#define __JAEYEONG_OS_H__
#include "apua.h"
#include "jstrings.h"

ResultString os_readfile(string path);
ResultFilePtr os_fopen(string path, string mode);
ResultInt os_find_cfile_size(FILE* fp);
ResultStringsBuilder os_slurp_file_in_builder(FILE* fp);
ResultInt os_fread(void* ptr, int item_size, int items, FILE* stream);
#endif /* __JAEYEONG_OS_H__ */