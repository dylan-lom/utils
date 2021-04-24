#!/usr/bin/env sh
#
# confirm: get user confirmation
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

truthy "$1" \
    && msg="$1" \
    || msg="Are you sure you want to do that?"
printf "%s [Y/n]: " "$msg"
read resp
test ! "$resp" = 'N' -a ! "$resp" = 'n'
