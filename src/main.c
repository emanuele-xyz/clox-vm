#include "chunk.h"
#include "common.h"
#include "debug.h"

int main(void)
{
    Chunk* chunk = chunk_new();

    uint8_t constant = (uint8_t) chunk_add_constant(chunk, 1.2);
    chunk_write(chunk, OP_CODE_CONSTANT);
    chunk_write(chunk, constant);

    chunk_write(chunk, OP_CODE_RETURN);

    debug_disassemble_chunk(chunk, "test chunk");

    chunk_free(&chunk);
}
