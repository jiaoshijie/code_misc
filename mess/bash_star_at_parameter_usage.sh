#!/usr/bin/env bash

# Usage: ./bash_star_at_parameter_usage.sh 'a b' 'cd'

# IFS='%'  # control word spliting
# IFS=' %'

fname() {
  echo $#
  var=$#
  while ((var--)); do
    var_string="$((var + 1)) = \$$((var + 1))"
    eval "echo $var_string"
  done
  echo
}

fname $*
fname "$*"

fname $@
fname "$@"
