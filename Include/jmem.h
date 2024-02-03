#ifndef __JAEYEONG_MEMORY_H__
#define __JAEYEONG_MEMORY_H__
#include <stdlib.h>
#include "apua.h"

DONOTUSE u8* prealloc_calloc(isize n);
DONOTUSE u8* prealloc_malloc(isize n);

//! @brief 메모리를 할당하고, 그 결과를 `u8*` 형태로 반환하는 함수입니다.
//! @details 이 함수는 주어진 크기의 메모리를 할당하고, 그 결과를 `u8*` 형태로 반환합니다. 
//! 메모리 할당이 성공하면 할당된 메모리의 포인터를 반환하고, 실패하면 NULL을 반환합니다.
//! `_JAEYEONG_DEV_TRACE_CALLOC` 또는 `_JAEYEONG_DEV_TRACE_MEMORY`가 정의된 경우, 할당된 메모리의 크기와 총 메모리 사용량을 출력합니다.
//! `_JAEYEONG_PREALLOC`이 정의된 경우, `prealloc_calloc` 함수를 사용하여 메모리를 할당합니다.
//! @param n 할당할 메모리의 크기입니다. 이 값이 0인 경우, NULL을 반환합니다. 이 값이 음수인 경우, 프로그램을 종료합니다.
//! @return 할당된 메모리의 포인터를 나타내는 `u8*`입니다. 메모리 할당이 실패하면 NULL을 반환합니다.
u8* jcalloc(isize n);

//! @brief 메모리를 할당하고, 그 결과를 `u8*` 형태로 반환하는 함수입니다.
//! @details 이 함수는 주어진 크기의 메모리를 할당하고, 그 결과를 `u8*` 형태로 반환합니다. 
//! 메모리 할당이 성공하면 할당된 메모리의 포인터를 반환하고, 실패하면 NULL을 반환합니다.
//! `_JAEYEONG_DEV_TRACE_CALLOC` 또는 `_JAEYEONG_DEV_TRACE_MEMORY`가 정의된 경우, 할당된 메모리의 크기와 총 메모리 사용량을 출력합니다.
//! `_JAEYEONG_PREALLOC`이 정의된 경우, `prealloc_calloc` 함수를 사용하여 메모리를 할당합니다. 그렇지 않은 경우, `jcalloc` 함수를 사용하여 메모리를 할당합니다.
//! @param n 할당할 메모리의 크기입니다. 
//! @return 할당된 메모리의 포인터를 나타내는 `u8*`입니다. 메모리 할당이 실패하면 NULL을 반환합니다.
u8* jcalloc_noscan(isize n);

//! @brief 메모리를 할당하고, 그 결과를 `u8*` 형태로 반환하는 함수입니다.
//! @details 이 함수는 주어진 크기의 메모리를 할당하고, 그 결과를 `u8*` 형태로 반환합니다. 
//! 메모리 할당이 성공하면 할당된 메모리의 포인터를 반환하고, 실패하면 프로그램을 종료합니다.
//! `_JAEYEONG_DEV_TRACE_MALLOC` 또는 `_JAEYEONG_DEV_TRACE_MEMORY`가 정의된 경우, 할당된 메모리의 크기와 총 메모리 사용량을 출력합니다.
//! `_JAEYEONG_PREALLOC`이 정의된 경우, `prealloc_malloc` 함수를 사용하여 메모리를 할당합니다. 그렇지 않은 경우, `malloc` 함수를 사용하여 메모리를 할당합니다.
//! `_JAEYEONG_DEBUG_MALLOC`이 정의된 경우, 할당된 메모리를 0x4D로 채웁니다.
//! @param n 할당할 메모리의 크기입니다. 이 값이 음수인 경우, 프로그램을 종료합니다.
//! @return 할당된 메모리의 포인터를 나타내는 `u8*`입니다.
UNSAFE u8* jmalloc(isize n);

//! @brief 메모리를 할당하고, 그 결과를 `u8*` 형태로 반환하는 함수입니다.
//! @details 이 함수는 주어진 크기의 메모리를 할당하고, 그 결과를 `u8*` 형태로 반환합니다. 
//! 메모리 할당이 성공하면 할당된 메모리의 포인터를 반환하고, 실패하면 프로그램을 종료합니다.
//! `_JAEYEONG_DEV_TRACE_MALLOC` 또는 `_JAEYEONG_DEV_TRACE_MEMORY`가 정의된 경우, 할당된 메모리의 크기와 총 메모리 사용량을 출력합니다.
//! `_JAEYEONG_PREALLOC`이 정의된 경우, `prealloc_malloc` 함수를 사용하여 메모리를 할당합니다. 그렇지 않은 경우, `malloc` 함수를 사용하여 메모리를 할당합니다.
//! `_JAEYEONG_DEBUG_MALLOC`이 정의된 경우, 할당된 메모리를 0x4D로 채웁니다.
//! @param n 할당할 메모리의 크기입니다. 이 값이 음수인 경우, 프로그램을 종료합니다.
//! @return 할당된 메모리의 포인터를 나타내는 `u8*`입니다.
UNSAFE u8* malloc_noscan(isize n);

