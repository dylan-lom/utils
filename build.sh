#!/usr/bin/env sh
#
#build stuff

VERSION='0.0.2-1'

CFLAGS="-std=c99 -Wall -W -Wpointer-arith -Wbad-function-cast -Wpedantic -D_XOPEN_SOURCE=700"
DEBDIR="dist/djl-utils"

commands="bin clean deb help tarball"
argv0="$0"

prettyname() {
    basename "$1" | rev | cut -d'.' -f2 | rev
}

cbuild() {
    target="$1"
    targetdest="bin/$(prettyname "$target")"
    shift
    (set -x; cc $CFLAGS -o "$targetdest" "$target" src/util.c "$@")
}

fbuild() {
    target="$1"
    targetdest="bin/$(prettyname "$target")"
    (set -x; cp "$target" "$targetdest")
}

bin() {
    [ ! -d bin ] && mkdir bin

    for f in src/*.c; do
        [ "$f" = "src/util.c" ] && continue
        cbuild "$f"
    done

    for f in src/pasta src/sign src/timestamp; do
        fbuild "$f"
    done
}

clean() {
    (set -x; rm -rf dist bin)
}

deb() {
    bin
    [ -d "$DEBDIR" ] && rm -f "$DISTDIR"
    (set -x; mkdir -p "$DEBDIR/usr/bin"
             mkdir -p "$DEBDIR/usr/share/man/man1"
             cp bin/* "$DEBDIR/usr/bin"
             cp doc/* "$DEBDIR/usr/share/man/man1"
             cp -r pkgsrc/DEBIAN "$DEBDIR"
             sed -i "s/%VERSION%/$VERSION/g" "$DEBDIR/DEBIAN/control"
             dpkg-deb -b "$DEBDIR")
}


help() {
    echo "$argv0 [$(echo "$commands" | tr ' ' '|')]" > /dev/stderr
}

tarball() {
    "$argv0" clean
    (set -x; tar -czf "v$VERSION.tgz" src doc pkgsrc "$argv0" LICENSE)
}

test -z "$1" && bin || $1

