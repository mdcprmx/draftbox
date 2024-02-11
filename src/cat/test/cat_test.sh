#!/bin/bash

cp ../s21_cat .

for OPTION in "" "-s" "-t" "-T" "-e" "-E" "-b" "-n" "-tesnbTE"
do 

    diff <(./s21_cat ${OPTION} ayo.txt) <(cat ${OPTION} ayo.txt)

done

	valgrind --tool=memcheck --leak-check=yes ./s21_cat ayo.txt