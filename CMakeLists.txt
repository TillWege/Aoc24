cmake_minimum_required(VERSION 3.29)
project(AoC24)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(AoC24 main.cpp
        colors.h
        days/Day01.cpp
        days/Day01.h
)

