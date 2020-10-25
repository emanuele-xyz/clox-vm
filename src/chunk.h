#pragma once

#include "common.h"
#include "value.h"

typedef enum OpCode
{
    OP_CODE_CONSTANT,
    OP_CODE_RETURN,
} OpCode;

typedef struct Chunk
{
    size_t count;
    size_t capacity;
    uint8_t* code;
    ValueArray* constants;
} Chunk;

Chunk* chunk_new();
void chunk_free(Chunk** chunk_ptr);

void chunk_write(Chunk* chunk, uint8_t byte);
size_t chunk_add_constant(Chunk* chunk, Value value);
