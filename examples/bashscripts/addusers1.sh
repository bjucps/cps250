#!/bin/bash

while read line
do
    fullname=$(echo $line | awk -F, '{print $1,$2 }')
    username=$(echo $line | awk -F, '{print $3}')
    useradd $username --name="$fullname" --homedir=/home/$username
    #echo $line
done < users.txt
