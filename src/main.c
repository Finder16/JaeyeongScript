#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include "jaeyeong.h"

CompilerOptions options;
lexer* lex = _jNULL;
LinesCache* lines_cache = _jNULL;

//! @since 0.1.0
//! @date 2024-01-28 19:22:00 KST
//! @brief Prints the usage message and exits.
void usage(void) {
  eprintln(LANG(_S_JAEYEONG_USAGE/*, options.language*/));
  exit(1);
}

void parse_option(CompilerOptions* opt, int argc, const wchar_t* argv[]) {
  wchar_t* allowedExtensions[] = {L".jy", L".jaeyeong", NULL};
  for (int i = 1; i < argc; i++) {
    if (wcscmp(argv[i], L"--help") == 0) {
      opt->help = true;
    } else if (wcscmp(argv[i], L"--english") == 0) {
      opt->language = opt->language;
    } else if (wcscmp(argv[i], L"--korean") == 0) {
      opt->language = (opt->language != English) ? opt->language : Korean;
    } else if (wcscmp(argv[i], L"--ukrainian") == 0) {
      opt->language = (opt->language != English) ? opt->language : Ukrainian;
    } else {
      for (int j = 0; allowedExtensions[j] != NULL; j++) {
        if (endsWithW(argv[i], allowedExtensions[j])) {
          OptionApuaFile file = apua_file_open(wchar_to_string(argv[i]), _SLIT("r"));
          if (!file.is_some) {
            eprintln(format_string(LANG(JAEYEONG_ERR_FILEOPEN/*, opt->language*/), (char*)wchar_to_string(argv[i]).str));
            exit(1);
          }
          opt->input_file = (ApuaFile*)file.value;
          break;
        }
      }
    }
  }
}

char* read_file(FILE* file) {
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = (char*)jmalloc(length + 1);
    if (buffer == NULL) {
        printf("Cannot allocate memory for file contents\n");
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, length, file);
    buffer[length] = '\0';

    fclose(file);
    return buffer;
}

