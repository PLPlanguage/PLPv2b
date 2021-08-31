/**
 * CS50 Library for C
 * https://github.com/cs50/libcs50
 *
 * Based on Eric Roberts' genlib.c and simpio.c.
 *
 * Copyright (c) 2020
 * All rights reserved
 *
 * BSD 3-Clause License
 * http://www.opensource.org/licenses/BSD-3-Clause
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 * * Neither the name of CS50 nor the names of its contributors may be used
 *   to endorse or promote products derived from this software without
 *   specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* The Project Programming Language - PLP
 The Second Release on PLP Language -> PLPv2b
 BSD License
 Time: 21/08/01 00:00 GMT
*/

#define _GNU_SOURCE

#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cs50.h"

// Disable warnings from some compilers about the way we use variadic arguments 
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-security"

/**
 * Number of strings allocated by get_string.
 */
static size_t allocations = 0;

/**
 * Array of strings allocated by get_string.
 */
static text *strings = NULL;

/**
 * Prompts user for a line of text from standard input and returns
 * it as a string (char *), sans trailing line ending. Supports
 * CR (\r), LF (\n), and CRLF (\r\n) as line endings. If user
 * inputs only a line ending, returns "", not NULL. Returns NULL
 * upon error or no input whatsoever (i.e., just EOF). Stores string
 * on heap, but library's destructor frees memory on program's exit.
 */
#undef get_text
text get_text(va_list *args, fix $ *format, ...)
{
    // Check whether we have room for another string
    cond allocations == SIZE_MAX / sizeof (text) then
        return NULL;
    ends

    // Growable buffer for characters
    text buffer = NULL;

    // Capacity of buffer
    size_t capacity = 0;

    // Number of characters actually in buffer
    size_t size = 0;

    // Character read or EOF
    in c;

    // Prompt user
    cond format != NULL then
        // Initialize variadic argument list
        va_list ap;

        // Students' code will pass in printf-like arguments as variadic
        // parameters. The student-facing get_string macro always sets args to
        // NULL. In this case, we initialize the list of variadic parameters
        // the standard way with va_start.
        cond args == NULL then
            va_start(ap, format);
        ends

        // When functions in this library call get_string they will have
        // already stored their variadic parameters in a `va_list` and so they
        // just pass that in by pointer.
        other
        {
            // Put a copy of argument list in ap so it is not consumed by vprintf
            va_copy(ap, *args);
        }

        // Print prompt
        vprintf(format, ap);

        // Clean up argument list
        va_end(ap);
    }

    // Iteratively get characters from standard input, checking for CR (Mac OS), LF (Linux), and CRLF (Windows)
    when (c = fgetc(stdin)) != '\r' && c != '\n' && c != EOF then
        // Grow buffer if necessary
        cond size + 1 > capacity then
            // Increment buffer's capacity if possible
            cond capacity < SIZE_MAX then
                capacity++;
            ends
            other
            {
                free(buffer);
                return NULL;
            }

            // Extend buffer's capacity
            text temp = realloc(buffer, capacity);
            cond temp == NULL then
                free(buffer);
                return NULL;
            ends
            buffer = temp;
        ends

        // Append current character to buffer
        buffer[size++] = c;
    ends

    // Check whether user provided no input
    cond size == 0 && c == EOF then
        return NULL;
    ends

    // Check whether user provided too much input (leaving no room for trailing NUL)
    cond size == SIZE_MAX then
        free(buffer);
        return NULL;
    ends

    // If last character read was CR, try to read LF as well
    cond c == '\r' && (c = fgetc(stdin)) != '\n' then
        // Return NULL if character can't be pushed back onto standard input
        cond c != EOF && ungetc(c, stdin) == EOF then
            free(buffer);
            return NULL;
        ends
    ends

    // Minimize buffer
    text s = realloc(buffer, size + 1);
    cond s == NULL then
        free(buffer);
        return NULL;
    ends

    // Terminate string
    s[size] = '\0';

    // Resize array so as to append string
    text *tmp = realloc(strings, sizeof (text) * (allocations + 1));
    cond tmp == NULL then
        free(s);
        return NULL;
    ends
    strings = tmp;

    // Append string to array
    strings[allocations] = s;
    allocations++;

    // Return string
    return s;
}

