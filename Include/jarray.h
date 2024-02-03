#ifndef __JAEYEONG_ARRAY_H__
#define __JAEYEONG_ARRAY_H__
#include <stdbool.h>
#include <string.h>
#include "apua.h"

//! @brief 배열의 동작을 제어하는 플래그를 나타내는 열거형입니다.
//! @details 이 열거형은 배열의 동작을 제어하는 플래그를 나타냅니다.
typedef enum {
  ArrayFlags__noslices = 1U, //! @brief 배열이 슬라이스를 지원하지 않음을 나타냅니다. u64(1) << 0
  ArrayFlags__noshrink = 2U, //! @brief 배열이 축소되지 않음을 나타냅니다. u64(1) << 1
  ArrayFlags__nogrow = 4U, //! @brief 배열이 확장되지 않음을 나타냅니다. u64(1) << 2
  ArrayFlags__nofree = 8U, //! @brief 배열이 해제되지 않음을 나타냅니다. u64(1) << 3
}  ArrayFlags;

//! @brief 배열을 나타내는 구조체입니다.
//! @details 이 구조체는 배열의 데이터와 메타데이터를 저장합니다.
struct array {
  void* data; //! @brief 배열의 데이터를 가리키는 포인터입니다.
  int offset; //! @brief 배열의 데이터가 시작하는 위치의 오프셋입니다.
  int len; //! @brief 배열의 길이입니다.
  int cap; //! @brief 배열의 용량입니다.
  ArrayFlags flags; //! @brief 배열의 플래그입니다.
  int element_size; //! @brief 배열의 각 요소의 크기입니다.
};

//! @brief 주어진 플래그가 모두 설정되어 있는지 확인하는 함수입니다.
//! @details 이 함수는 주어진 플래그(e)가 flag가 모두 설정되어 있는지 확인합니다.
//! @param e 확인할 플래그입니다.
//! @param flag 확인할 설정입니다.
//! @return 플래그가 모두 설정되어 있다면 true를, 그렇지 않다면 false를 반환합니다.
inline bool ArrayFlags_all(ArrayFlags* e, ArrayFlags flag) {
  return ((((int)(*e)) & (((int)(flag))))) == ((int)(flag));
}

//! @brief 주어진 플래그에 설정을 추가하는 함수입니다.
//! @details 이 함수는 주어진 플래그(e)에 flag를 설정합니다.
//! @param e 설정을 추가할 플래그입니다.
//! @param flag 추가할 설정입니다.
inline void ArrayFlags_set(ArrayFlags* e, ArrayFlags flag) {
  *e = ((ArrayFlags)((((int)(*e)) | (((int)(flag))))));
}

//! @brief 주어진 플래그에 모든 설정을 추가하는 함수입니다.
//! @details 이 함수는 주어진 플래그(e)에 모든 설정을 추가합니다.
//! @param e 설정을 추가할 플래그입니다.
inline void ArrayFlags_set_all(ArrayFlags* e) {
  *e = ((ArrayFlags)(0b1111));
}

//! @brief 새로운 배열을 생성하는 함수입니다.
//! 이 함수는 주어진 길이(mylen), 용량(cap), 요소 크기(``elm_size)를 사용하여 새로운 배열을 생성합니다.
//! 용량은 길이와 주어진 용량 중 더 큰 값으로 설정되며, 배열의 데이터는 jcalloc 함수를 사용하여 할당됩니다.
//! @param mylen 배열의 초기 길이입니다.
//! @param cap 배열의 초기 용량입니다.
//! @param elm_size 배열 요소의 크기입니다.
//! @return 새로 생성된 배열을 반환합니다.
array __new_array(int mylen, int cap, int elm_size);

//! @brief 기본값이 주어진 새로운 배열을 생성하는 함수입니다.
//! 이 함수는 주어진 길이(mylen), 용량(cap), 요소 크기(elm_size), 기본값(val)을 사용하여 새로운 배열을 생성합니다.
//! 용량은 길이와 주어진 용량 중 더 큰 값으로 설정되며, 배열의 데이터는 jmalloc 또는 jcalloc 함수를 사용하여 할당됩니다.
//! 기본값이 주어진 경우, 배열의 모든 요소를 기본값으로 설정합니다.
//! @param mylen 배열의 초기 길이입니다.
//! @param cap 배열의 초기 용량입니다.
//! @param elm_size 배열 요소의 크기입니다.
//! @param val 배열 요소의 기본값입니다.
//! @return 새로 생성된 배열을 반환합니다.
array __new_array_with_default(int mylen, int cap, int elm_size, void* val);

