cmake_minimum_required(VERSION 3.29)
project(AoC24)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(AoC24 main.cpp
        colors.h
        days/Day01.cpp
        days/Day01.h
        common.h
        days/Day02.cpp
        days/Day02.h
        days/Day03.cpp
        days/Day03.h
        days/Day04.cpp
        days/Day04.h
        days/Day05.cpp
        days/Day05.h
        days/Day06.cpp
        days/Day06.h
        days/Day07.cpp
        days/Day07.h
        days/Day08.cpp
        days/Day08.h
        days/Day09.cpp
        days/Day09.h
        days/Day10.cpp
        days/Day10.h
)
