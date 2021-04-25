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
#include <errno.h>
#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

void
die(const char *fmt, ...)
{
    fmt = str_concat(2, fmt, "\n");
    va_list ap;

    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);

    exit(1);
}

void
edie(const char *fmt, ...)
{
	fmt = str_concat(2, fmt, strerror(errno));
    va_list ap;
    die(fmt, ap);
}

void *
ecalloc(size_t nmemb, size_t size)
{
    void *ptr = calloc(nmemb, size);
    if (ptr == NULL) edie("calloc: ");
    return ptr;
}

char *
str_dupe(const char *s, size_t n)
{
    char *r = STR_EALLOC(n);
    strncpy(r, s, n);
    return r;
}

size_t
str_pushc(char *s, char c, size_t s_size, size_t realloc_amount)
{
    /* Realloc s if needed */
    size_t s_len = strlen(s);
    if (s_len + 1 > s_size) {
        s_size += realloc_amount;
        s = realloc(s, s_size);
        if (s == NULL) edie("realloc: ");
    }

    s[s_len] = c;
    s[s_len + 1] = '\0';
    return s_size;
}

int
str_trimr(char *s, char c, int max_num)
{
    int removed = 0;
    int i = strlen(s)-1;
    while (s[i] == c && removed <= max_num) {
        s[i] = '\0';
        i--;
        removed++;
    }
    return removed;
}

char *
str_concat(int count, ...)
{
    va_list ap;
    int new_len = 1;

    /* Total length of all strings */
    va_start(ap, count);
    for (int i = 0; i < count; i++)
        new_len += strlen(va_arg(ap, char*));
    va_end(ap);

    char *new_str = calloc(new_len, sizeof(char));
    if (new_str == NULL) edie("calloc: ");

    /* Concat strings into newstr */
    va_start(ap, count);
    for (int i = 0; i < count; i++) {
        char *s = va_arg(ap, char*);
        strcat(new_str, s);
    }
    va_end(ap);

    return new_str;
}

char *
str_toupper(char *s, size_t n)
{
    for (size_t i = 0; i < n; i++) {
        if islower(s[i]) s[i] = toupper(s[i]);
    }
    return s;
}
