#!/usr/bin/env bash
set -eu

root_dir="$(cd "$(dirname "$0")"/..; pwd)"

repos_url="https://github.com/atcoder/ac-library"
src="$root_dir"/tmp/ac-library
dst="$root_dir"/

if [[ -d "$src" ]]; then
   pushd "$src"
   git pull --force
   popd
else
   git clone "$repos_url" "$src"
fi
cp -v -a -f "$src"/atcoder "$dst"
