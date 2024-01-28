#ifndef __JAEYEONG_MEMORY_H__
#define __JAEYEONG_MEMORY_H__
#include <stdlib.h>
#include "apua.h"

DONOTUSE u8* prealloc_calloc(isize n);
DONOTUSE u8* prealloc_malloc(isize n);
//! @fn u8* jcalloc(isize n)
//! @brief Allocates memory of a given size and initializes it to zero.
//!
//! This function allocates memory of a given size and initializes it to zero.
//! If the requested size is less than 0, the function will panic and should never return.
//! If the requested size is 0, the function will return a null pointer.
//! In development mode, the function keeps track of the total allocated memory.
//!
//! @param n The size of the memory to allocate.
//! @return Returns a pointer to the allocated memory, or a null pointer if the requested size is 0.
u8* jcalloc(isize n);
//! @fn u8* jcalloc_noscan(isize n)
//! @brief Allocates memory of a given size.
//!
//! This function allocates memory of a given size. 
//! The allocated memory is not initialized.
//! In development mode, the function keeps track of the total allocated memory.
//!
//! @param n The size of the memory to allocate.
//! @return Returns a pointer to the allocated memory.
u8* jcalloc_noscan(isize n);
//! @fn UNSAFE u8* jmalloc(isize n)
//! @brief Allocates memory of a given size.
//!
//! This function allocates memory of a given size. The allocated memory is not initialized.
//! If the requested size is less than 0, the function will panic and should never return.
//! If the allocation fails, the function will also panic.
//! In development mode, the function keeps track of the total allocated memory and fills the allocated memory with a debug pattern.
//!
//! @param n The size of the memory to allocate.
//! @return Returns a pointer to the allocated memory.
UNSAFE u8* jmalloc(isize n);
//! @fn UNSAFE u8* malloc_noscan(isize n)
//! @brief Allocates memory of a given size.
//!
//! This function allocates memory of a given size. The allocated memory is not initialized.
//! If the requested size is less than 0, the function will panic and should never return.
//! If the allocation fails, the function will also panic.
//! In development mode, the function keeps track of the total allocated memory and fills the allocated memory with a debug pattern.
//!
//! @param n The size of the memory to allocate.
//! @return Returns a pointer to the allocated memory.
UNSAFE u8* malloc_noscan(isize n);
//! @fn UNSAFE u8* jrealloc(u8* b, isize n)
//! @brief Changes the size of the memory block pointed to by b.
//!
//! This function changes the size of the memory block pointed to by b to n bytes.
//! The contents will be unchanged to the minimum of the old and new sizes.
//! If the new size is larger, the value of the newly allocated portion is indeterminate.
//! If b is null, the call is equivalent to malloc(size).
//! If the function fails to allocate the requested block of memory, a panic occurs.
//!
//! @param b Pointer to the memory area to be reallocated.
//! @param n The new size of the memory block.
//! @return Returns a pointer to the newly allocated memory block.
UNSAFE u8* jrealloc(u8* b, isize n);
//! @fn UNSAFE u8* realloc_data(u8* old_data, int old_size, int new_size)
//! @brief Changes the size of the memory block pointed to by old_data.
//!
//! This function changes the size of the memory block pointed to by old_data to new_size bytes.
//! The contents will be unchanged to the minimum of the old and new sizes.
//! If the new size is larger, the value of the newly allocated portion is indeterminate.
//! If the function fails to allocate the requested block of memory, a panic occurs.
//!
//! @param old_data Pointer to the memory area to be reallocated.
//! @param old_size The old size of the memory block.
//! @param new_size The new size of the memory block.
//! @return Returns a pointer to the newly allocated memory block.
UNSAFE u8* realloc_data(u8* old_data, int old_size, int new_size);
//! @fn UNSAFE void* memdup(void* src, isize sz)
//! @brief Duplicates a block of memory.
//!
//! This function duplicates a block of memory of sz bytes pointed to by src.
//! The memory is allocated using jmalloc and can be freed with jfree.
//! If sz is 0, a unique pointer to an access protected, zero sized block is returned.
//!
//! @param src The pointer to the memory block to be duplicated.
//! @param sz The size of the memory block to be duplicated.
//! @return Returns a pointer to the duplicated block of memory.
UNSAFE void* memdup(void* src, isize sz);
//! @fn UNSAFE void* memdup_noscan(void* src, isize sz)
//! @brief Duplicates a block of memory.
//!
//! This function duplicates a block of memory of sz bytes pointed to by src.
//! The memory is allocated using malloc_noscan and can be freed with jfree.
//! If sz is 0, a unique pointer to an access protected, zero sized block is returned.
//!
//! @param src The pointer to the memory block to be duplicated.
//! @param sz The size of the memory block to be duplicated.
//! @return Returns a pointer to the duplicated block of memory.
UNSAFE void* memdup_noscan(void* src, isize sz);
//! @fn UNSAFE void jfree(void* ptr)
//! @brief Deallocates the memory previously allocated by a call to jmalloc or jrealloc.
//! The argument ptr is a pointer to a memory block previously allocated with jmalloc, jcalloc, or jrealloc. 
//! If ptr is NULL, no operation is performed.
//!
//! @param ptr The pointer to the memory block to be deallocated.
UNSAFE void jfree(void* ptr);

#endif /* __JAEYEONG_MEMORY_H__ */