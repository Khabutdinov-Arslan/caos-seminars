#!/usr/bin/bash

function greet_person() {
    if [[ $1 == "Arslan" && false ]]; then
        echo "Again, $1?"
    else
        echo "Hello, $1!"
    fi
    echo "Person greeted."
}

echo "Prepare to greet $# people."
for person in $@
do
    echo $(greet_person $person)
    echo $person
    greet_person $person
done