//! @brief 새로운 배열을 생성하는 함수입니다.
//! 이 함수는 주어진 길이(mylen), 용량(cap), 요소 크기(elm_size), 기본값(val)을 사용하여 새로운 배열을 생성합니다.
//! 용량은 길이와 주어진 용량 중 더 큰 값으로 설정되며, 배열의 데이터는 jmalloc 또는 jcalloc 함수를 사용하여 할당됩니다.
//! 기본값이 주어진 경우, 배열의 모든 요소를 기본값으로 설정합니다.
//! @param mylen 배열의 초기 길이입니다.
//! @param cap 배열의 초기 용량입니다.
//! @param elm_size 배열 요소의 크기입니다.
//! @param val 배열 요소의 기본값입니다.
//! @return 새로 생성된 배열을 반환합니다.
array __new_array_with_multi_default(int mylen, int cap, int elm_size, void* val);

//! @brief 배열 기본값이 주어진 새로운 배열을 생성하는 함수입니다.
//! 이 함수는 주어진 길이(mylen), 용량(cap), 요소 크기(elm_size), 기본값(val)을 사용하여 새로운 배열을 생성합니다.
//! 용량은 길이와 주어진 용량 중 더 큰 값으로 설정되며, 배열의 데이터는 jmalloc 함수를 사용하여 할당됩니다.
//! 기본값이 주어진 경우, 배열의 모든 요소를 기본값으로 설정합니다. 이 때, 각 요소의 기본값은 val에서 복제된 배열입니다.
//! @param mylen 배열의 초기 길이입니다.
//! @param cap 배열의 초기 용량입니다.
//! @param elm_size 배열 요소의 크기입니다.
//! @param val 배열 요소의 기본값입니다.
//! @param depth 복제할 배열의 깊이입니다.
//! @return 새로 생성된 배열을 반환합니다.
array __new_array_with_array_default(int mylen, int cap, int elm_size, array val, int depth);
// array __new_array_with_map_default(int mylen, int cap, int elm_size, map val);

//! @brief C 배열로부터 새로운 배열을 생성하는 함수입니다.
//! 이 함수는 주어진 길이(len), 용량(cap), 요소 크기(elm_size), C 배열(c_array)을 사용하여 새로운 배열을 생성합니다.
//! 용량은 길이와 주어진 용량 중 더 큰 값으로 설정되며, 배열의 데이터는 jcalloc 함수를 사용하여 할당됩니다.
//! 그리고 C 배열의 데이터를 새로 생성된 배열로 복사합니다.
//! @param len C 배열의 길이입니다.
//! @param cap 배열의 초기 용량입니다.
//! @param elm_size 배열 요소의 크기입니다.
//! @param c_array C 배열입니다.
//! @return 새로 생성된 배열을 반환합니다.
array new_array_from_c_array(int len, int cap, int elm_size, void* c_array);

//! @brief 메모리 할당 없이 C 배열로부터 새로운 배열을 생성하는 함수입니다.
//! 이 함수는 주어진 길이(len), 용량(cap), 요소 크기(elm_size), C 배열(c_array)을 사용하여 새로운 배열을 생성합니다.
//! 배열의 데이터는 C 배열을 직접 사용하며, 별도의 메모리 할당을 수행하지 않습니다.
//! @param len C 배열의 길이입니다.
//! @param cap 배열의 용량입니다.
//! @param elm_size 배열 요소의 크기입니다.
//! @param c_array C 배열입니다.
//! @return 새로 생성된 배열을 반환합니다.
array new_array_from_c_array_no_alloc(int len, int cap, int elm_size, void* c_array);

//! @brief 배열의 용량이 필요한 용량보다 크거나 같도록 보장하는 함수입니다.
//! 이 함수는 주어진 배열(a)와 필요한 용량(required)을 사용하여 배열의 용량을 증가시킵니다.
//! 만약 필요한 용량이 현재 배열의 용량보다 작거나 같다면, 함수는 아무런 동작을 수행하지 않습니다.
//! 만약 배열이 더 이상 성장할 수 없는 상태(.nogrow 플래그가 설정된 경우)라면, 함수는 패닉을 발생시킵니다.
//! @param a 용량을 보장할 배열입니다.
//! @param required 필요한 용량입니다.
void array_ensure_cap(array* a, int required);

