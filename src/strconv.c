#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <wchar.h>
#include "jaeyeong.h"

const string _const_strconv__base_digits = _SLIT("0123456789abcdefghijklmnopqrstuvwxyz");
const u32 _const_strconv__single_plus_zero = 0; // precomputed2
const u32 _const_strconv__single_minus_zero = 2147483648; // precomputed2
const u32 _const_strconv__single_plus_infinity = 2139095040; // precomputed2
const u32 _const_strconv__single_minus_infinity = 4286578688; // precomputed2
const u64 _const_strconv__double_plus_zero = 0U; // precomputed2
const u64 _const_strconv__double_minus_zero = 9223372036854775808U; // precomputed2
const u64 _const_strconv__double_plus_infinity = 9218868437227405312U; // precomputed2
const u64 _const_strconv__double_minus_infinity = 18442240474082181120U; // precomputed2
const u32 _const_strconv__c_ten = 10; // precomputed2
const u32 _const_strconv__mantbits32 = 23; // precomputed2
const u32 _const_strconv__expbits32 = 8; // precomputed2

string strconv__format_int(i64 n, int radix) {
  if (radix < 2 || radix > 36) {
    __panic( str_intp(2, _MOV((StrIntpData[]){{_SLIT("invalid radix: "), /*100 &int*/0x7, {.d_i32 = radix}}, {_SLIT(" . It should be => 2 and <= 36"), 0, { .d_c = 0 }}})));
    UNREACHABLE();
  }
  if (n == 0) return _SLIT("0");
  char buffer[65] = {0};
  char *ptr = &buffer[sizeof(buffer) / sizeof(char) - 1];
  *ptr = '\0';
  const char *digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  i64 num = n < 0 ? -n : n;
  do {
      *--ptr = digits[num % radix];
    num /= radix;
  } while (num > 0);
  if (n < 0) *--ptr = '-';
    string result = {.str = (byte*)strdup(ptr), .len = strlen(ptr), .is_lit = 0};
  return result;
}

string strconv__format_uint(u64 n, int radix) {
  if (radix < 2 || radix > 36) {
    __panic( str_intp(2, _MOV((StrIntpData[]){{_SLIT("invalid radix: "), /*100 &int*/0x7, {.d_i32 = radix}}, {_SLIT(" . It should be => 2 and <= 36"), 0, { .d_c = 0 }}})));
    UNREACHABLE();
  }
  if (n == 0) return _SLIT("0");
  char buffer[65] = {0}; // Buffer to hold the result string
  char *ptr = &buffer[sizeof(buffer) - 1]; // Start at the end of the buffer
  *ptr = '\0'; // Null-terminate the string
  const char *digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // Digits for conversion
  u64 num = n; // Work with the absolute value of n
  do {
    *--ptr = digits[num % radix]; // Get the next digit
    num /= radix; // Reduce the number
  } while (num > 0);
  // Create the result string
  string result = {.str = (byte*)strdup(ptr), .len = strlen(ptr), .is_lit = 0};
  return result;
}