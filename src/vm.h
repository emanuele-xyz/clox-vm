#pragma once

#include "chunk.h"

typedef struct VM
{
    Chunk* chunk;
    uint8_t* ip;
} VM;

typedef enum VMInterpretResult
{
    VM_INTERPRET_RESULT_OK,
    VM_INTERPRET_RESULT_COMPILE_ERROR,
    VM_INTERPRET_RESULT_RUNTIME_ERROR,
} VMInterpretResult;

void vm_init(void);
void vm_dispose(void);

VMInterpretResult vm_interpret(Chunk* chunk);
