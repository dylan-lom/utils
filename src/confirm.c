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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <strings.h>

#include "util.h"

const char *argv0;

/*
 * Display msg, and prompt user for choice from opts.
 * Returns index of chosen opt.
 *
 * First option (opts[0]) is default if nothing else matches
 * Comparison is case insensitive
 */
int
confirm(const char *msg, const char **opts, int opts_count)
{
    if (opts_count < 2) return 0;

    char *opt0 = str_dupe(opts[0], sizeof(opts[0]));
    printf("%s [%s", msg, str_toupper(opt0, strlen(opt0)));
    free(opt0);
    for (int i = 1; i < opts_count; i++) {
        printf("/%s", opts[i]);
    }
    printf("]: ");

    char *resp = NULL;
    size_t n = 0;
    getline(&resp, &n, stdin);
    str_trimr(resp, '\n', 1);

    for (int i = 0; i < opts_count; i++) {
        if (strncasecmp(opts[i], resp, n) == 0) return i;
    }

    return 0;
}

/*
 * Get user confirmation
 * Examples:
 *   $ confirm
 *   $ confirm "Exit?"
 *   $ confirm "Download file?" n y
 *   $ confirm "What color?" red yellow blue
 */
int
main(int argc, const char *argv[])
{
    SET_ARGV0();

    // Options provided as args
    if (argc > 1) return confirm(argv[0], argv+1, argc-1);

    const char **opts = STR_EALLOC(2);
    opts[0] = "y";
    opts[1] = "n";
    return confirm(argc == 1 ? argv[0] : "Are you sure?", opts, 2);
}
