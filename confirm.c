/* confirm.c v0.2.1
 * ============================================================================
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
 * ============================================================================
 * CHANGELOG:
 *  v0.2.1: Use 255 as the default UNKNOWN_OPT_EXIT CODE (instead of 0).
 *    Stop -w flag being treated as message when no extra arguments given.
 *    Statically allocate default options, remove "prompt" function.
 */

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

const char *argv0;
/* Check input for whole-word match with options, enabled with -w flag at
 * runtime */
bool word_mode = false;
/* Exit code to when none of the available options were entered -- you can
 * change this to 0 if you just want to use the default option on unknown
 * input */
#define UNKNOWN_OPT_EXIT_CODE 255

static const char* default_opts[] = { "yes", "no" };

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
    // Display prompt
    printf("%s", msg);
    printf(" [%c%s", toupper(**opts), *opts+1);
    for (int i = 1; i < opts_count; i++) {
        printf("/%s", opts[i]);
    }
    printf("]: ");

    // Get response
    char *resp = NULL;
    size_t n = 0;
    getline(&resp, &n, stdin);
    if (strisspace(resp)) return 0; // No response -- default
    size_t resp_len = strlen(resp);
    resp[resp_len-1] = '\0';

    // Match response to option
    for (int i = 0; i < opts_count; i++) {
        if (!word_mode && toupper(resp[0]) == toupper(opts[i][0])) return i;
        if (word_mode && strncasecmp(opts[i], resp, n) == 0) return i;
    }

    // Response wasn't in opts
    return UNKNOWN_OPT_EXIT_CODE;
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
    argv0 = *(argv++);
    argc--;

    if (argc && strncmp(argv[0], "-w", 3) == 0) {
        word_mode = true;
        argv++;
        argc--;
    }

    for (int i = 1; i < argc; i++) {
        if (strisspace(argv[i])) {
            fprintf(stderr,
                    "confirm: ERROR: Options must be at least one non-whitespace character long, but option #%d was not. The default option will be chosen as supplied options are invalid.\n",
                    i);
            return 0;
        }
    }

    if (argc > 1) {
        // Options provided as args
        return confirm(argv[0], argv+1, --argc);
    } else {
        return confirm(argc ? argv[0] : "Are you sure?", default_opts, 2);
    }
}

