#!/usr/bin/env bash
set -eu

if [[ $# -lt 1 ]]; then
   echo "usage: $0 problem_prefix" >&2
   exit 1
fi

prefix="$1"
bin=bin/${prefix}.out
make "$bin"
mkdir -p tmp
csplit \
    --quiet \
    --prefix=tmp/${prefix}_ \
    --suffix-format=%02d.txt \
    --suppress-matched \
    ${prefix}.txt /^$/ {*}
for i in tmp/${prefix}_*.txt; do
   "./$bin" < "${i}"
done