//! @brief 주어진 배열을 반복하여 새로운 배열을 생성하는 함수입니다.
//! 이 함수는 주어진 배열(a)과 반복 횟수(count)를 사용하여 새로운 배열을 생성합니다.
//! 이 때, 배열의 각 요소는 깊이 0까지 복제됩니다.
//! @param a 반복할 배열입니다.
//! @param count 반복 횟수입니다.
//! @return 반복된 배열을 반환합니다.
array array_repeat(array a, int count);

//! @brief 주어진 깊이까지 배열을 반복하여 새로운 배열을 생성하는 함수입니다.
//! 이 함수는 주어진 배열(a), 반복 횟수(count), 깊이(depth)를 사용하여 새로운 배열을 생성합니다.
//! 만약 반복 횟수가 음수라면, 함수는 패닉을 발생시킵니다.
//! 새로운 배열의 크기는 원래 배열의 길이와 요소 크기, 그리고 반복 횟수의 곱으로 계산됩니다.
//! 만약 계산된 크기가 0이라면, 새로운 배열의 크기는 원래 배열의 요소 크기로 설정됩니다.
//! 새로운 배열의 데이터는 jcalloc 함수를 사용하여 할당되며, 원래 배열의 데이터를 깊이에 따라 복제하여 채웁니다.
//! @param a 반복할 배열입니다.
//! @param count 반복 횟수입니다.
//! @param depth 복제할 깊이입니다.
//! @return 반복된 배열을 반환합니다.
array array_repeat_to_depth(array a, int count, int depth);

//! @brief 배열의 특정 위치에 값을 삽입하는 함수입니다.
//! 이 함수는 주어진 배열(a), 인덱스(i), 값(val)을 사용하여 배열에 값을 삽입합니다.
//! 만약 인덱스가 배열의 범위를 벗어나면, 함수는 패닉을 발생시킵니다.
//! 만약 배열의 길이가 용량보다 크거나 같다면, 배열의 용량을 증가시킵니다.
//! 그리고 배열의 해당 위치에 값을 삽입하고, 배열의 길이를 1 증가시킵니다.
//! @param a 값을 삽입할 배열입니다.
//! @param i 삽입할 위치의 인덱스입니다.
//! @param val 삽입할 값입니다.
void array_insert(array* a, int i, void* val);

//! @brief 배열의 특정 위치에 여러 개의 값을 삽입하는 함수입니다.
//! 이 함수는 주어진 배열(a), 인덱스(i), 값(val), 크기(size)를 사용하여 배열에 여러 개의 값을 삽입합니다.
//! 만약 인덱스가 배열의 범위를 벗어나면, 함수는 패닉을 발생시킵니다.
//! 만약 배열의 길이가 용량보다 크거나 같다면, 배열의 용량을 증가시킵니다.
//! 그리고 배열의 해당 위치에 값을 삽입하고, 배열의 길이를 삽입된 값의 개수만큼 증가시킵니다.
//! @param a 값을 삽입할 배열입니다.
//! @param i 삽입할 위치의 인덱스입니다.
//! @param val 삽입할 값들입니다.
//! @param size 삽입할 값의 개수입니다.
void array_insert_many(array* a, int i, void* val, int size);

//! @brief 배열의 시작 위치에 값을 삽입하는 함수입니다.
//! 이 함수는 주어진 배열(a)와 값(val)을 사용하여 배열의 시작 위치에 값을 삽입합니다.
//! 이 함수는 array_insert 함수를 사용하여 값을 삽입합니다.
//! @param a 값을 삽입할 배열입니다.
//! @param val 삽입할 값입니다.
void array_prepend(array* a, void* val);

//! @brief 배열의 시작 위치에 여러 개의 값을 삽입하는 함수입니다.
//! 이 함수는 주어진 배열(a), 값(val), 크기(size)를 사용하여 배열의 시작 위치에 여러 개의 값을 삽입합니다.
//! 이 함수는 array_insert_many 함수를 사용하여 값을 삽입합니다.
//! @param a 값을 삽입할 배열입니다.
//! @param val 삽입할 값들입니다.
//! @param size 삽입할 값의 개수입니다.
void array_prepend_many(array* a, void* val, int size);

//! @brief 배열의 특정 위치의 값을 삭제하는 함수입니다.
//! 이 함수는 주어진 배열(a)와 인덱스(i)를 사용하여 배열의 특정 위치의 값을 삭제합니다.
//! 이 함수는 array_delete_many 함수를 사용하여 값을 삭제합니다.
//! @param a 값을 삭제할 배열입니다.
//! @param i 삭제할 위치의 인덱스입니다.
void array_delete(array* a, int i);

