/*
 * Copyright (c) 2021 Dylan Lom <djl@dylanlom.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */ 

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>

#include "util.h"

const char *argv0;

/*
 * Check if s is a valid decimal number.
 */
bool
isnum(const char *s)
{
    if (*s == '-' || *s == '+') s++;
    while (*s) {
        if (!isdigit(*s)) return false;
        s++;
    }
    return true;
}

/*
 * Coalesce s into true/false boolean.
 * The following strings are considered false:
 *   false, null, 0 (and its other representations, e.g. 000, -, +)
 * BUG: Non base-10 representations of 0 are considered truthy
 */
bool
truthy(const char *s)
{
    if (isnum(s) && atoi(s) == 0) return false;
    if (strcasecmp(s, "false") == 0 || strcasecmp(s, "null") == 0) return false;

    return true;
}

/*
 * Determine if a value is true-adjacent. Inspired by (but not following)
 * JavaScript's concept of truthy/falsey-ness.
 * https://developer.mozilla.org/en-US/docs/Glossary/Falsy
 */
int
main(int argc, char *argv[])
{
    SET_ARGV0();

    if (argc < 1 || !truthy(argv[0]))
        return 1;
    return 0;
}
