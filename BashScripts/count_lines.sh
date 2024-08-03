#!/bin/sh
# ПРОБЕЛЫ ВАЖНЫ
str=$(cat "$1" | wc -l)
echo "num of lines is: $str"