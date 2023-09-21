/* suptime.c v0.2.1
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

#define SECSPERMIN 60
#define SECSPERHOUR 3600
#define SECSPERDAY 86400
#define SECSPERYEAR 31557600

typedef enum {
    MODE_SECONDS,
    MODE_MINUTES,
    MODE_HOURS,
    MODE_DAYS,
    MODE_FMT,
} Mode;

#define BUF_SIZE 1024
const char *argv0;

void
usage()
{
    fprintf(stderr, "usage: %s [-s|-m|-H|-d|-h]\n", argv0);
    fprintf(stderr, "usage: %s -f FORMAT\n", argv0);
    exit(1);
}

void
fmtprint(const char *fmt, time_t uptime)
{
    char c;
    while ((c = *fmt++)) {
        if (c == '%') {
            c = *fmt++;
            switch (c) {
                break; case 'Y': printf("%ld", uptime / SECSPERYEAR);
                break; case 'd': printf("%ld", uptime / SECSPERDAY);
                break; case 'H': printf("%02ld", uptime / SECSPERHOUR);
                break; case 'm': printf("%02ld", uptime / SECSPERMIN);
                break; case 's': printf("%02ld", uptime);
                break; case 'D': printf("%ld", uptime % SECSPERYEAR / SECSPERDAY);
                break; case 'h': printf("%02ld", uptime % SECSPERDAY / SECSPERHOUR);
                break; case 'M': printf("%02ld", uptime % SECSPERHOUR / SECSPERMIN);
                break; case 'S': printf("%02ld", uptime % SECSPERMIN);
                break; case 'n': putc('\n', stdout);
                break; case 't': putc('\t', stdout);
                break; case 'T': printf("%02ld:%02ld:%02ld",
                        uptime / SECSPERHOUR,
                        uptime % SECSPERHOUR / SECSPERMIN,
                        uptime % SECSPERMIN);
                break; default: printf("%%%c", c);
            }
        } else {
            putc(c, stdout);
        }
    }

    putc('\n', stdout);
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
    case MODE_MINUTES: printf("%ld\n", uptime / SECSPERMIN); break;
    case MODE_HOURS: printf("%ld\n", uptime / SECSPERHOUR); break;
    case MODE_DAYS: printf("%ld\n", uptime / SECSPERDAY); break;
    case MODE_FMT: fmtprint(argv[2], uptime); break;
    default: assert(0 && "suptime: UNREACHABLE");
    }
}
