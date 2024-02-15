cmake_minimum_required(VERSION 3.26)
project(withptr)

set(CMAKE_CXX_STANDARD 20)

add_executable(withptr main.cpp
        menu.cpp
        MyString.cpp)
