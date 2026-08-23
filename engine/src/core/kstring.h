#pragma once

#include "defines.h"

#include "math/math_types.h"

/**
 * @brief Returns the length of the given string.
 * 
 * @param str The string to get the length of.
 * @returns The length of str.
 */
KAPI u64 string_length(const char* str);

/**
 * @brief Returns a duplicate of the given string.
 * 
 * @param str The string to duplicate.
 * @returns A pointer to str.
 */
KAPI char* string_duplicate(const char* str);

/**
 * @brief Performs a case-sensitive string comparison.
 * 
 * @param str0 The first string to compare.
 * @param str1 The second string to compare.
 * @returns true if str0 and str1 are the same; otherwise false.
 */
KAPI b8 strings_equal(const char* str0, const char* str1);

/**
 * @brief Performs a case-insensitive string comparison.
 * 
 * @param str0 The first string to compare.
 * @param str1 The second string to compare.
 * @returns true if str0 and str1 are the same; otherwise false.
 */
KAPI b8 strings_equali(const char* str0, const char* str1);

/**
 * @brief Performs string formatting to dest given format string and parameters.
 * 
 * @param dest The destination for the formatted string.
 * @param format The string to be formatted.
 * @param ... The parameter argument list.
 * @returns The size of the data written.
 */
KAPI i32 string_format(char* dest, const char* format, ...);

/**
 * @brief Performs variadic string formatting to dest given format string and va_list.
 * 
 * @param dest The destination for the formatted string.
 * @param format The string to be formatted.
 * @param va_list The variadic argument list.
 * @returns The size of the data written.
 */
KAPI i32 string_format_v(char* dest, const char* format, void* va_list);

/**
 * @brief Empties the provided string by setting the first character to 0.
 * 
 * @param str The string to be emptied.
 * @returns A pointer to str.
 */
KAPI char* string_empty(char* str);

/**
 * @brief Performs a string copy to dest using source.
 * 
 * @param dest The destination string.
 * @param source The source string.
 * @returns A pointer to dest.
 */
KAPI char* string_copy(char* dest, const char* source);

/**
 * @brief Performs a string copy to dest using source and a given length.
 * 
 * @param dest The destination string.
 * @param source The source string.
 * @param length The length of the source string to copy.
 * @returns A pointer to dest.
 */
KAPI char* string_ncopy(char* dest, const char* source, i64 length);

/**
 * @brief Trims whitespace and trailing characters from the given string.
 * 
 * @param str The string to trim.
 * @returns A pointer to the trimmed string.
 */
KAPI char* string_trim(char* str);

KAPI void string_mid(char* dest, const char* source, i32 start, i32 length);

/**
 * @brief Returns the index of the first occurance of c in str; otherwise -1;
 * 
 * @param str The string to be scanned.
 * @param c The character to search for.
 * @returns The index of the first occurance of c; otherwise -1 if not found.
 */
KAPI i32 string_index_of(char* str, char c);

/**
 * @brief Attempts to parse a vector from the provided string,
 * 
 * @param str The string to parse from. Should be space-delimited. (i.e. "1.0 2.0 3.0 4.0").
 * @param out_vector A pointer to the vector to write to.
 * @returns true if parsed successfully; otherwise false.
 */
KAPI b8 string_to_vec4(char* str, vec4* out_vector);

/**
 * @brief Attempts to parse a vector from the provided string,
 * 
 * @param str The string to parse from. Should be space-delimited. (i.e. "1.0 2.0 3.0").
 * @param out_vector A pointer to the vector to write to.
 * @returns true if parsed successfully; otherwise false.
 */
KAPI b8 string_to_vec3(char* str, vec3* out_vector);

/**
 * @brief Attempts to parse a vector from the provided string,
 * 
 * @param str The string to parse from. Should be space-delimited. (i.e. "1.0 2.0").
 * @param out_vector A pointer to the vector to write to.
 * @returns true if parsed successfully; otherwise false.
 */
KAPI b8 string_to_vec2(char* str, vec2* out_vector);

/**
 * @brief Attempts to parse a 32-bit floating-point number from the provided string.
 * 
 * @param str The string to parse from. Should *NOT* be postfixed with 'f'.
 * @param f A pointer to the float to write to.
 * @returns true if parsed successfully; otherwise false.
 */
KAPI b8 string_to_f32(char* str, f32* f);

/**
 * @brief Attempts to parse a 64-bit floating-point number from the provided string.
 * 
 * @param str The string to parse from. Should *NOT* be postfixed with 'f'.
 * @param f A pointer to the float to write to.
 * @returns true if parsed successfully; otherwise false.
 */
KAPI b8 string_to_f64(char* str, f64* f);

/**
 * @brief Attempts to parse an 8-bit signed integer from the provided string.
 * 
 * @param str The string to parse from.
 * @param i A pointer to the int to write to.
 * @returns true if parsed successfully; otherwise false.
 */
KAPI b8 string_to_i8(char* str, i8* i);

/**
 * @brief Attempts to parse a 16-bit signed integer from the provided string.
 * 
 * @param str The string to parse from.
 * @param i A pointer to the int to write to.
 * @returns true if parsed successfully; otherwise false.
 */
KAPI b8 string_to_i16(char* str, i16* i);

/**
 * @brief Attempts to parse a 32-bit signed integer from the provided string.
 * 
 * @param str The string to parse from.
 * @param i A pointer to the int to write to.
 * @returns true if parsed successfully; otherwise false.
 */
KAPI b8 string_to_i32(char* str, i32* i);

/**
 * @brief Attempts to parse a 64-bit signed integer from the provided string.
 * 
 * @param str The string to parse from.
 * @param i A pointer to the int to write to.
 * @returns true if parsed successfully; otherwise false.
 */
KAPI b8 string_to_i64(char* str, i64* i);

/**
 * @brief Attempts to parse an 8-bit unsigned integer from the provided string.
 * 
 * @param str The string to parse from.
 * @param u A pointer to the int to write to.
 * @returns true if parsed successfully; otherwise false.
 */
KAPI b8 string_to_u8(char* str, u8* u);

/**
 * @brief Attempts to parse a 16-bit unsigned integer from the provided string.
 * 
 * @param str The string to parse from.
 * @param u A pointer to the int to write to.
 * @returns true if parsed successfully; otherwise false.
 */
KAPI b8 string_to_u16(char* str, u16* u);

/**
 * @brief Attempts to parse a 32-bit unsigned integer from the provided string.
 * 
 * @param str The string to parse from.
 * @param u A pointer to the int to write to.
 * @returns true if parsed successfully; otherwise false.
 */
KAPI b8 string_to_u32(char* str, u32* u);

/**
 * @brief Attempts to parse a 64-bit unsigned integer from the provided string.
 * 
 * @param str The string to parse from.
 * @param u A pointer to the int to write to.
 * @returns true if parsed successfully; otherwise false.
 */
KAPI b8 string_to_u64(char* str, u64* u);

/**
 * @brief Attempts to parse a boolean from the provided string.
 * 
 * @param str The string to parse from. "true" or "1" are considered true; anything else is false.
 * @param b A pointer to the boolean to write to.
 * @returns true if parsed successfully; otherwise false.
 */
KAPI b8 string_to_bool(char* str, b8* b);
