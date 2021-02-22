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

#include "util.h"

const char *argv0;

void
usage()
{
    die("usage: %s [LINE...]", argv0);
}

int
getlineno(const char *s)
{
    int ln;
    char *p;
    ln = (int)strtol(s, &p, 10);
    if (errno != 0 || *p != '\0' || ln <= 0) {
        errno ? edie("strtol: ") : die("unable to parse line");
    }
    return ln;
}

/* Insert ln into lns, assuming it is lns_size long and 0 initialised */
int *
insertln(int ln, int *lns, size_t lns_size)
{
    int *ip = lns;
    int j;

    while (lns_size && *ip && *ip < ln) {
        ADVANCE_PTR(ip, lns_size);
    }

    while (lns_size) {
        j = *ip;
        *ip = ln;
        ln = j;
        ADVANCE_PTR(ip, lns_size);
    }

    return lns;
}

void
printlines(FILE *fp, int *lns, size_t lns_size)
{
    char c;
    int cln = 1;
    while (lns_size && (c = fgetc(fp)) != '\0') {
        if (cln > *lns) { ADVANCE_PTR(lns, lns_size); }
        if (cln == *lns) putc(c, stdout);
        if (c == '\n') cln++;
    }
}

/* Print specified lines from stdin */
int
main(int argc, char *argv[])
{
    int *lns;
    SET_ARGV0();

    if (argc < 1) usage();
    size_t lns_size = argc;
    lns = ecalloc(lns_size, sizeof(int));

    while (argc) {
        lns = insertln(getlineno(argv[0]), lns, lns_size);
        SHIFT_ARGS();
    }

    FILE *fp;
    fp = fdopen(STDIN_FILENO, "r");
    printlines(fp, lns, lns_size);
    return 0;
}

