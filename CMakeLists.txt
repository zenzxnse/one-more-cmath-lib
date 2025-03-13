cmake_minimum_required(VERSION 3.10)

project(CMathematics C)

include_directories(headers)

set(SOURCES src/main.c src/vec.c)

add_executable(CMathematics ${SOURCES})