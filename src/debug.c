#include "debug.h"

#include <assert.h>
#include <stdio.h>

static int simple_instruction(const char* name, size_t offset);

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

    uint8_t instruction = chunk->code[offset];
    switch (instruction)
    {
    case OP_CODE_RETURN:
        return simple_instruction("OP_RETURN", offset);

    default:
        printf("Unknown opcode %d\n", instruction);
        return offset + 1;
    }
}

static int simple_instruction(const char* name, size_t offset)
{
    assert(name && ERROR_INVALID("name"));

    printf("%s\n", name);
    return offset + 1;
}
