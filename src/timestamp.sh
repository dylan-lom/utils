#!/usr/bin/env sh
#
# timestamp: print current date-time(stamp)
# author: Dylan Lom <djl@dylanlom.com>
#
# Copyright (C) 2021 Dylan Lom <djl@dylanlom.com>
#
# Permission to use, copy, modify, and/or distribute this software for any purpose
# with or without fee is hereby granted.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
# REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
# FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
# INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
# OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
# TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF
# THIS SOFTWARE.
#
# flags:
#  -d    date only.
#  -r    rfc3339 without a colon in offset.
#  -R    rfc3339
#  -v    verbose human readable.
#  -h    display help
#  *     human readable.

argv0="$0"

usage() {
    echo "USAGE: $argv0 [-d|-r|-R|-v|-h]" > /dev/stderr
    exit 1
}

case "$1" in
    '-h') usage ;;
    '-d') fmt='%Y-%m-%d';;
    '-r') fmt='%Y-%m-%dT%T%z' ;;
    '-R') fmt='%Y-%m-%dT%T%:z' ;;
    '-v') fmt='%Y-%m-%d %T %Z';;
    *)    fmt='%Y-%m-%d %H:%M';;
esac

date "+$fmt"
