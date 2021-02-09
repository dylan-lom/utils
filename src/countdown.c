/*
 * Copyright (c) 2020 Dylan Lom <djl@dylanlom.com>
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
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "util.h"

const char* argv0;

void usage() {
    fprintf(stderr, "usage: %s time\n", argv0);
    exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]) {
    SET_ARGV0();

    if (argc < 1) usage();
    long time;
    char* p;
    time = strtol(argv[0], &p, 10);
    if (errno != 0 || *p != '\0') {
        fprintf(stderr, "strtol: %s\n", errno
                ? strerror(errno)
                : "Failed to parse time argument."
        );
        exit(EXIT_FAILURE);
    }
    SHIFT_ARGS();

    while (time) {
        /* Clear stdout, otherwise going from e.g. 10->9 leaves a trailing 0 */
        printf("\r                    ");
        printf("\r%d", time);
        fflush(stdout);
        sleep(1);
        time--;
    }

    puts("\n");
    return EXIT_SUCCESS;
}
