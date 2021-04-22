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

# CHRISTMAS GIT MAGIC
add() {
    truthy "$1" \
        && git add $1 \
        #|| (for f in $(git status --porcelain | cut -c4-); do)
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

# Is anything already staged
#    then: commit that
#    else: stage and commit everything 
commit() {
    status
    git status --porcelain | grep '^[^ ]*A' \
        && git commit -a \
        || (git add . && git commit "$1")
}

amend() {
    git commit --amend -a
}

push() {
    git push $1
}

alias update='pull'
pull() {
    git pull $1
}

status() {
    git status --short
}

diff() {
    git diff $1
}

$@
