#!/usr/bin/env bash
set -eu

repos_url="https://github.com/atcoder/ac-library"
src=tmp/ac-library/
dst=./

if [[ -d "$src" ]]; then
   pushd "$src"
   git pull --force
   popd
else
   git clone "$repos_url" "$src"
fi
cp -v -a -f "$src"/atcoder "$dst"
