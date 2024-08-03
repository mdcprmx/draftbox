#!/bin/bash

for i in one two three; do
    echo "$i"
done

counter=1
while [ $counter -le 3 ]; do
    # le is less or equal
    echo "nash while: $counter"
    let counter++
done