int wmain(int argc, wchar_t* argv[]/*, wchar_t envp[]*/) {
  builtin_init();
  options = default_options();
  parse_option(&options, argc, (const wchar_t**)argv);
  printf("%d\n", sizeof(void*));
  lines_cache = ((LinesCache*)memdup(&(LinesCache){.lines = new_map(sizeof(string), sizeof(Array_string), &map_hash_string, &map_eq_string, &map_clone_string, &map_free_string),}, sizeof(LinesCache))); // 3global
  if (options.input_file == NULL) usage();
  // read text from file
  print(_SLIT("//============================== HELPER C MACROS =============================*/\n// _SLIT0 is used as NULL string for literal arguments\n// `\"\" s` is used to enforce a string literal argument\n#define _SLIT0 (string){.str=(byteptr)(\"\"), .len=0, .is_lit=1}\n#define _SLIT(s) ((string){.str=(byteptr)(\"\" s), .len=(sizeof(s)-1), .is_lit=1})\n#define _SLEN(s, n) ((string){.str=(byteptr)(\"\" s), .len=n, .is_lit=1})\n\n// take the address of an rvalue\n#define ADDR(type, expr) (&((type[]){expr}[0]))\n\n// copy something to the heap\n#define HEAP(type, expr) ((type*)memdup((void*)&((type[]){expr}[0]), sizeof(type)))\n#define HEAP_noscan(type, expr) ((type*)memdup_noscan((void*)&((type[]){expr}[0]), sizeof(type)))\n\n#define _PUSH_MANY(arr, val, tmp, tmp_typ) {tmp_typ tmp = (val); array_push_many(arr, tmp.data, tmp.len);}\n#define _PUSH_MANY_noscan(arr, val, tmp, tmp_typ) {tmp_typ tmp = (val); array_push_many_noscan(arr, tmp.data, tmp.len);}\n\n// unsigned/signed comparisons\nstatic inline bool _us32_gt(uint32_t a, int32_t b) { return a > INT32_MAX || (int32_t)a > b; }\nstatic inline bool _us32_ge(uint32_t a, int32_t b) { return a >= INT32_MAX || (int32_t)a >= b; }\nstatic inline bool _us32_eq(uint32_t a, int32_t b) { return a <= INT32_MAX && (int32_t)a == b; }\nstatic inline bool _us32_ne(uint32_t a, int32_t b) { return a > INT32_MAX || (int32_t)a != b; }\nstatic inline bool _us32_le(uint32_t a, int32_t b) { return a <= INT32_MAX && (int32_t)a <= b; }\nstatic inline bool _us32_lt(uint32_t a, int32_t b) { return a < INT32_MAX && (int32_t)a < b; }\nstatic inline bool _us64_gt(uint64_t a, int64_t b) { return a > INT64_MAX || (int64_t)a > b; }\nstatic inline bool _us64_ge(uint64_t a, int64_t b) { return a >= INT64_MAX || (int64_t)a >= b; }\nstatic inline bool _us64_eq(uint64_t a, int64_t b) { return a <= INT64_MAX && (int64_t)a == b; }\nstatic inline bool _us64_ne(uint64_t a, int64_t b) { return a > INT64_MAX || (int64_t)a != b; }\nstatic inline bool _us64_le(uint64_t a, int64_t b) { return a <= INT64_MAX && (int64_t)a <= b; }\nstatic inline bool _us64_lt(uint64_t a, int64_t b) { return a < INT64_MAX && (int64_t)a < b; }\n\n#define EMPTY_VARG_INITIALIZATION 0\n#define EMPTY_STRUCT_DECLARATION\n#define EMPTY_STRUCT_INITIALIZATION\n// Due to a tcc bug, the length of an array needs to be specified, but GCC crashes if it is...\n#define EMPTY_ARRAY_OF_ELEMS(x,n) (x[])\n#define TCCSKIP(x) x\n\n#define __NOINLINE __attribute__((noinline))\n#define __IRQHANDLER __attribute__((interrupt))\n\n#define __V_architecture 0\n#if defined(__x86_64__) || defined(_M_AMD64)\n  #define __V_amd64  1\n  #undef __V_architecture\n  #define __V_architecture 1\n#endif\n\n#if defined(__aarch64__) || defined(__arm64__) || defined(_M_ARM64)\n  #define __V_arm64  1\n  #undef __V_architecture\n  #define __V_architecture 2\n#endif\n\n#if defined(__arm__) || defined(_M_ARM)\n  #define __V_arm32  1\n  #undef __V_architecture\n  #define __V_architecture 3\n#endif\n\n#if defined(__riscv) && __riscv_xlen == 64\n  #define __V_rv64  1\n  #undef __V_architecture\n  #define __V_architecture 4\n#endif\n\n#if defined(__riscv) && __riscv_xlen == 32\n  #define __V_rv32  1\n  #undef __V_architecture\n  #define __V_architecture 5\n#endif\n\n#if defined(__i386__) || defined(_M_IX86)\n  #define __V_x86    1\n  #undef __V_architecture\n  #define __V_architecture 6\n#endif\n\n// Using just __GNUC__ for detecting gcc, is not reliable because other compilers define it too:\n#ifdef __GNUC__\n  #define __V_GCC__\n#endif\n#ifdef __TINYC__\n  #undef __V_GCC__\n#endif\n#ifdef __cplusplus\n  #undef __V_GCC__\n#endif\n#ifdef __clang__\n  #undef __V_GCC__\n#endif\n\n#ifdef _MSC_VER\n  #undef __V_GCC__\n  #undef EMPTY_STRUCT_DECLARATION\n  #undef EMPTY_STRUCT_INITIALIZATION\n  #define EMPTY_STRUCT_DECLARATION unsigned char _dummy_pad\n  #define EMPTY_STRUCT_INITIALIZATION 0\n#endif\n\n#ifndef _WIN32\n  #if defined __has_include\n    #if __has_include (<execinfo.h>)\n      #include <execinfo.h>\n    #else\n      // On linux: int backtrace(void **__array, int __size);\n      // On BSD: size_t backtrace(void **, size_t);\n    #endif\n  #endif\n#endif\n\n#ifdef __TINYC__\n  #define _Atomic volatile\n  #undef EMPTY_STRUCT_DECLARATION\n  #undef EMPTY_STRUCT_INITIALIZATION\n  #define EMPTY_STRUCT_DECLARATION unsigned char _dummy_pad\n  #define EMPTY_STRUCT_INITIALIZATION 0\n  #undef EMPTY_ARRAY_OF_ELEMS\n  #define EMPTY_ARRAY_OF_ELEMS(x,n) (x[n])\n  #undef __NOINLINE\n  #undef __IRQHANDLER\n  // tcc does not support inlining at all\n  #define __NOINLINE\n  #define __IRQHANDLER\n  #undef TCCSKIP\n  #define TCCSKIP(x)\n  // #include <byteswap.h>\n  #ifndef _WIN32\n    int tcc_backtrace(const char *fmt, ...);\n  #endif\n#endif\n\n// Use __offsetof_ptr instead of __offset_of, when you *do* have a valid pointer, to avoid UB:\n#ifndef __offsetof_ptr\n  #define __offsetof_ptr(ptr,PTYPE,FIELDNAME) ((size_t)((byte *)&((PTYPE *)ptr)->FIELDNAME - (byte *)ptr))\n#endif\n\n// for __offset_of\n#ifndef __offsetof\n  #define __offsetof(PTYPE,FIELDNAME) ((size_t)(&((PTYPE *)0)->FIELDNAME))\n#endif\n\n#define OPTION_CAST(x) (x)\n\n#ifndef V64_PRINTFORMAT\n  #ifdef PRIx64\n    #define V64_PRINTFORMAT \"0x%\"PRIx64\n  #elif defined(__WIN32__)\n    #define V64_PRINTFORMAT \"0x%I64x\"\n  #elif defined(__linux__) && defined(__LP64__)\n    #define V64_PRINTFORMAT \"0x%lx\"\n  #else\n    #define V64_PRINTFORMAT \"0x%llx\"\n  #endif\n#endif\n\n#if defined(_WIN32) || defined(__CYGWIN__)\n  #define VV_EXPORTED_SYMBOL extern __declspec(dllexport)\n  #define VV_LOCAL_SYMBOL static\n#else\n  // 4 < gcc < 5 is used by some older Ubuntu LTS and Centos versions,\n  // and does not support __has_attribute(visibility) ...\n  #ifndef __has_attribute\n    #define __has_attribute(x) 0  // Compatibility with non-clang compilers.\n  #endif\n  #if (defined(__GNUC__) && (__GNUC__ >= 4)) || (defined(__clang__) && __has_attribute(visibility))\n    #ifdef ARM\n      #define VV_EXPORTED_SYMBOL  extern __attribute__((externally_visible,visibility(\"default\")))\n    #else\n      #define VV_EXPORTED_SYMBOL  extern __attribute__((visibility(\"default\")))\n    #endif\n    #if defined(__clang__) && (defined(_VUSECACHE) || defined(_VBUILDMODULE))\n      #define VV_LOCAL_SYMBOL static\n    #else\n      #define VV_LOCAL_SYMBOL  __attribute__ ((visibility (\"hidden\")))\n    #endif\n  #else\n    #define VV_EXPORTED_SYMBOL extern\n    #define VV_LOCAL_SYMBOL static\n  #endif\n#endif\n\n#ifdef __cplusplus\n  #include <utility>\n  #define _MOV std::move\n#else\n  #define _MOV\n#endif\n\n// tcc does not support has_include properly yet, turn it off completely\n#if defined(__TINYC__) && defined(__has_include)\n#undef __has_include\n#endif\n\n\n#if !defined(VWEAK)\n  #define VWEAK __attribute__((weak))\n  #ifdef _MSC_VER\n    #undef VWEAK\n    #define VWEAK\n  #endif\n  #if defined(__MINGW32__) || defined(__MINGW64__)\n    #undef VWEAK\n    #define VWEAK\n  #endif\n#endif\n\n#if !defined(VNORETURN)\n  #if defined(__TINYC__)\n    #include <stdnoreturn.h>\n    #define VNORETURN noreturn\n  #endif\n  # if !defined(__TINYC__) && defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L\n  #  define VNORETURN _Noreturn\n  # elif !defined(VNORETURN) && defined(__GNUC__) && __GNUC__ >= 2\n  #  define VNORETURN __attribute__((noreturn))\n  # endif\n  #ifndef VNORETURN\n    #define VNORETURN\n  #endif\n#endif\n\n#if !defined(VUNREACHABLE)\n  #if defined(__GNUC__) && !defined(__clang__)\n    #define V_GCC_VERSION  (__GNUC__ * 10000L + __GNUC_MINOR__ * 100L + __GNUC_PATCHLEVEL__)\n    #if (V_GCC_VERSION >= 40500L) && !defined(__TINYC__)\n      #define VUNREACHABLE()  do { __builtin_unreachable(); } while (0)\n    #endif\n  #endif\n  #if defined(__clang__) && defined(__has_builtin) && !defined(__TINYC__)\n    #if __has_builtin(__builtin_unreachable)\n      #define VUNREACHABLE()  do { __builtin_unreachable(); } while (0)\n    #endif\n  #endif\n  #ifndef VUNREACHABLE\n    #define VUNREACHABLE() do { } while (0)\n  #endif\n#endif\n\n//likely and unlikely macros\n#if defined(__GNUC__) || defined(__INTEL_COMPILER) || defined(__clang__)\n  #define _likely_(x)  __builtin_expect(x,1)\n  #define _unlikely_(x)  __builtin_expect(x,0)\n#else\n  #define _likely_(x) (x)\n  #define _unlikely_(x) (x)\n#endif\n\n\n// c_headers\ntypedef int (*qsort_callback_func)(const void*, const void*);\n#include <stdio.h>  // TODO remove all these includes, define all function signatures and types manually\n#include <stdlib.h>\n#include <string.h>\n\n#include <stdarg.h> // for va_list\n\n//================================== GLOBALS =================================*/\nint load_so(byteptr);\nvoid _vinit(int ___argc, voidptr ___argv);\nvoid _vcleanup(void);\n#define sigaction_size sizeof(sigaction);\n#define _ARR_LEN(a) ( (sizeof(a)) / (sizeof(a[0])) )\n\nvoid v_free(voidptr ptr);\n//voidptr memdup(voidptr src, isize sz);\n\n#if INTPTR_MAX == INT32_MAX\n  #define TARGET_IS_32BIT 1\n#elif INTPTR_MAX == INT64_MAX\n  #define TARGET_IS_64BIT 1\n#else\n  #error \"The environment is not 32 or 64-bit.\"\n#endif\n\n#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ || defined(__BYTE_ORDER) && __BYTE_ORDER == __BIG_ENDIAN || defined(__BIG_ENDIAN__) || defined(__ARMEB__) || defined(__THUMBEB__) || defined(__AARCH64EB__) || defined(_MIBSEB) || defined(__MIBSEB) || defined(__MIBSEB__)\n  #define TARGET_ORDER_IS_BIG 1\n#elif defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ || defined(__BYTE_ORDER) && __BYTE_ORDER == __LITTLE_ENDIAN || defined(__LITTLE_ENDIAN__) || defined(__ARMEL__) || defined(__THUMBEL__) || defined(__AARCH64EL__) || defined(_MIPSEL) || defined(__MIPSEL) || defined(__MIPSEL__) || defined(_M_AMD64) || defined(_M_X64) || defined(_M_IX86)\n  #define TARGET_ORDER_IS_LITTLE 1\n#else\n  #error \"Unknown architecture endianness\"\n#endif\n\n#ifndef _WIN32\n  #include <ctype.h>\n  #include <locale.h> // tolower\n  #include <sys/time.h>\n  #include <unistd.h> // sleep\n  extern char **environ;\n#endif\n\n#if defined(__CYGWIN__) && !defined(_WIN32)\n  #error Cygwin is not supported, please use MinGW or Visual Studio.\n#endif\n\n#if defined(__linux__) || defined(__APPLE__) || defined(__FreeBSD__) || defined(__DragonFly__) || defined(__vinix__) || defined(__serenity__) || defined(__sun) || defined(__plan9__)\n  #include <sys/types.h>\n  #include <sys/wait.h> // os__wait uses wait on nix\n#endif\n\n#ifdef __OpenBSD__\n  #include <sys/types.h>\n  #include <sys/resource.h>\n  #include <sys/wait.h> // os__wait uses wait on nix\n#endif\n\n#ifdef __NetBSD__\n  #include <sys/wait.h> // os__wait uses wait on nix\n#endif\n\n#ifdef _WIN32\n  #define WINVER 0x0600\n  #ifdef _WIN32_WINNT\n    #undef _WIN32_WINNT\n  #endif\n  #define _WIN32_WINNT 0x0600\n  #ifndef WIN32_FULL\n  #define WIN32_LEAN_AND_MEAN\n  #endif\n  #ifndef _UNICODE\n  #define _UNICODE\n  #endif\n  #ifndef UNICODE\n  #define UNICODE\n  #endif\n  #include <windows.h>\n\n  #include <io.h> // _waccess\n  #include <direct.h> // _wgetcwd\n  #ifdef V_USE_SIGNAL_H\n  #include <signal.h> // signal and SIGSEGV for segmentation fault handler\n  #endif\n\n  #ifdef _MSC_VER\n    // On MSVC these are the same (as long as /volatile:ms is passed)\n    #define _Atomic volatile\n\n    // MSVC cannot parse some things properly\n    #undef OPTION_CAST\n    #define OPTION_CAST(x)\n    #undef __NOINLINE\n    #undef __IRQHANDLER\n    #define __NOINLINE __declspec(noinline)\n    #define __IRQHANDLER __declspec(naked)\n\n    #include <dbghelp.h>\n    #pragma comment(lib, \"Dbghelp\")\n  #endif\n#else\n  #include <pthread.h>\n  #ifndef PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP\n    // musl does not have that\n    #define pthread_rwlockattr_setkind_np(a, b)\n  #endif\n#endif\n\n// g_live_info is used by live.info()\nstatic void* g_live_info = NULL;\n\n#if defined(__MINGW32__) || defined(__MINGW64__) || (defined(_WIN32) && defined(__TINYC__))\n  #undef PRId64\n  #undef PRIi64\n  #undef PRIo64\n  #undef PRIu64\n  #undef PRIx64\n  #undef PRIX64\n  #define PRId64 \"lld\"\n  #define PRIi64 \"lli\"\n  #define PRIo64 \"llo\"\n  #define PRIu64 \"llu\"\n  #define PRIx64 \"llx\"\n  #define PRIX64 \"llX\"\n#endif\n\n#ifdef _VFREESTANDING\n#undef _VFREESTANDING\n#endif\n"));
  char* file = read_file(options.input_file->file_ptr);
  lex = new_lexer(string_with_len((u8*)file, strlen(file)), string_clone(options.input_file->path));
  lexer_scan_all(lex);
  bulitin_cleanup();
  return 0;
}

void bulitin_cleanup(void) {
  free_options(&options);
}