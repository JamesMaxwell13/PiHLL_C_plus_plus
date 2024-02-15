cmake_minimum_required(VERSION 3.26)
project(3lab)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(3lab
        main.cpp
        product.cpp
        product.h
        users.cpp
        users.h)
