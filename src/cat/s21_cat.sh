#!/bin/bash

function TestWithOptions() {
    ./s21_cat -$1 $2 > ./result.txt
    cat -$1 $2 > ./result_cat.txt
    diff -s ./result_cat.txt ./result.txt
}

function TestWithGnu() {
    ./s21_cat -$1 $2 > ./result.txt
    cat -$3 $2 > ./result_cat.txt
    diff -s ./result_cat.txt ./result.txt
}

function SimpleTest() {
    ./s21_cat $1 > ./result.txt
    cat $1 > ./result_cat.txt
    diff -s ./result_cat.txt ./result.txt
}

array=(b n s e t)
gnu_array=(-number-nonblank -number -squeeze-blank)
name=test.txt
for item in ${array[*]}
do
    printf "\n\t OPTION:%c FILE:correct\n" $item
    TestWithOptions "$item" "$name"
done

for index in ${!gnu_array[*]}
do
    printf "\n\tOPTTION:-%s FILE:correct\n" ${gnu_array[$index]}
    TestWithGnu "${gnu_array[$index]}" "$name" "${array[$index]}"
done

printf "\n\tOPTION:none FILE:correct\n"
SimpleTest "$name"
