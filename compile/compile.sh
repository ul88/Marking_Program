#!/bin/bash

path="../marking/resource"

file=$(find "$path" -maxdepth 1 -type f -name "main.*" | head -n 1)

problem_id=$1
user_id=$2

if [ -n "$file" ]; then
    echo "파일 존재함"
    echo "파일 이름: $file"

    ext="${file##*.}"
    echo "확장자 이름 : $ext"

    case $ext in
        "c") 
            gcc $file -o "$path/a.out"
            cd ../marking/build
            ./program $ext $problem_id $user_id
            ;;
        "cpp") 
            g++ $file -o "$path/a.out"
            cd ../marking/build
            ./program $ext $problem_id $user_id
            ;;
    esac
else
    echo "파일 없음"
fi
