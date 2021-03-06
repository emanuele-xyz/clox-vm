#include "chunk.h"

#include <assert.h>

#include "mem.h"

#define CHUNK_DEFAULT_CAPACITY 8
#define CHUNK_GROW_FACTOR 2

Chunk* chunk_new(void)
{
    Chunk* chunk = mem_alloc(1, sizeof(*chunk));

    chunk->capacity = CHUNK_DEFAULT_CAPACITY;
    chunk->code = mem_alloc(chunk->capacity, sizeof(*chunk->code));
    chunk->lines = mem_alloc(chunk->capacity, sizeof(*chunk->lines));
    chunk->constants = value_array_new();

    return chunk;
}

void chunk_free(Chunk** chunk_ptr)
{
    assert(chunk_ptr && ERROR_INVALID("chunk pointer"));
    assert(*chunk_ptr && ERROR_INVALID("chunk"));

    {
        Chunk* chunk = *chunk_ptr;
        mem_free(&chunk->code);
        mem_free(&chunk->lines);
        value_array_free(&chunk->constants);
    }

    mem_free(chunk_ptr);
}

void chunk_write(Chunk* chunk, uint8_t byte, size_t line)
{
    assert(chunk && ERROR_INVALID("chunk"));

    if (chunk->capacity < chunk->count + 1)
    {
        chunk->capacity *= CHUNK_GROW_FACTOR;
        chunk->code =
            mem_realloc(chunk->code, chunk->capacity, sizeof(*chunk->code));
        chunk->lines =
            mem_realloc(chunk->lines, chunk->capacity, sizeof(*chunk->lines));
    }

    chunk->code[chunk->count] = byte;
    chunk->lines[chunk->count] = line;
    chunk->count++;
}

size_t chunk_add_constant(Chunk* chunk, Value value)
{
    assert(chunk && ERROR_INVALID("chunk"));

    value_array_write(chunk->constants, value);
    return chunk->constants->count - 1;
}
