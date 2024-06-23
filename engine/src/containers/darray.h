#pragma once

#include "defines.h"

/*
Memory layout
u64 capacity = number elements that can be held
u64 length = number of elements currently contained
u64 stride = size of each element in bytes
void* elements
*/

enum {
    DARRAY_CAPACITY,
    DARRAY_LENGTH,
    DARRAY_STRIDE,
    DARRAY_FIELD_LENGTH   
};

KAPI void* _darray_create(u64 length, u64 stride);
KAPI void _darray_destroy(void* array);

KAPI u64 _darray_field_get(void* array, u64 field);
KAPI void _darray_field_set(void* array, u64 field, u64 value);

KAPI void* _darray_resize(void* array);

KAPI void* _darray_push(void* array, const void* value_ptr);
KAPI void* _darray_pop(void* array, void* dest);

KAPI void* _darray_pop_at(void* array, u64 index, void* dest);
KAPI void* _darray_insert_at(void* array, u64 index, void* value_ptr);

#define DARRAY_DEFAULT_CAPACITY 1
#define DARRAY_RESIZE_FACTOR 2

#define darray_create(type) \
    _darray_create(DARRAY_DEFAULT_CAPACITY, sizeof(type))

#define darray_reserve(type, capacity) \
    _darray_create(capacity, sizeof(type))

#define darray_destroy(array) _darray_destroy(array);