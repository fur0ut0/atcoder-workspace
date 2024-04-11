#!/usr/bin/env bash
set -eu

function confirm_exec() {
   cmd="$1"

   echo "----------------------------"
   echo "You are going to execute '$cmd'"
   echo "If you want to continue, input 'yes'"
   read input

   if [ $input = 'yes' ] || [ $input = 'YES' ] || [ $input = 'y' ]; then
      echo "$cmd"
      eval "$cmd"
      return 0
   else
      return 1
   fi
}

cmd="git reset --hard"
confirm_exec "$cmd"
