#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <stdint.h>
#include <float.h>
#include "jaeyeong.h"

i8Option check_i8_range(string s) {
  char* endptr;
  errno = 0;
  long val = strtol(s.str, &endptr, 10);
  if ((errno == ERANGE && (val == LLONG_MAX || val == LLONG_MIN)) || (errno != 0 && val == 0)) return none();
  else if (endptr == s.str) return none();
  else return (val >= INT8_MIN && val <= INT8_MAX) ? some((void*)&val, sizeof(i8)) : none();
}

i16Option check_i16_range(string s) {
  char* endptr;
  errno = 0;
  long val = strtol(s.str, &endptr, 10);
  if ((errno == ERANGE && (val == LLONG_MAX || val == LLONG_MIN)) || (errno != 0 && val == 0)) return none();
  else if (endptr == s.str) return none();
  else return (val >= INT16_MIN && val <= INT16_MAX) ? some((void*)&val, sizeof(i16)) : none();
}

i32Option check_i32_range(string s) {
  char* endptr;
  errno = 0;
  long val = strtol(s.str, &endptr, 10);
  if ((errno == ERANGE && (val == LLONG_MAX || val == LLONG_MIN)) || (errno != 0 && val == 0)) return none();
  else if (endptr == s.str) return none();
  else return (val >= INT32_MIN && val <= INT32_MAX) ? some((void*)&val, sizeof(i32)) : none();
}

i64Option check_i64_range(string s) {
  char* endptr;
  errno = 0;
  long long val = strtoll(s.str, &endptr, 10);
  if ((errno == ERANGE && (val == LLONG_MAX || val == LLONG_MIN)) || (errno != 0 && val == 0)) return none();
  else if (endptr == s.str) return none();
  else return (val >= INT64_MIN && val <= INT64_MAX) ? some((void*)&val, sizeof(i64)) : none();
}

isizeOption check_isize_range(string s) {
  char* endptr;
  errno = 0;
  long long val = strtoll(s.str, &endptr, 10);
  if ((errno == ERANGE && (val == LLONG_MAX || val == LLONG_MIN)) || (errno != 0 && val == 0)) return none();
  else if (endptr == s.str) return none();
  else return (val >= INTPTR_MIN && val <= INTPTR_MAX) ? some((void*)&val, sizeof(isize)) : none();
}

u8Option check_u8_range(string s) {
  char* endptr;
  errno = 0;
  long val = strtol(s.str, &endptr, 10);
  if ((errno == ERANGE && (val == LLONG_MAX || val == LLONG_MIN)) || (errno != 0 && val == 0)) return none();
  else if (endptr == s.str) return none();
  else return (val >= 0 && val <= UINT8_MAX) ? some((void*)&val, sizeof(u8)) : none();
}

u16Option check_u16_range(string s) {
  char* endptr;
  errno = 0;
  long val = strtol(s.str, &endptr, 10);
  if ((errno == ERANGE && (val == LLONG_MAX || val == LLONG_MIN)) || (errno != 0 && val == 0)) return none();
  else if (endptr == s.str) return none();
  else return (val >= 0 && val <= UINT16_MAX) ? some((void*)&val, sizeof(u16)) : none();
}

u32Option check_u32_range(string s) {
  char* endptr;
  errno = 0;
  long val = strtol(s.str, &endptr, 10);
  if ((errno == ERANGE && (val == LLONG_MAX || val == LLONG_MIN)) || (errno != 0 && val == 0)) return none();
  else if (endptr == s.str) return none();
  else return (val >= 0 && val <= UINT32_MAX) ? some((void*)&val, sizeof(u32)) : none();
}

u64Option check_u64_range(string s) {
  char* endptr;
  errno = 0;
  long long val = strtoll(s.str, &endptr, 10);
  if ((errno == ERANGE && (val == LLONG_MAX || val == LLONG_MIN)) || (errno != 0 && val == 0)) return none();
  else if (endptr == s.str) return none();
  else return (val >= 0 && val <= UINT64_MAX) ? some((void*)&val, sizeof(u64)) : none();
}

usizeOption check_usize_range(string s) {
  char* endptr;
  errno = 0;
  long long val = strtoll(s.str, &endptr, 10);
  if ((errno == ERANGE && (val == LLONG_MAX || val == LLONG_MIN)) || (errno != 0 && val == 0)) return none(); 
  else if (endptr == s.str) return none();
  else return (val >= 0 && val <= UINTPTR_MAX) ? some((void*)&val, sizeof(usize)) : none();
}

f32Option check_f32_range(string s) {
  char* endptr;
  errno = 0;
  float val = strtof(s.str, &endptr);
  if ((errno == ERANGE && (val == FLT_MAX || val == FLT_MIN)) || (errno != 0 && val == 0)) return none(); 
  else if (endptr == s.str) return none();
  else return some((void*)&val, sizeof(f32));
}

f64Option check_f64_range(string s) {
  char* endptr;
  errno = 0;
  double val = strtod(s.str, &endptr);
  if ((errno == ERANGE && (val == DBL_MAX || val == DBL_MIN)) || (errno != 0 && val == 0)) return none(); 
  else if (endptr == s.str) return none();
  else return some((void*)&val, sizeof(f64));
}