#!/usr/bin/bash

echo "Prepare to greet $# people."
for person in $@
do
    echo "Hello, $person!"
done
