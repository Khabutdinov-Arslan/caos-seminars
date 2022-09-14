#!/usr/bin/bash

function greet_person() {
    if [[ $1 == "Arslan" ]]; then
        echo "Again, $1?"
    else
        echo "Hello, $1!"
    fi
}

echo "Prepare to greet $# people."
for person in $@
do
    greet_person $person
done
