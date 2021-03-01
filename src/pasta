#!/usr/bin/env sh
#
# pasta: simple ssh-based paste bin (client)
# author: Hiltjo Posthuma <hiltjo@codemass.org>, Dylan Lom <djl@dylanlom.com>
# see-also: https://codemadness.org/paste-service.html

sshdomain="djl@p.dlom.cc"
destpath="/usr/local/www/p.dlom.cc"
destdomain="http://p.dlom.cc"

argv0="$0"

usage() {
	echo "usage: $argv0 [-p|-c|-g] [-x] filename"
	exit 1
}

while [ "$#" -gt 1 ]; do
    case "$1" in
        '-p') png='true'; ;;
        '-c') concat='true'; ;;
        '-g') get='true'; ;;
        '-x') xclip='true'; ;;
        *) usage ;;
    esac
    shift
done

name="$1"
[ -z "$name" ] && usage

if truthy "$xclip"; then
    command -v xclip > /dev/null \
        || (echo "ERROR: xclip not found" && exit 1) \
        && (echo "$destdomain/$name" | \
            tr -d '\n' | \
            xclip -selection clipboard)
fi

if truthy "$get"; then
    curl "$destdomain/$name"
    exit
fi

if truthy "$concat"; then
   ssh "$sshdomain" "cat >> $destpath/$name"
else
    (truthy "$png" && import png:- || cat) | \
        ssh "$sshdomain" "cat > $destpath/$name"
fi

echo "$destdomain/$name"

