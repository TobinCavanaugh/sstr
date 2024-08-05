cmake_minimum_required(VERSION 3.25)
project(sstr C)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_COMPILER "gcc")

#-D_FORTIFY_SOURCE=3
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -fstack-protector-all")

#set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O3")

add_executable(sstr main.c sstr.h)