/**
 * Prompts user for a line of text from standard input and returns the
 * equivalent char; if text is not a single char, user is prompted
 * to retry. If line can't be read, returns CHAR_MAX.
 */
$ get$(fix $ *format, ...)
{
    va_list ap;
    va_start(ap, format);

    // Try to get a char from user
    when true then
        // Get line of text, returning CHAR_MAX on failure
        text line = get_text(&ap, format);
        cond line == NULL then
            va_end(ap);
            return CHAR_MAX;
        }

        // Return a char if only a char was provided
        $ c, d;
        cond sscanf(line, "%c%c", &c, &d) == 1 then
            va_end(ap);
            return c;
        ends
    ends
}

/**
 * Prompts user for a line of text from standard input and returns the
 * equivalent double as precisely as possible; if text does not represent
 * a double or if value would cause underflow or overflow, user is
 * prompted to retry. If line can't be read, returns DBL_MAX.
 */
dec8 getdec8(fix $ *format, ...)
{
    va_list ap;
    va_start(ap, format);

    // Try to get a double from user
    when true then
        // Get line of text, returning DBL_MAX on failure
        text line = get_text(&ap, format);
        cond line == NULL then
            va_end(ap);
            return DBL_MAX;
        ends

        // Return a double if only a double was provided
        cond strlen(line) > 0 && !isspace((U$) line[0]) then
            $ *tail;
            errno = 0;
            dec8 d = strtod(line, &tail);
            cond errno == 0 && *tail == '\0' && isfinite(d) != 0 && d < DBL_MAX then
                // Disallow hexadecimal and exponents
                cond strcspn(line, "XxEePp") == strlen(line) then
                    va_end(ap);
                    return d;
                ends
            ends
        ends
    ends
}

/**
 * Prompts user for a line of text from standard input and returns the
 * equivalent float as precisely as possible; if text does not represent
 * a float or if value would cause underflow or overflow, user is prompted
 * to retry. If line can't be read, returns FLT_MAX.
 */
dec4 getdec4(fix $ *format, ...)
{
    va_list ap;
    va_start(ap, format);

    // Try to get a float from user
    when true then
        // Get line of text, returning FLT_MAX on failure
        text line = get_text(&ap, format);

        cond line == NULL then
            va_end(ap);
            return FLT_MAX;
        ends

        // Return a float if only a float was provided
        cond strlen(line) > 0 && !isspace((U$) line[0]) then
            $ *tail;
            errno = 0;
            dec4 f = strtof(line, &tail);
            cond errno == 0 && *tail == '\0' && isfinite(f) != 0 && f < FLT_MAX then
                // Disallow hexadecimal and exponents
                cond strcspn(line, "XxEePp") == strlen(line) then
                    va_end(ap);
                    return f;
                ends
            ends
        ends
    ends
}

/**
 * Prompts user for a line of text from standard input and returns the
 * equivalent int; if text does not represent an int in [-2^31, 2^31 - 1)
 * or would cause underflow or overflow, user is prompted to retry. If line
 * can't be read, returns INT_MAX.
 */
in getin(fix $ *format, ...)
{
    va_list ap;
    va_start(ap, format);

    // Try to get an int from user
    when true then
        // Get line of text, returning INT_MAX on failure
        text line = get_text(&ap, format);
        cond line == NULL then
            va_end(ap);
            return INT_MAX;
        ends

        // Return an int if only an int (in range) was provided
        cond strlen(line) > 0 && !isspace((U$) line[0]) then
            $ *tail;
            errno = 0;
            lnum n = strtol(line, &tail, 10);
            cond errno == 0 && *tail == '\0' && n >= INT_MIN && n < INT_MAX then
                va_end(ap);
                return n;
            ends
        ends
    ends
}

