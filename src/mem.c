#include "mem.h"

#include <assert.h>
#include <stdlib.h>

#include "error.h"

void* mem_alloc(size_t n, size_t size)
{
    void* ptr = calloc(n, size);
    assert(ptr && ERROR_ALLOC);

    return ptr;
}

void* mem_realloc(void* ptr, size_t n, size_t size)
{
    ptr = realloc(ptr, n * size);
    assert(ptr && ERROR_ALLOC);

    return ptr;
}

void mem_free_internal(void** ptr_ptr)
{
    assert(ptr_ptr && ERROR_INVALID("pointer to be freed"));
    assert(*ptr_ptr && ERROR_ZERO_POINTER_FREE);

    free(*ptr_ptr);
    *ptr_ptr = 0;
}
