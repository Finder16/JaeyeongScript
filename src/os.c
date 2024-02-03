#include <stdio.h>
#include <stdlib.h>
#include "jaeyeong.h"

ResultString os_readfile(string path) {
  bool os__read_file_defer_0 = false;
  FILE* fp;
  string mode = _SLIT("rb");
  ResultFilePtr _t1 = os_fopen(path, mode);
  if (_t1.is_err) {
    ResultString r;
    memcpy(&r, &_t1, sizeof(Result));
    return r;
  }
  fp =  (*(FILE**)_t1.data);
  os__read_file_defer_0 = true;
  ResultInt _t3 = os_find_cfile_size(fp);
  if (_t3.is_err) {
    if (os__read_file_defer_0) fclose(fp);
    ResultString r;
    memcpy(&r, &_t3, sizeof(Result));
    return r;
  }
  int allocate =  (*(int*)_t3.data);
  if (allocate == 0) {
    ResultStringsBuilder _t5 = os_slurp_file_in_builder(fp);
    if (_t5.is_err) {
      if (os__read_file_defer_0) fclose(fp);
      ResultString r;
      memcpy(&r, &_t5, sizeof(Result));
      return r;
    }
    strings__Builder sb =  (*(strings__Builder*)_t5.data);
    string res = strings__Builder_str(&sb);
    strings__Builder_free(&sb);
    ResultString _t7 = Ok(&(string[]) { res }, sizeof(string));
    if (os__read_file_defer_0) fclose(fp);
    return _t7;
  }
  u8* str = malloc_noscan((int)(allocate + 1));
  int nelements = ((int)(fread(str, 1, allocate, fp)));
  int is_eof = ((int)(feof(fp)));
  int is_error = ((int)(ferror(fp)));
  if (is_eof == 0 && is_error != 0) {
    jfree(str);
    ResultString _t8 = Err(__error(_SLIT("fread failed")));
    if (os__read_file_defer_0) fclose(fp);
    return _t8;
  }
  str[nelements] = 0;
  if (nelements == 0) {
    ResultString _t9 = Ok(&(string[]) { ((string){.str = str, .len = (strlen(((char*)(str))))}) }, sizeof(string));
    if (os__read_file_defer_0) fclose(fp);
    return _t9;
  }
  ResultString _t10 = Ok(&(string[]) { ((string){.str = str, .len = nelements, .is_lit = 0}) }, sizeof(string));
  if (os__read_file_defer_0) fclose(fp);
  return _t10;
}

ResultFilePtr os_fopen(string path, string mode) {
  if (path.len == 0) return (ResultFilePtr)Err(__error(_SLIT("empty path")));
  void* fp = ((void*)0);
  fp = _wfopen(string_to_wide(path), string_to_wide(mode));
  if (fp == ((void*)0)) return (ResultFilePtr)Err(__error(_SLIT("failed to open file")));
  ResultFilePtr r = Ok(&(FILE*[]) { fp }, sizeof(FILE*));
  return r;
}

ResultInt os_find_cfile_size(FILE* fp) {
  int cseek = fseek(fp, 0, SEEK_END);
  isize raw_fsize = ftell(fp);
  if (raw_fsize != 0 && cseek != 0) return (ResultInt)Err(__error(_SLIT("fseek failed")));
  if (cseek != 0 && raw_fsize < 0) return (ResultInt)Err(__error(_SLIT("ftell failed")));
  int len = ((int)(raw_fsize));
  if (((i64)(len)) < raw_fsize) return (ResultInt)Err(__error(str_intp(3, _MOV((StrIntpData[]){{_SLIT("int("), /*100 &isize*/0x9, {.d_i64 = raw_fsize}}, {_SLIT(") cast results in "), /*100 &int*/0x7, {.d_i32 = len}}, {_SLIT0, 0, { .d_c = 0 }}}))));
  rewind(fp);
  ResultInt r = Ok(&(int[]) { len }, sizeof(int));
  return r;
}

ResultStringsBuilder os_slurp_file_in_builder(FILE* fp) {
  ArrFixedu8_4096 buf = {0};
  strings__Builder sb = strings__new_builder(4096);
  for (;;) {
    ResultInt _t1 = os_fread(&buf[0], 1, 4096, fp);
    if (_t1.is_err) {
      ErrorInterface err = _t1.err;
      if (err._typ == ERRINTFACE_T_MESGERR) {
        MessageError* x = err._MessageError;
        if (x->code == ETYPE_EOF) {
          break;
        }
      }
      strings__Builder_free(&sb);
      return (ResultStringsBuilder)Err(err);
    }
    int read_bytes =  (*(int*)_t1.data);
    strings__Builder_write_ptr(&sb, &buf[0], read_bytes);
  }
  ResultStringsBuilder _t3 = Ok(&(strings__Builder[]) { sb }, sizeof(strings__Builder));
  return _t3;
}

ResultInt os_fread(void* ptr, int item_size, int items, FILE* stream) {
  int nbytes = ((int)(fread(ptr, item_size, items, stream)));
  if (nbytes <= 0) {
    // return (_result_int){ .is_error=true, .err=I_os__Eof_to_Interface_IError(((os__Eof*)memdup(&(os__Eof){.Error = ((Error){EMPTY_STRUCT_INITIALIZATION}),}, sizeof(os__Eof)))), .data={EMPTY_STRUCT_INITIALIZATION} };
    if (feof(stream) != 0) return (ResultInt)Err(jerror(_SLIT("EOF"), ETYPE_EOF));
    if (ferror(stream) != 0) return (ResultInt)Err(__error(_SLIT("file read error")));
  }
  ResultInt _t3 = Ok(&(int[]) { nbytes }, sizeof(int));
  return _t3;
}