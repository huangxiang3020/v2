#pragma once

#include "defines.h"

typedef struct hashtable {
    u64 element_size;
    u32 element_count;
    b8 is_pointer_type;
    void* memory;
} hashtable;

KAPI void hashtable_create(u64 element_size, u32 element_count, void* memory, b8 is_pointer_type, hashtable* out_hashtable);

KAPI void hashtable_destroy(hashtable* table);

KAPI b8 hashtable_set(hashtable* table, const char* name, void* value);

KAPI b8 hashtable_set_ptr(hashtable* table, const char* name, void** value);

KAPI b8 hashtable_get(hashtable* table, const char* name, void* out_value);

KAPI b8 hashtable_get_ptr(hashtable* table, const char* name, void** out_value);

KAPI b8 hashtable_fill(hashtable* table, void* value);
