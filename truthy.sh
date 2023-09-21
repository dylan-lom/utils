#!/bin/sh
_truthy_lower() {
	echo "$@" | tr '[[:upper:]]' '[[:lower:]]'
}

_truthy_isnum() {
	echo "$@" | grep -Eq '^-?[0-9]*\.?[0-9]*[fdu]?$'
}

_truthy_digits() {
	echo "$@" | tr -dc '[[:digit:]]'
}

truthy() {
	arg="$(_truthy_lower $1)"
	if [ -z "$arg" ]; then
		return 1
	elif _truthy_isnum "$arg"; then
		test $(_truthy_digits "$arg") -ne 0
	else
		test "$arg" != 'false' -a "$arg" != 'null'
	fi
}

if (echo "$0" | grep -q 'truthy'); then
	truthy "$@"
fi

