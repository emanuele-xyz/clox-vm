#pragma once

#include "common.h"

typedef double Value;

typedef struct ValueArray
{
    size_t capacity;
    size_t count;
    Value* values;
} ValueArray;

ValueArray* value_array_new();
void value_array_free(ValueArray** array_p);

void value_array_write(ValueArray* array, Value value);
