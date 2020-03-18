#!/bin/bash

awk -F, '{print "useradd -c \"" $1,$2 "\" " $3}' users.txt | bash

