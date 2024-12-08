#pragma once

#include "defines.h"
#include "math/math_types.h"

KAPI u64 string_length(const char* str );

KAPI char* string_dulicate(const char* str);

KAPI b8 strings_equal(const char* str0, const char* str1);

KAPI b8 strings_equali(const char* str0, const char* str1);

KAPI i32 string_format(char* dest, const char* format, ...);

/**
 * Performs variadic string formatting to dest given format string and va_list.
 * @param dest The destination for the formatted string.
 * @param format The string to be formatted.
 * @param va_list The variadic argument list.
 * @returns The size of the data written.
 */
KAPI i32 string_format_v(char* dest, const char* format, void* va_list);

KAPI char* string_copy(char* dest, const char* source);

KAPI char* string_ncopy(char* dest, const char* source, i64 length);

KAPI char* string_trim(char* str);

KAPI void string_mid(char* dest, const char* source, i32 start, i32 length);

KAPI i32 string_index_of(char* str, char c);

KAPI b8 string_to_vec4(char* str, vec4* out_vector);

KAPI b8 string_to_vec3(char* str, vec3* out_vector);

KAPI b8 string_to_vec3(char* str, vec3* out_vector);

KAPI b8 string_to_vec2(char* str, vec2* out_vector);

KAPI b8 string_to_f32(char* str, f32* f);

KAPI b8 string_to_f64(char* str, f64* f);

KAPI b8 string_to_i8(char* str, i8* i);

KAPI b8 string_to_i16(char* str, i16* i);

KAPI b8 string_to_i32(char* str, i32* i);

KAPI b8 string_to_i64(char* str, i64* i);

KAPI b8 string_to_u8(char* str, u8* u);

KAPI b8 string_to_u16(char* str, u16* u);

KAPI b8 string_to_u32(char* str, u32* u);

KAPI b8 string_to_u64(char* str, u64* u);

KAPI b8 string_to_bool(char* str, b8* b);