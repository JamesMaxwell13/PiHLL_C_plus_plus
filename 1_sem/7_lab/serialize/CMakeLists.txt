cmake_minimum_required(VERSION 3.27)
project(serialize)

set(CMAKE_CXX_STANDARD 23)

add_executable(serialize
        serialization.cpp
        template_list.cpp
        template_list.h
        MyString.cpp
        MyString.h)
