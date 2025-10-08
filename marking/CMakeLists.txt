# CMake 프로그램의 최소 버전
cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 프로젝트 정보
project(
  MarkingProgram
  VERSION 0.1
  DESCRIPTION "채점 프로그램"
  LANGUAGES CXX)

add_executable (program main.cpp)

target_include_directories(program PRIVATE
    /usr/include/mariadb
)
# 라이브러리 링크
target_link_libraries(program PRIVATE
    mariadbcpp
)