#!/bin/bash

path="./marking/resource"

file=$(find "$path" -maxdepth 1 -type f -name "main.*" | head -n 1)

ext=$1
problem_id=$2
user_id=$3

file=./marking/resource/main.$ext

cat > $file

case $ext in
    "c") 
        gcc $file -o "$path/a.out"
        cd ./marking/build
        ./program $ext $problem_id $user_id
        ;;
    "cpp") 
        g++ $file -o "$path/a.out"
        cd ./marking/build
        ./program $ext $problem_id $user_id
        ;;
    "python")
        cd ./marking/build
        ./program $ext $program_id $user_id
        ;;
esac