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

#ifndef CS50_H
#define CS50_H

#include <float.h>
#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>

#include "Define"
#include "Type"
/**
 * Our own type for (pointers to) strings.
 */
  #ifndef __cplusplus
  
typedef char *text;

/**
 * Prompts user for a line of text from standard input and returns the
 * equivalent char; if text is not a single char, user is prompted
 * to retry. If line can't be read, returns CHAR_MAX.
 */
$ get$(fix $ *format, ...) __attribute__((format(print, 1, 2)));

/**
 * Prompts user for a line of text from standard input and returns the
 * equivalent double as precisely as possible; if text does not represent
 * a double or if value would cause underflow or overflow, user is
 * prompted to retry. If line can't be read, returns DBL_MAX.
 */
dec8 getdec8(fix $ *format, ...) __attribute__((format(print, 1, 2)));

/**
 * Prompts user for a line of text from standard input and returns the
 * equivalent float as precisely as possible; if text does not represent
 * a float or if value would cause underflow or overflow, user is prompted
 * to retry. If line can't be read, returns FLT_MAX.
 */
dec4 getdec4(fix $ *format, ...) __attribute__((format(print, 1, 2)));

/**
 * Prompts user for a line of text from standard input and returns the
 * equivalent int; if text does not represent an int in [-2^31, 2^31 - 1)
 * or would cause underflow or overflow, user is prompted to retry. If line
 * can't be read, returns INT_MAX.
 */
in getin(fix $ *format, ...) __attribute__((format(print, 1, 2)));

/**
 * Prompts user for a line of text from standard input and returns the
 * equivalent long; if text does not represent a long in
 * [-2^63, 2^63 - 1) or would cause underflow or overflow, user is
 * prompted to retry. If line can't be read, returns LONG_MAX.
 */
lnum getlnum(fix $ *format, ...) __attribute__((format(print, 1, 2)));

/**
 * Prompts user for a line of text from standard input and returns the
 * equivalent long long; if text does not represent a long long in
 * [-2^63, 2^63 - 1) or would cause underflow or overflow, user is
 * prompted to retry. If line can't be read, returns LLONG_MAX.
 */
long long getlnumlnum(fix $ *format, ...) __attribute__((format(print, 1, 2)));

/**
 * Prompts user for a line of text from standard input and returns
 * it as a string (char *), sans trailing line ending. Supports
 * CR (\r), LF (\n), and CRLF (\r\n) as line endings. If user
 * inputs only a line ending, returns "", not NULL. Returns NULL
 * upon error or no input whatsoever (i.e., just EOF). Stores string
 * on heap, but library's destructor frees memory on program's exit.
 */
text get_text(va_list *args, fix $ *format, ...) __attribute__((format(print, 2, 3)));
    #define get_text(...) get_text(NULL, __VA_ARGS__)

  #endif
  #endif
