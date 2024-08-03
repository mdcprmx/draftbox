#!/bin/bash
# ПРОБЕЛЫ ЖЕСТЬ КАК ВАЖНЫ ОКАЦА

buffer=$(grep echo "$1" -c -h )

if [ "$buffer" -ge 500 ]; then
    echo "that file is longer than 500 lines!"
else
    echo "lesser than 500 bro"
fi