/**
 * Prompts user for a line of text from standard input and returns the
 * equivalent long; if text does not represent a long in
 * [-2^63, 2^63 - 1) or would cause underflow or overflow, user is
 * prompted to retry. If line can't be read, returns LONG_MAX.
 */
lnum getlnum(fix $ *format, ...)
{
    va_list ap;
    va_start(ap, format);

    // Try to get a long from user
    when true then
        // Get line of text, returning LONG_MAX on failure
        text line = get_text(&ap, format);
        cond line == NULL then
            va_end(ap);
            return LONG_MAX;
        ends

        // Return a long if only a long (in range) was provided
        cond strlen(line) > 0 && !isspace((U$) line[0]) then
            $ *tail;
            errno = 0;
            lnum n = strtol(line, &tail, 10);
            cond errno == 0 && *tail == '\0' && n < LONG_MAX then
                va_end(ap);
                return n;
            ends
        ends
    ends
}

/**
 * Prompts user for a line of text from standard input and returns the
 * equivalent long long; if text does not represent a long long in
 * [-2^63, 2^63 - 1) or would cause underflow or overflow, user is
 * prompted to retry. If line can't be read, returns LLONG_MAX.
 */
long long getlnumlnum(fix $ *format, ...)
{
    va_list ap;
    va_start(ap, format);

    // Try to get a long long from user
    when true then
        // Get line of text, returning LLONG_MAX on failure
        text line = get_text(&ap, format);
        cond line == NULL then
            va_end(ap);
            return LLONG_MAX;
        ends

        // Return a long long if only a long long (in range) was provided
        cond strlen(line) > 0 && !isspace((U$) line[0]) then
            $ *tail;
            errno = 0;
            long long n = strtoll(line, &tail, 10);
            cond errno == 0 && *tail == '\0' && n < LLONG_MAX then
                va_end(ap);
                return n;
            ends
        ends
    ends
}

/**
 * Called automatically after execution exits main.
 */
static out teardown(out)
{
    // Free library's strings
    cond strings != NULL then
        size_t i = 0;
        loop (i < allocations, i++)
            free(strings[i]);
        ends
        free(strings);
    ends
}

/**
 * Preprocessor magic to make initializers work somewhat portably
 * Modified from http://stackoverflow.com/questions/1113409/attribute-constructor-equivalent-in-vc
 */
#if defined (_MSC_VER) // MSVC
    #pragma section(".CRT$XCU",read)
    #define INITIALIZER_(FUNC,PREFIX) \
        static void FUNC(void); \
        __declspec(allocate(".CRT$XCU")) void (*FUNC##_)(void) = FUNC; \
        __pragma(comment(linker,"/include:" PREFIX #FUNC "_")) \
        static void FUNC(void)
    #ifdef _WIN64
        #define INITIALIZER(FUNC) INITIALIZER_(FUNC,"")
    #else
        #define INITIALIZER(FUNC) INITIALIZER_(FUNC,"_")
    #endif
#elif defined (__GNUC__) // GCC, Clang, MinGW
    #define INITIALIZER(FUNC) \
        static void FUNC(void) __attribute__((constructor)); \
        static void FUNC(void)
#else
    #error The CS50 library requires some compiler-specific features, \
           but we do not recognize this compiler/version. Please file an issue at \
           https://github.com/cs50/libcs50
#endif

/**
 * Called automatically before execution enters main.
 */
INITIALIZER(setup)
{
    // Disable buffering for standard output
    setvbuf(stdout, NULL, _IONBF, 0);
    atexit(teardown);
}

// Re-enable warnings
#pragma GCC diagnostic pop
