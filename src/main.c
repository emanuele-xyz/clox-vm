#include "chunk.h"
#include "common.h"
#include "debug.h"

int main(void)
{
    Chunk* chunk = chunk_new();
    chunk_write(chunk, OP_CODE_RETURN);

    debug_disassemble_chunk(chunk, "test chunk");

    chunk_free(&chunk);
}
