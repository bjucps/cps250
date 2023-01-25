#!/bin/bash

function addtheuser {
    local USERNAME FULLNAME
    USERNAME=$1
    FULLNAME=$2

    useradd $USERNAME --name="$FULLNAME" --homedir=/home/$USERNAME

}

while read line
do
    fullname=$(echo $line | awk -F, '{print $1,$2 }')
    username=$(echo $line | awk -F, '{print $3}')
    addtheuser "$username" "${fullname}"
    #echo $line
done < users.txt
