/*
 * Copyright (c) 2020, 2021 Dylan Lom <djl@dylanlom.com>
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

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

const char *argv0;

void
usage()
{
    fprintf(stderr, "usage: %s [LINE...]", argv0);
    exit(1);
}

int
strtoi_safe(const char *s)
{
    int ln;
    char *p;
    // TODO: We should probably check for int overflows...
    ln = (int)strtol(s, &p, 10);
    if (errno != 0 || *p != '\0' || ln <= 0) {
        perror(errno ? NULL : "unable to parse line");
        exit(1);
    }
    return ln;
}

// Insert n into ordered set ns
void
insert(int n, int *ns, size_t ns_sz)
{
    size_t i;
    for (i = 0; i < ns_sz; i++) {
        if (ns[i] == n) return; // Don't insert duplicates
        if (ns[i] == 0 || ns[i] > n) break; // Found insertion point
    }

    int next;
    for (; i < ns_sz; i++) {
        next = ns[i];
        ns[i] = n;
        n = next;
    }
}

void
printlines(FILE *fp, int *lines, size_t lines_sz)
{
    char *s = NULL;
    size_t n = 0;

    for (int line = 1; getline(&s, &n, fp) != -1; line++) {
        if (!lines_sz) break;
        if (line == *lines) {
            printf(s);
            lines++;
            lines_sz--;
        }
    }

    free(s);
}

/* Print lines listed in argv from fp */
void
lines(int argc, char *argv[], FILE *fp)
{
    size_t lines_sz = argc; // how many lines were given as arguments
    int *lines = calloc(lines_sz, sizeof(*lines));
    if (!lines) {
        perror(NULL);
        exit(1);
    }

    // Construct ordered list of lines to extract from input
    while (argc) {
        insert(strtoi_safe(argv[0]), lines, lines_sz);
        argv++;
        argc--;
    }

    printlines(fp, lines, lines_sz);
}

int
main(int argc, char *argv[])
{
    argv0 = argv[0];
    argv++;
    argc--;

    if (argc < 1) usage(); // At least one line required

    FILE *fp = fdopen(STDIN_FILENO, "r");
    lines(argc, argv, fp);
    return 0;
}

