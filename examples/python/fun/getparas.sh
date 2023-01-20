#!/bin/sh

sed 's/^$/___LINESEP___/g' < "$1" |
	tr -s '\t\n' ' ' |
	sed 's/ \?___LINESEP___ \?/\n/g'
