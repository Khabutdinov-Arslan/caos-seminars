#!/usr/bin/bash

friends=("Frodo" "Sam" "Merry" "Pippin")

echo "Prepare to greet ${#friends[@]} people."
for i in {0..3}
do
    echo "Hello, ${friends[$i]}!"
done
