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
    die("usage: %s ln", argv0);
}

/* Print the ln'th line from fp to stdout */
void
line(FILE *fp, int ln)
{
    char c;
    int cln = 1;
    while ((c = fgetc(fp)) != '\0') {
        if (cln > ln) break;
        if (cln == ln) putc(c, stdout);
        if (c == '\n') cln++;
    }
}

/* Print a specified line from stdin */
int
main(int argc, char *argv[])
{
    SET_ARGV0();

    if (argc < 1) usage();
    int ln;
    char *p;
    ln = (int)strtol(argv[0], &p, 10);
    if (errno != 0 || *p != '\0') {
        errno ? edie("strtol: ") : die("unable to parse ln");
    }
    SHIFT_ARGS();

    FILE *fp;
    fp = fdopen(STDIN_FILENO, "r");
    line(fp, ln);
    return 0;
}

