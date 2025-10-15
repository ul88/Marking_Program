#!/bin/bash

path="../resource"

file=$(find "$path" -maxdepth 1 -type f -name "main.*" | head -n 1)

if [ -n "$file" ]; then
    echo "파일 존재함"
    echo "파일 이름: $file"

    ext="${file##*.}"
    echo "확장자 이름 : $ext"

    case $ext in
        "c") 
            gcc $file -o "$path/a.out"
            cd /home/hanul/coding/marking_program/marking/build
            ./program $ext 1
            ;;
        "cpp") 
            g++ $file -o "$path/a.out"
            cd /home/hanul/coding/marking_program/marking/build
            ./program $ext 1
            ;;
    esac
else
    echo "파일 없음"
fi
