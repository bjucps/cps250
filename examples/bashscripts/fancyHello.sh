#!/bin/bash
# Demonstrates the use of a function

function FancyHello {
  local MYNAME

  if [ $# -gt 0 ]; then
    for MYNAME in "$@"; do
      echo "Hello $MYNAME"
    done
  else
    echo "What is your name?"
    read MYNAME
    if [ -z "$MYNAME" ]; then
      echo "Hello world."
    else
      FancyHello $MYNAME
    fi
  fi
}

FancyHello "$@"

