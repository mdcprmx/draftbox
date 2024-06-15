#!/bin/bash
CNTR_SUCCESS=0
CNTR_FAIL=0
TEST_FILE1="./test_cache/1.txt"
TEST_FILE2="./test_cache/1.txt ./test_cache/2.txt ./test_cache/3.txt ./test_cache/test.txt"
PATTERN1="a"
PATTERN2="test"

all_flags=(-i -v -c -l -n -e -s -h)

echo "Test started. Wait..."

for var in ${all_flags[@]}
do
    TEST="$var $PATTERN2 $TEST_FILE2"
    ./s21_grep $TEST > school_grep.txt
    grep $TEST > original_grep.txt
    DIFF_RES="$(diff -s school_grep.txt original_grep.txt)"
    if [ "$DIFF_RES" == "Files school_grep.txt and original_grep.txt are identical" ]
        then
            ((CNTR_SUCCESS++))
        else
            echo "Test case $var failed! oh noes"
            ((CNTR_FAIL++))
    fi
done

rm original_grep.txt school_grep.txt
echo "SUCCESS: $CNTR_SUCCESS"
echo "FAIL: $CNTR_FAIL"