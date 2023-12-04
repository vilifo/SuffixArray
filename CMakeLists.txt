cmake_minimum_required(VERSION 3.22)
project(NI_EVY)

set(CMAKE_CXX_STANDARD 14)

#add_definitions(-DDEBUG)
include_directories(.)

add_executable(NI_EVY
        NaiveAlgorithm.cpp
        NaiveAlgorithm.h
        printFunctions.cpp
        printFunctions.h
        suffixArray.cpp
        suffixArray.h
        test.cpp)
