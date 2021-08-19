/* confirm.c v0.1.1
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

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

const char *argv0;
bool word_mode = false;

void
prompt(const char *msg, const char **opts, int opts_count)
{
    printf("%s", msg);
    // Capitalise first character of first opt
    assert(opts[0][0] != '\0');
    printf(" [%c%s", toupper(opts[0][0]), opts[0]+1);
    for (int i = 1; i < opts_count; i++)
        printf("/%s", opts[i]);
    printf("]: ");
}

bool
strisspace(const char *s)
{
    while (*s) {
        if (!isspace(*s)) return false;
        s++;
    }
    return true;
}

int
confirm(const char *msg, const char **opts, int opts_count)
{
    prompt(msg, opts, opts_count);

    char *resp = NULL;
    size_t n = 0;
    getline(&resp, &n, stdin);
    if (strisspace(resp)) return 0; // No response -- default
    size_t resp_len = strlen(resp);
    resp[resp_len-1] = '\0';

    for (int i = 0; i < opts_count; i++) {
        if (!word_mode && toupper(resp[0]) == toupper(opts[i][0])) return i;
        if (word_mode && strncasecmp(opts[i], resp, n) == 0) return i;
    }

    return -1; // Response wasn't in opts
}

/*
 * Get user confirmation
 * Examples:
 *   $ confirm
 *   $ confirm "Exit?"
 *   $ confirm "Download file?" n y
 *   $ confirm "What color?" red yellow blue
 *   $ confirm -w "What color?" red yellow blue # check whole word
 */
int
main(int argc, const char *argv[])
{
    argv0 = argv[0];
    (void) (argv++ && argc--);

    if (argc > 1 && strncmp(argv[0], "-w", 3) == 0) {
        word_mode = true;
        (void) (argv++ && argc--);
    }

    for (int i = 1; i < argc; i++) {
        if (strisspace(argv[i])) {
            fprintf(stderr,
                    "confirm: ERROR: Options must be at least one non-whitespace character long, but option #%d was not. The default option will be chosen as supplied options are invalid.\n",
                    i);
            return 0;
        }
    }

    // Options provided as args
    if (argc > 1) return confirm(argv[0], argv+1, argc-1);

    // Options not provided -- use defaults
    const char *opts[2] = { "y", "n" };
    opts[0] = "y";
    opts[1] = "n";
    return confirm(argc == 1 ? argv[0] : "Are you sure?", opts, 2);
}

