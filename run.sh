#!/bin/sh
set -e

# 프로젝트 디렉토리로 이동
cd ./marking/

# resource, output, build 디렉토리 생성
mkdir -p resource output build

cd build

# CMake 설정 및 빌드
cmake ..
make