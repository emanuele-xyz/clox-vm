#include "chunk.h"
#include "common.h"

int main(void)
{
    Chunk* chunk = chunk_new();
    chunk_write(chunk, OP_CODE_RETURN);
    chunk_free(&chunk);
}
