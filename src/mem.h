#pragma once

#include "common.h"

void* mem_alloc(size_t n, size_t size);

void* mem_realloc(void* ptr, size_t n, size_t size);

void mem_free(void** ptr_ptr);

#define mem_free(ptr_ptr) mem_free((void**) ptr_ptr);
