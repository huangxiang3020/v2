#include "core/kstring.h"

#include <string.h>

#include "core/kmemory.h"

u64 string_length(const char* str) {
    return strlen(str);
}

char* string_dulicate(const char* str) {
    u64 length = string_length(str);
    char* copy = kallocate(length + 1, MEMORY_TAG_STRING);
    kcopy_memory(copy, str, length + 1);
    return copy;
}