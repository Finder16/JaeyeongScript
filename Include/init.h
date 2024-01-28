#ifndef __JAEYEONG_INIT_H__
#define __JAEYEONG_INIT_H__
#include "apua.h"

#define _const_std_output_handle -11
#define _const_std_error_handle -12
#define _const_enable_processed_output 1
#define _const_enable_wrap_at_eol_output 2
#define _const_cp_utf8 65001
#define _const_evable_virtual_terminal_processing 4

int is_terminal(int fd);
void restore_codepage(void);
void builtin_init(void);
#endif