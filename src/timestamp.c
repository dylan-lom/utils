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

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "util.h"

const char *argv0;

void
usage()
{
	die("usage: %s [-d|-r|-R|-v]", argv0);
}

// TODO: strftime doesn't take %:z format (-R)
int
main(int argc, char *argv[])
{
    argv0 = argv[0];
    const char *fmt = "%Y-%m-%d %H:%M";
    char opt;
    while ((opt = getopt(argc, argv, "drRv")) != -1) {
        switch (opt) {
        case 'd': fmt = "%Y-%m-%d"; break;
        case 'r': fmt = "%Y-%m-%dT%T%z"; break;
        case 'R': fmt = "%Y-%m-%dT%T%:z"; break;
        case 'v': fmt = "%Y-%m-%d %H:%M %Z"; break;
        default: usage();
        }
    }

    if (!fmt) usage();

    time_t now = time(0);
    struct tm *now_tm = localtime(&now);

    char *s = STR_EALLOC(100);
    strftime(s, 100, fmt, now_tm);

    printf("%s\n", s);

    return 0;
}
