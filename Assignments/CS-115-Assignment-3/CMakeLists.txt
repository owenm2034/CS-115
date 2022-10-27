cmake_minimum_required(VERSION 3.23)
project(CS_115_Assignment_3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(CS_115_Assignment_3
        Item.cpp
        Item.h
        Location.cpp
        Location.h
        main.cpp
        World.cpp
        World.h)
