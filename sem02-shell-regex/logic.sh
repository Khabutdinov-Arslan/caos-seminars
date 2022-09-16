#!/usr/bin/bash

ping 8.8.8.8 -c 1 || echo "8.800.555.3535 not found"
ping 8232324.8.8.8 -c 1  && echo "8.8.8.8 found"

IFS=:
while read token
do 
echo "Token is: $token"
done