#ifndef _POSIX_C_SOURCE
#define ssize_t long
#endif // _POSIX_C_SOURCE

#if _POSIX_C_SOURCE < 200809L
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
ssize_t getline(char **lineptr, size_t *n, FILE *stream)
{
    // This is what my glibc allocates in increments of
    const size_t alloc_increment = 120;
    size_t len = 0;

    if (lineptr == NULL || n == NULL || stream == NULL) {
        errno = EINVAL;
        return -1;
    }

    if (*lineptr == NULL && *n == 0) {
        *n = alloc_increment;
        *lineptr = malloc(*n);
        if (*lineptr == NULL) return -1;
    }

    char c;
    while ((c = fgetc(stream)) != EOF) {
        // Make sure there is room for c + \0
        if (len + 1 >= *n) {
            *n += alloc_increment;
            // realloc will set errno on error
            *lineptr = realloc(*lineptr, *n);
            if (*lineptr == NULL) return -1;
        }
        (*lineptr)[len++] = c;
        if (c == '\n') break;
    }
    (*lineptr)[len+1] = '\0';
    
    return len;
}

#endif // _POSIX_C_SOURCE < 200809L

