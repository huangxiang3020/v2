#pragma once

#include "defines.h"

KAPI u64 string_length(const char* str );

KAPI char* string_dulicate(const char* str);

KAPI b8 strings_equal(const char* str0, const char* str1);

KAPI i32 string_format(char* dest, const char* format, ...);

/**
 * Performs variadic string formatting to dest given format string and va_list.
 * @param dest The destination for the formatted string.
 * @param format The string to be formatted.
 * @param va_list The variadic argument list.
 * @returns The size of the data written.
 */
KAPI i32 string_format_v(char* dest, const char* format, void* va_list);