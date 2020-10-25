#include "chunk.h"
#include "common.h"
#include "debug.h"
#include "vm.h"

int main(void)
{
    vm_init();

    Chunk* chunk = chunk_new();

    uint8_t constant = (uint8_t) chunk_add_constant(chunk, 1.2);
    chunk_write(chunk, OP_CODE_CONSTANT, 123);
    chunk_write(chunk, constant, 123);

    chunk_write(chunk, OP_CODE_RETURN, 123);

    debug_disassemble_chunk(chunk, "test chunk");

    vm_interpret(chunk);

    chunk_free(&chunk);

    vm_dispose();
}
