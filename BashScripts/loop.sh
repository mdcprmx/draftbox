#!/bin/bash

for X in {3..6}
do
    echo cycle is going $X
done

i=1
while [[ $i -le 15 ]]; do
    echo "$i"
    ((i += 3))
done

a=1
while [[ $a -le 10 ]]; do
    echo "desu"
    ((a++));
done





