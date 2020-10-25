#include "value.h"

#include <assert.h>
#include <stdio.h>

#include "mem.h"

#define VALUE_ARRAY_DEFAULT_CAPACITY 8
#define VALUE_ARRAY_GROW_FACTOR 2

ValueArray* value_array_new()
{
    ValueArray* array = mem_alloc(1, sizeof(*array));

    array->capacity = VALUE_ARRAY_DEFAULT_CAPACITY;
    array->values = mem_alloc(array->capacity, sizeof(*array->values));

    return array;
}

void value_array_free(ValueArray** array_p)
{
    assert(array_p && ERROR_INVALID("array pointer"));
    assert(*array_p && ERROR_INVALID("array"));

    {
        ValueArray* array = *array_p;
        mem_free(&array->values);
    }

    mem_free(array_p);
}

void value_array_write(ValueArray* array, Value value)
{
    assert(array && ERROR_INVALID("array"));

    if (array->capacity < array->count + 1)
    {
        array->capacity *= VALUE_ARRAY_GROW_FACTOR;
        array->values =
            mem_realloc(array->values, array->capacity, sizeof(*array->values));
    }

    array->values[array->count] = value;
    array->count++;
}

void value_print(Value value)
{
    printf("%g", value);
}
