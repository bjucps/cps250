#!/bin/sh

tr -s ' \t' '\n' < "$1" | tr -dc 'a-zA-Z\n'
