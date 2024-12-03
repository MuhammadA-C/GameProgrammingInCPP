cmake_minimum_required(VERSION 3.29)
project(Chapter2)

set(CMAKE_CXX_STANDARD 20)

add_executable(Chapter2 main.cpp
        Actor.cpp
        Actor.h
        Component.cpp
        Component.h)
