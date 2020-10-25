#include "vm.h"

#include <stdio.h>

#include "common.h"
#include "debug.h"

static VMInterpretResult run(void);
static void stack_reset(void);

static VM vm = {0};

void vm_init(void)
{
    stack_reset();
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

void vm_push(Value value)
{
    *vm.stack_top = value;
    vm.stack_top++;
}

Value vm_pop(void)
{
    vm.stack_top--;
    return *vm.stack_top;
}

static VMInterpretResult run(void)
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants->values[READ_BYTE()])
{
    for (;;)
    {
#ifdef DEBUG_TRACE_EXECUTION
        {
            printf("         ");
            for (Value* slot = vm.stack; slot < vm.stack_top; slot++)
            {
                printf("[ ");
                value_print(*slot);
                printf(" ]");
            }
            printf("\n");

            size_t offset = (size_t)(vm.ip - vm.chunk->code);
            debug_disassemble_instruction(vm.chunk, offset);
        }
#endif
        uint8_t instruction = READ_BYTE();
        switch (instruction)
        {
        case OP_CODE_RETURN: {
            value_print(vm_pop());
            printf("\n");
            return VM_INTERPRET_RESULT_OK;
        }

        case OP_CODE_CONSTANT: {
            Value constant = READ_CONSTANT();
            vm_push(constant);
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

static void stack_reset(void)
{
    vm.stack_top = vm.stack;
}
