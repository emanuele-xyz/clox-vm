#pragma once

#include "common.h"

#define mem_free(ptr_ptr) mem_free_internal((void**) ptr_ptr)

void* mem_alloc(size_t n, size_t size);

void* mem_realloc(void* ptr, size_t n, size_t size);

void mem_free_internal(void** ptr_ptr);
