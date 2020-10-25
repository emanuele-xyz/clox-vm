#include "vm.h"

#include <stdio.h>

#include "common.h"

static VMInterpretResult run(void);

static VM vm = {0};

void vm_init(void)
{
}

void vm_dispose(void)
{
}

VMInterpretResult vm_interpret(Chunk* chunk)
{
    vm.chunk = chunk;
    vm.ip = vm.chunk->code;

    return run();
}

static VMInterpretResult run(void)
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants->values[READ_BYTE()])
{
    for (;;)
    {
        uint8_t instruction = READ_BYTE();
        switch (instruction)
        {
        case OP_CODE_RETURN: {
            return VM_INTERPRET_RESULT_OK;
        }

        case OP_CODE_CONSTANT: {
            Value constant = READ_CONSTANT();
            value_print(constant);
            printf("\n");
            break;
        }

        default: {
            break;
        }
        }
    }
}
#undef READ_CONSTANT
#undef READ_BYTE
