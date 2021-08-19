/* suptime.c v0.2.0
 * The following implementation is written "from scratch", and replaces the
 * original implementation (v0.1.x) which was derived from the OpenBSD w(1)
 * tool.
 *
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

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUF_SIZE 1024

typedef enum {
    MODE_SECONDS,
    MODE_MINUTES,
    MODE_HOURS,
    MODE_DAYS,
    MODE_FMT,
} Mode;

const char *argv0;

void
usage()
{
    fprintf(stderr, "usage: %s [-s|-m|-H|-d|-h]\n", argv0);
    fprintf(stderr, "usage: %s -f FORMAT\n", argv0);
    exit(1);
}

int
main(int argc, char *argv[])
{
    argv0 = argv[0];
    Mode mode = MODE_SECONDS;

    if (argc > 1) {
        if (argv[1][0] != '-') usage();

        char opt = argv[1][1];
        switch (opt) {
        case 's': mode = MODE_SECONDS; break;
        case 'm': mode = MODE_MINUTES; break;
        case 'H': mode = MODE_HOURS; break;
        case 'd': mode = MODE_DAYS; break;
        case 'f': mode = MODE_FMT; break;
        default: usage();
        }

        if (argv[1][2] != '\0') usage();
        if (mode == MODE_FMT && argc < 3) usage();
    }

    struct timespec ts;
    if (clock_gettime(CLOCK_BOOTTIME, &ts) == -1) {
        perror("clock_gettime");
        exit(1);
    }
    time_t uptime = ts.tv_sec;

    switch (mode) {
    case MODE_SECONDS: printf("%ld\n", uptime); break;
    case MODE_MINUTES: printf("%ld\n", uptime / 60); break;
    case MODE_HOURS: printf("%ld\n", uptime / 3600); break;
    case MODE_DAYS: printf("%ld\n", uptime / 86400); break;
    case MODE_FMT: {
        // TODO: Implement custom format function
        char buf[BUF_SIZE] = {0};
        struct tm *tm = gmtime(&(uptime));
        tm->tm_year = -1900; // Offset year by UTC epoch
        tm->tm_mday -= 1; // Start month at 0 so that results look better...
        if (strftime(buf, BUF_SIZE, argv[2], tm) == 0) exit(1);
        puts(buf);
    } break;
    default: assert(0 && "suptime: UNREACHABLE");
    }
}
