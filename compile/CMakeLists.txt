# CMake 프로그램의 최소 버전
cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 프로젝트 정보
project(
  CompileProgram
  VERSION 0.1
  DESCRIPTION "컴파일 프로그램"
  LANGUAGES CXX)

add_executable (program main.cpp)