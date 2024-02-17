#!/bin/bash

for OPTION in "" "-s" "-t" "-T" "-e" "-E" "-b" "-n" "-tesnbTE"
do

    diff <(./s21_cat ${OPTION} ayo.txt) <(cat ${OPTION} ayo.txt)

done
