cmake_minimum_required(VERSION 3.25)
project(sstr C)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_COMPILER "gcc")

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fstack-protector-all")

add_executable(sstr main.c sstr.h)