//! @brief 배열의 특정 위치에서 여러 개의 값을 삭제하는 함수입니다.
//! 이 함수는 주어진 배열(a), 인덱스(i), 크기(size)를 사용하여 배열에서 여러 개의 값을 삭제합니다.
//! 만약 인덱스가 배열의 범위를 벗어나면, 함수는 패닉을 발생시킵니다.
//! 만약 배열의 길이가 삭제할 값의 개수보다 작다면, 함수는 패닉을 발생시킵니다.
//! 그리고 배열에서 해당 위치의 값을 삭제하고, 배열의 길이를 삭제된 값의 개수만큼 감소시킵니다.
//! @param a 값을 삭제할 배열입니다.
//! @param i 삭제할 시작 위치의 인덱스입니다.
//! @param size 삭제할 값의 개수입니다.
void array_delete_many(array* a, int i, int size);

//! @brief 배열의 모든 값을 삭제하는 함수입니다.
//! 이 함수는 주어진 배열(a)의 모든 값을 삭제합니다.
//! 배열의 길이를 0으로 설정하여 모든 값을 삭제합니다.
//! @param a 값을 삭제할 배열입니다.
void array_clear(array* a);

//! @brief 배열의 모든 값을 0으로 초기화하는 함수입니다.
//! 이 함수는 주어진 배열(a)의 모든 값을 0으로 초기화합니다.
//! memset 함수를 사용하여 배열의 모든 값을 0으로 설정합니다.
//! @param a 값을 초기화할 배열입니다.
void array_reset(array* a);

//! @brief 배열의 특정 위치 이후의 모든 값을 삭제하는 함수입니다.
//! 이 함수는 주어진 배열(a)와 인덱스(index)를 사용하여 특정 위치 이후의 모든 값을 삭제합니다.
//! 만약 인덱스가 배열의 길이보다 작다면, 배열의 길이를 인덱스로 설정하여 해당 위치 이후의 모든 값을 삭제합니다.
//! @param a 값을 삭제할 배열입니다.
//! @param index 삭제할 시작 위치의 인덱스입니다.
void array_trim(array* a, int index);

//! @brief 배열의 앞에서 주어진 개수만큼의 요소를 삭제하는 함수입니다.
//! @details 이 함수는 주어진 배열(a)에서 앞에서 num 개의 요소를 삭제합니다.
//! 만약 num이 0 이하라면, 함수는 아무런 동작을 하지 않습니다.
//! 만약 num이 배열의 길이보다 크다면, 모든 요소를 삭제합니다.
//! @param a 요소를 삭제할 배열입니다.
//! @param num 삭제할 요소의 개수입니다.
void array_drop(array* a, int num);

//! @brief 배열의 주어진 위치의 요소를 안전하지 않게 가져오는 함수입니다.
//! @details 이 함수는 주어진 배열(a)에서 i 위치의 요소를 가져옵니다.
//! 이 함수는 인덱스의 유효성을 검사하지 않습니다.
//! @param a 요소를 가져올 배열입니다.
//! @param i 가져올 요소의 위치입니다.
//! @return 요소의 주소를 반환합니다.
void* array_get_unsafe(array a, int i);

//! @brief 배열의 주어진 위치의 요소를 가져오는 함수입니다.
//! @details 이 함수는 주어진 배열(a)에서 i 위치의 요소를 가져옵니다.
//! 만약 i가 배열의 범위를 벗어나면, 함수는 패닉을 발생시킵니다.
//! @param a 요소를 가져올 배열입니다.
//! @param i 가져올 요소의 위치입니다.
//! @return 요소의 주소를 반환합니다.
//! @exception 패닉을 발생시킵니다.
void* array_get(array a, int i);

//! @brief 배열의 주어진 위치의 요소를 안전하게 가져오는 함수입니다.
//! @details 이 함수는 주어진 배열(a)에서 i 위치의 요소를 가져옵니다.
//! 만약 i가 배열의 범위를 벗어나면, 함수는 NULL을 반환합니다.
//! @param a 요소를 가져올 배열입니다.
//! @param i 가져올 요소의 위치입니다.
//! @return 요소의 주소를 반환하거나, 인덱스가 범위를 벗어나면 NULL을 반환합니다.
void* array_get_with_check(array a, int i);

