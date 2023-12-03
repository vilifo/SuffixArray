cmake_minimum_required(VERSION 3.22)
project(NI_EVY)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

set(CMAKE_CXX_FLAGS -DDEBUG)
#set(CMAKE_CXX_FLAGS -DTESTING)

add_executable(NI_EVY
        NaiveAlgorithm.cpp
        NaiveAlgorithm.h
        suffixArray.cpp
        suffixArray.h
        test.cpp
        printFunctions.h
        printFunctions.cpp)
