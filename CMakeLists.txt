cmake_minimum_required(VERSION 3.14)
project(LibraryDB)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXE_LINKER_FLAGS -static)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -s -O1")

add_executable(LibraryDB
        main.cpp
        Record.hpp
        Record.cpp
        DataKeeper.hpp
        DataKeeper.cpp
        )