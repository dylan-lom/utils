#!/bin/sh

test -n "$CONFIRM_UNKNOWN_EXIT" || CONFIRM_UNKNOWN_EXIT=255
word=false # match whole words (-w)

_confirm_echo_n() {
        printf "$@"
}

_confirm_upper() {
        echo "$@" | tr '[[:lower:]]' '[[:upper:]]'
}

_confirm_isspace() {
        test -z "$(echo "$1" | tr -d '[[:space:]]')"
}

_confirm_startswith() {
        echo "$2" | grep -qi "^$1.*$"
}

_confirm_contains() {
        echo "$2" | grep -qi "$1"
}

_confirm_matchopt() {
        sel="$1"
        (! _confirm_isspace "$sel") || return 0

        shift

        i=0
        for opt in "$@"; do
                if (
                        test "$sel" = "$opt" \
                        || (test "$word" = false && _confirm_startswith "$sel" "$opt")
                ); then
                        return "$i"
                fi

                i="$((i + 1))"
        done

        return $CONFIRM_UNKNOWN_EXIT
}

# Get user confirmation
# Examples:
#   $ confirm
#   $ confirm "Exit?"
#   $ confirm "Download file?" n y
#   $ confirm "What color?" red yellow blue
#   $ confirm -w "What color?" red yellow blue # check whole word
confirm() {
        if [ "$1" = "-w" ]; then
                word=true
                shift
        fi

        if [ "$#" -eq 0 ]; then
                confirm "Are you sure?" "y" "n"
                return $?
        fi

        prompt="$1"
        shift

        if [ "$#" -eq 0 ]; then
                confirm "$prompt" "y" "n"
                return $?
        fi

        _confirm_echo_n "$prompt ["
        i=0
        for opt in "$@"; do
                test $i -eq 0 \
                        && opt="$(_confirm_upper "$opt")" \
                        || opt="/$opt"
                _confirm_echo_n "$opt"
                i="$((i+1))"
        done
        _confirm_echo_n "]: "

        read sel
        _confirm_matchopt "$sel" "$@"
}

if _confirm_contains "confirm" "$0"; then
        confirm "$@"
fi

