#!/usr/bin/env bash
set -eu

if [[ $# -lt 1 ]]; then
   echo "usage: $0 problem_prefix" >&2
   exit 1
fi

# Increase stack size
if [[ $(ulimit -s) < 1048576 ]]; then
   ulimit -s 1048576
fi

prefix="$1"
bin=bin/${prefix}.out
make "$bin"

txt="${2:-${prefix}.txt}"
mkdir -p tmp
rm -rf tmp/${prefix}_*
csplit \
    --quiet \
    --prefix=tmp/${prefix}_ \
    --suffix-format=%02d.txt \
    --suppress-matched \
    "$txt" /^$/ {*}
for i in tmp/${prefix}_*.txt; do
   echo "==> Test case '$i':"
   "./$bin" < "${i}"
done
