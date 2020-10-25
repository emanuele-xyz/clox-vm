#pragma once

#include "chunk.h"
#include "value.h"

#define STACK_MAX 256

typedef struct VM
{
    Chunk* chunk;
    uint8_t* ip;
    Value stack[STACK_MAX];
    Value* stack_top;
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

void vm_push(Value value);
Value vm_pop(void);