//! @brief 메모리를 재할당하고, 그 결과를 `u8*` 형태로 반환하는 함수입니다.
//! @details 이 함수는 주어진 포인터가 가리키는 메모리를 주어진 크기로 재할당하고, 그 결과를 `u8*` 형태로 반환합니다. 
//! 메모리 재할당이 성공하면 재할당된 메모리의 포인터를 반환하고, 실패하면 프로그램을 종료합니다.
//! `_JAEYEONG_DEV_TRACE_REALLOC` 또는 `_JAEYEONG_DEV_TRACE_MEMORY`가 정의된 경우, 재할당된 메모리의 크기를 출력합니다.
//! `_JAEYEONG_PREALLOC`이 정의된 경우, `jmalloc` 함수를 사용하여 메모리를 할당하고, 원래 메모리의 내용을 새 메모리로 복사합니다. 그렇지 않은 경우, `realloc` 함수를 사용하여 메모리를 재할당합니다.
//! @param b 재할당할 메모리의 원래 포인터입니다.
//! @param n 재할당할 메모리의 크기입니다.
//! @return 재할당된 메모리의 포인터를 나타내는 `u8*`입니다.
UNSAFE u8* jrealloc(u8* b, isize n);

//! @brief 주어진 포인터가 가리키는 메모리 블록의 크기를 재조정하고, 그 결과를 `u8*` 형태로 반환하는 함수입니다.
//! @details 이 함수는 주어진 포인터가 가리키는 메모리 블록의 크기를 재조정하고, 그 결과를 `u8*` 형태로 반환합니다. 
//! `_JAEYEONG_DEV_TRACE_REALLOC` 또는 `_JAEYEONG_DEV_TRACE_MEMORY`가 정의된 경우, 재조정된 메모리의 크기를 출력합니다.
//! `_JAEYEONG_PREALLOC`이 정의된 경우, `prealloc_realloc` 함수를 사용하여 메모리를 재조정합니다.
//! `CUSTOM_DEFINE_debug_realloc`이 정의된 경우, `jmalloc` 함수를 사용하여 새 메모리를 할당하고, 원래 메모리의 내용을 새 메모리로 복사한 후, 원래 메모리를 해제합니다.
//! 위의 조건들 중 어느 것도 만족하지 않는 경우, `realloc` 함수를 사용하여 메모리를 재조정합니다. 만약 `realloc` 함수가 실패하면, 프로그램은 패닉 상태로 전환되고, 이 함수는 도달할 수 없는 상태가 됩니다.
//! @param old_data 재조정할 메모리의 원래 포인터입니다.
//! @param old_size 재조정할 메모리의 원래 크기입니다.
//! @param new_size 재조정할 메모리의 새 크기입니다.
//! @return 재조정된 메모리의 포인터를 나타내는 `u8*`입니다.
UNSAFE u8* realloc_data(u8* old_data, int old_size, int new_size);

//! @brief 주어진 메모리 블록을 복사하고, 그 결과를 `void*` 형태로 반환하는 함수입니다.
//! @details 이 함수는 주어진 포인터가 가리키는 메모리 블록을 복사하고, 그 결과를 `void*` 형태로 반환합니다. 
//! 복사할 메모리의 크기가 0인 경우, `jcalloc` 함수를 사용하여 1바이트의 메모리를 할당합니다. 그렇지 않은 경우, `jmalloc` 함수를 사용하여 메모리를 할당하고, `memcpy` 함수를 사용하여 메모리를 복사합니다.
//! @param src 복사할 메모리의 원래 포인터입니다.
//! @param sz 복사할 메모리의 크기입니다.
//! @return 복사된 메모리의 포인터를 나타내는 `void*`입니다.
UNSAFE void* memdup(void* src, isize sz);

//! @brief 주어진 메모리 블록을 복사하고, 그 결과를 `void*` 형태로 반환하는 함수입니다. 이 함수는 스캔을 수행하지 않습니다.
//! @details 이 함수는 주어진 포인터가 가리키는 메모리 블록을 복사하고, 그 결과를 `void*` 형태로 반환합니다. 
//! 복사할 메모리의 크기가 0인 경우, `jcalloc_noscan` 함수를 사용하여 1바이트의 메모리를 할당합니다. 그렇지 않은 경우, `malloc_noscan` 함수를 사용하여 메모리를 할당하고, `memcpy` 함수를 사용하여 메모리를 복사합니다.
//! @param src 복사할 메모리의 원래 포인터입니다.
//! @param sz 복사할 메모리의 크기입니다.
//! @return 복사된 메모리의 포인터를 나타내는 `void*`입니다.
UNSAFE void* memdup_noscan(void* src, isize sz);

//! @brief 주어진 포인터가 가리키는 메모리 블록을 해제하는 함수입니다.
//! @details 이 함수는 주어진 포인터가 가리키는 메모리 블록을 해제합니다. 
//! `_JAEYEONG_PREALLOC`이 정의된 경우, 이 함수는 아무 것도 하지 않습니다. 그렇지 않은 경우, `free` 함수를 사용하여 메모리를 해제합니다.
//! @param ptr 해제할 메모리의 포인터입니다.
UNSAFE void jfree(void* ptr);
#endif /* __JAEYEONG_MEMORY_H__ */