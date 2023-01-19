#!/bin/bash

function TestWithOptions() {
    ./s21_grep -$1 tes $2 > ./result.txt
    grep -$1 tes $2 > ./result_cat.txt
    diff -s ./result_cat.txt ./result.txt
}

function SimpleTest() {
    ./s21_grep tes $1 > ./result.txt
    grep tes $1 > ./result_cat.txt
    diff -s ./result_cat.txt ./result.txt
}

function ETest() {
    ./s21_grep -e rr $1 > ./result.txt
    grep -e rr $1 > ./result_cat.txt
    diff -s ./result_cat.txt ./result.txt
}

function FTest() {
    ./s21_grep -f temp.txt $1 > ./result.txt
    grep -f temp.txt $1 > ./result_cat.txt
    diff -s ./result_cat.txt ./result.txt
}

function IVTest() {
    ./s21_grep -iv TEST $1 > ./result.txt
    grep -iv TEST $1 > ./result_cat.txt
    diff -s ./result_cat.txt ./result.txt
}

function INTest() {
    ./s21_grep -in TEST $1 > ./result.txt
    grep -in TEST $1 > ./result_cat.txt
    diff -s ./result_cat.txt ./result.txt
}

array=(e i v c l n h s o)
name=text.txt
for item in ${array[*]}
do
    printf "\n\t OPTION:%c FILE:correct\n" $item
    TestWithOptions "$item" "$name"
done

printf "\n\tOPTION:none FILE:correct\n"
SimpleTest "$name"

printf "\n\tOPTION:e_extend FILE:correct\n"
ETest "$name"

printf "\n\tOPTION:f FILE:correct\n"
FTest "$name"

printf "\n\tOPTION:iv FILE:correct\n"
IVTest "$name"

printf "\n\tOPTION:in FILE:correct\n"
INTest "$name"
