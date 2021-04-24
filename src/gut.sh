#!/usr/bin/env sh
#
# gut: git but gross
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

root() {
    git rev-parse --show-toplevel
}

add() {
    truthy "$1" \
        && git add $1 \
        || (for f in $(git status --porcelain | cut -c4-); do \
            confirm "Add $f?" && git add "$(root)/$f"; done)
}

alias co='checkout'
checkout() {
    truthy "$1" && target="$1" || target="$(git config init.defaultBranch)"
    git checkout "$target"
}


alias save='stash'
stash() {
    truthy "$1" \
        && git stash push -m "$1" \
        || git stash push
}

# If anything already added (staged):
#    then commit that
#    else prompt user to stage then commit
commit() {
    git status --porcelain | grep -q '^[^ ]*A' \
        && git commit \
        || (status; add; git commit)
}

# If anything already added (staged):
#    then amend that
#    else amend all
amend() {
    git status --porcelain | grep -q '^[^ ]*A' \
        && git commit --amend \
        || git commit --amend -a
}

status() {
    git status --short
}

$@
