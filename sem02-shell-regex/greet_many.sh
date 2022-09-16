#!/usr/bin/bash

echo "Prepare to greet $# people."
for person in $@
do
    echo "Hello, $person!"
done

paths="Vasya:Petya:Vanya"
IFS=:
for person in $paths:
do
    echo $person
done