//! @brief 배열의 첫 번째 요소를 가져오는 함수입니다.
//! @details 이 함수는 주어진 배열(a)의 첫 번째 요소를 가져옵니다.
//! 만약 배열이 비어있다면, 함수는 패닉을 발생시킵니다.
//! @param a 요소를 가져올 배열입니다.
//! @return 첫 번째 요소의 주소를 반환합니다.
//! @exception 패닉을 발생시킵니다.
void* array_first(array a);

//! @brief 배열의 마지막 요소를 가져오는 함수입니다.
//! @details 이 함수는 주어진 배열(a)의 마지막 요소를 가져옵니다.
//! 만약 배열이 비어있다면, 함수는 패닉을 발생시킵니다.
//! @param a 요소를 가져올 배열입니다.
//! @return 마지막 요소의 주소를 반환합니다.
//! @throws 패닉을 발생시킵니다.
void* array_last(array a);

//! @brief 배열의 마지막 요소를 삭제하고, 그 요소를 반환하는 함수입니다.
//! @details 이 함수는 주어진 배열(a)의 마지막 요소를 삭제하고, 그 요소를 반환합니다.
//! 만약 배열이 비어있다면, 함수는 패닉을 발생시킵니다.
//! @param a 요소를 삭제하고 반환할 배열입니다.
//! @return 삭제된 마지막 요소의 주소를 반환합니다.
//! @throws 패닉을 발생시킵니다.
void* array_pop(array* a);

//! @brief 배열의 마지막 요소를 삭제하는 함수입니다.
//! @details 이 함수는 주어진 배열(a)의 마지막 요소를 삭제합니다.
//! 만약 배열이 비어있다면, 함수는 패닉을 발생시킵니다.
//! @param a 요소를 삭제할 배열입니다.
//! @throws 패닉을 발생시킵니다.
void array_delete_last(array* a);

//! @brief 배열의 주어진 범위를 슬라이스하는 함수입니다.
//! @details 이 함수는 주어진 배열(a)의 start 위치부터 end 위치까지의 요소를 슬라이스합니다.
//! 만약 end가 _const_max_int와 같다면, end는 배열의 길이로 설정됩니다.
//! 만약 start가 end보다 크거나, end가 배열의 길이보다 크거나, start가 0보다 작다면, 함수는 패닉을 발생시킵니다.
//! @param a 슬라이스할 배열입니다.
//! @param start 슬라이스의 시작 위치입니다.
//! @param _end 슬라이스의 끝 위치입니다.
//! @return 슬라이스된 배열을 반환합니다.
//! @throws 패닉을 발생시킵니다.
array array_slice(array a, int start, int _end);

//! @brief 배열의 주어진 범위를 슬라이스하는 함수입니다.
//! @details 이 함수는 주어진 배열(a)의 _start 위치부터 _end 위치까지의 요소를 슬라이스합니다.
//! 만약 _start 또는 _end가 0보다 작다면, 그 값은 배열의 길이에 더해져서 계산됩니다.
//! 만약 _end가 _const_max_int와 같다면, _end는 배열의 길이로 설정됩니다.
//! @param a 슬라이스할 배열입니다.
//! @param _start 슬라이스의 시작 위치입니다.
//! @param _end 슬라이스의 끝 위치입니다.
//! @return 슬라이스된 배열을 반환합니다.
array array_slice_ni(array a, int _start, int _end);

//! @brief 배열을 복제하는 함수입니다.
//! @details 이 함수는 주어진 배열(a)를 복제합니다.
//! 복제는 주어진 depth까지 이루어집니다.
//! @param a 복제할 배열입니다.
//! @param depth 복제할 깊이입니다.
//! @return 복제된 배열을 반환합니다.
array array_clone_static_to_depth(array a, int depth);

//! @brief 배열을 복제하는 함수입니다.
//! @details 이 함수는 주어진 배열(a)를 복제합니다.
//! 복제는 0 depth까지 이루어집니다.
//! @param a 복제할 배열입니다.
//! @return 복제된 배열을 반환합니다.
array array_clone(array* a);

//! @brief 배열을 주어진 깊이까지 복제하는 함수입니다.
//! @details 이 함수는 주어진 배열(a)를 복제합니다.
//! 복제는 주어진 depth까지 이루어집니다.
//! 만약 depth가 0보다 크고, 배열의 요소 크기가 array의 크기와 같으며, 배열의 길이가 0 이상이고, 배열의 용량이 배열의 길이 이상이라면, 배열의 각 요소를 복제합니다.
//! 그렇지 않다면, 배열의 데이터를 복제합니다.
//! @param a 복제할 배열입니다.
//! @param depth 복제할 깊이입니다.
//! @return 복제된 배열을 반환합니다.
array array_clone_to_depth(array* a, int depth);


