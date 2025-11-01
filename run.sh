#!/bin/sh
set -e

# 프로젝트 디렉토리로 이동
cd ./marking/

# build 디렉토리 생성 (이미 있으면 무시)
mkdir -p build
cd build

# CMake 설정 및 빌드
cmake ..
make