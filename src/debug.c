#include "debug.h"

#include <assert.h>
#include <stdio.h>

#include "value.h"

static void print_line_number(Chunk const* chunk, size_t offset);
static size_t simple_instruction(const char* name, size_t offset);
static size_t constant_instruction(char const* name, Chunk const* chunk,
                                   size_t offset);

void debug_disassemble_chunk(Chunk const* chunk, char const* name)
{
    assert(chunk && ERROR_INVALID("chunk"));
    assert(name && ERROR_INVALID("name"));

    printf("== %s ==\n", name);

    for (size_t offset = 0; offset < chunk->count;)
    {
        offset = debug_disassemble_instruction(chunk, offset);
    }
}

size_t debug_disassemble_instruction(Chunk const* chunk, size_t offset)
{
    assert(chunk && ERROR_INVALID("chunk"));

    printf("%04zu ", offset);

    print_line_number(chunk, offset);

    uint8_t instruction = chunk->code[offset];
    switch (instruction)
    {
    case OP_CODE_CONSTANT:
        return constant_instruction("OP_CONST", chunk, offset);

    case OP_CODE_RETURN:
        return simple_instruction("OP_RETURN", offset);

    default:
        printf("Unknown opcode %d\n", instruction);
        return offset + 1;
    }
}

static void print_line_number(Chunk const* chunk, size_t offset)
{
    if (offset > 0 && chunk->lines[offset] == chunk->lines[offset - 1])
    {
        printf("   | ");
    }
    else
    {
        printf("%4zu ", chunk->lines[offset]);
    }
}

static size_t simple_instruction(const char* name, size_t offset)
{
    assert(name && ERROR_INVALID("name"));

    printf("%s\n", name);
    return offset + 1;
}

static size_t constant_instruction(char const* name, Chunk const* chunk,
                                   size_t offset)
{
    assert(name && ERROR_INVALID("name"));
    assert(chunk && ERROR_INVALID("chunk"));

    uint8_t constant_offset = chunk->code[offset + 1];
    printf("%-16s %4d '", name, constant_offset);
    value_print(chunk->constants->values[constant_offset]);
    printf("\n");

    return offset + 2;
}