//! @brief 배열의 특정 인덱스에 값을 설정하는 함수입니다.
//! @details 이 함수는 배열 `a`, 인덱스 `i`, 그리고 설정할 값 `val`을 입력으로 받아, `a`의 `i`번째 위치에 `val`을 설정합니다. 
//! 이 함수는 안전성 검사를 수행하지 않으므로, 인덱스가 배열의 범위를 벗어나지 않도록 주의해야 합니다.
//! @param a 값을 설정할 배열입니다.
//! @param i 설정할 값의 인덱스입니다.
//! @param val 설정할 값입니다.
inline void array_set_unsafe(array* a, int i, void* val) { memcpy(((u8*)(a->data)) + (u64)(((u64)(a->element_size)) * ((u64)(i))), val, a->element_size); }

//! @brief 배열의 주어진 위치에 값을 설정하는 함수입니다.
//! @details 이 함수는 주어진 배열(a)의 i 위치에 값을 설정합니다.
//! 만약 i가 0보다 작거나, i가 배열의 길이 이상이라면, 함수는 패닉을 발생시킵니다.
//! @param a 값을 설정할 배열입니다.
//! @param i 값을 설정할 위치입니다.
//! @param val 설정할 값입니다.
//! @throws 패닉을 발생시킵니다.
void array_set(array* a, int i, void* val);

//! @brief 배열의 끝에 값을 추가하는 함수입니다.
//! @details 이 함수는 주어진 배열(a)의 끝에 값을 추가합니다.
//! 만약 배열의 길이가 배열의 용량 이상이라면, 배열의 용량을 늘립니다.
//! @param a 값을 추가할 배열입니다.
//! @param val 추가할 값입니다.
void array_push(array* a, void* val);

//! @brief 배열의 끝에 여러 값을 추가하는 함수입니다.
//! @details 이 함수는 주어진 배열(a3)의 끝에 여러 값을 추가합니다.
//! 만약 size가 0 이하이거나, val이 null이라면, 함수는 아무 것도 하지 않고 반환합니다.
//! 만약 배열의 데이터가 val과 같고, 배열의 데이터가 null이 아니라면, 배열을 복제하고 복제된 배열의 데이터를 추가합니다.
//! 그렇지 않다면, val의 데이터를 추가합니다.
//! @param a3 값을 추가할 배열입니다.
//! @param val 추가할 값들입니다.
//! @param size 추가할 값들의 개수입니다.
void array_push_many(array* a3, void* val, int size);

//! @brief 배열을 해제하는 함수입니다.
//! @details 이 함수는 주어진 배열(a)를 해제합니다.
//! 만약 배열의 플래그에 ArrayFlags__nofree가 설정되어 있다면, 함수는 패닉을 발생시킵니다.
//! @param a 해제할 배열입니다.
//! @throws 패닉을 발생시킵니다.
void array_free(array* a);

//! @brief 주어진 배열의 문자열들을 주어진 구분자로 결합하는 함수입니다.
//! @details 이 함수는 주어진 배열(a)의 문자열들을 주어진 구분자(sep)로 결합하여 새로운 문자열을 생성합니다.
//! 만약 배열의 길이가 0이라면, 빈 문자열을 반환합니다.
//! 그렇지 않다면, 배열의 각 문자열과 구분자의 길이를 합한 길이를 가진 새로운 문자열을 생성합니다.
//! 이후, 배열의 각 문자열을 새로운 문자열에 복사하고, 각 문자열 사이에 구분자를 추가합니다.
//! 마지막으로, 새로운 문자열의 끝에 null 문자를 추가합니다.
//! @param a 결합할 문자열들이 있는 배열입니다.
//! @param sep 문자열들 사이에 추가할 구분자입니다.
//! @return 결합된 문자열을 반환합니다.
string Array_string_join(Array_string a, string sep);

//! @brief 주어진 플래그가 설정되어 있는지 확인하는 함수입니다.
//! @details 이 함수는 주어진 플래그(e)가 flag가 설정되어 있는지 확인합니다.
//! @param e 확인할 플래그입니다.
//! @param flag 확인할 설정입니다.
//! @return 플래그가 설정되어 있다면 true를, 그렇지 않다면 false를 반환합니다.
inline bool ArrayFlags_has(ArrayFlags* e, ArrayFlags flag) { return ((((int)(*e)) & (((int)(flag))))) != 0; }
#endif /* __JAEYEONG_ARRAY_H__ */