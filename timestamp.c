/* timestamp.c v0.1.0
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
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>

#define STR_SZ 100
const char *argv0;

void
usage()
{
    fprintf(stderr, "usage: %s [-d|-r|-R|-v|-Y]\n", argv0);
    exit(1);
}

// TODO: strftime doesn't take %:z format (-R)
int
main(int argc, char *argv[])
{
    argv0 = argv[0];
    const char *fmt = "%Y-%m-%d %H:%M";

    tzset();
    int rfctz = 0;

    time_t now = time(0);
    struct tm *tm = localtime(&now);

    char opt;
    while ((opt = getopt(argc, argv, "drRvY")) != -1) {
        switch (opt) {
        case 'd': fmt = "%Y-%m-%d"; break;
        case 'r': fmt = "%Y-%m-%dT%T%z"; break;
        case 'R': {
            fmt = "%Y-%m-%dT%T";
            rfctz = 1;
        } break;
        case 'v': fmt = "%Y-%m-%d %H:%M %Z"; break;
        case 'Y': {
            printf("%d\n", tm->tm_yday);
            return 0;
        }
        default: usage();
        }
    }

    if (!fmt) usage();

    char *s = calloc(STR_SZ, sizeof(*s));
    if (!s) {
        perror("calloc");
        exit(1);
    }

    size_t l = strftime(s, STR_SZ, fmt, tm);

    if (rfctz) {
        assert(STR_SZ - l > 5);
        long hr = timezone / 60 / 60 * -1, // timezone is west of utc
             min = timezone / 60 % 60;
        snprintf(s+l, STR_SZ - l, "%+03ld:%02ld", hr, labs(min));
    }

    printf("%s\n", s);

    return 0;
}
