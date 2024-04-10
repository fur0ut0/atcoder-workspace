#!/usr/bin/env bash
set -eu

if [[ $# -lt 1 ]]; then
   echo "usage: $0 basename [mode]" >&2
   exit 1
fi

# Increase stack size
if [[ $(ulimit -s) < 1048576 ]]; then
   ulimit -s 1048576
fi

basename="$1"
txt="$1.txt"
mode="${2:-release}"

BASENAME=$basename make $mode

if [[ $mode == "debug" ]]; then
   bin=bin/debug/${basename}.out
else
   bin=bin/${basename}.out
fi

mkdir -p tmp
rm -rf tmp/${basename}_*
csplit \
    --quiet \
    --prefix=tmp/${basename}_ \
    --suffix-format=%02d.txt \
    --suppress-matched \
    "$txt" /^$/ {*}

for i in tmp/${basename}_*.txt; do
   echo "==> Test case '$i':"
   "./$bin" < "${i}"
done
