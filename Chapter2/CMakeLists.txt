cmake_minimum_required(VERSION 3.29)
project(Chapter2)

set(CMAKE_CXX_STANDARD 20)

# Set paths explicitly for SDL2 installed in /opt/homebrew/opt/sdl2
set(SDL2_INCLUDE_DIR /opt/homebrew/opt/sdl2/include/SDL2)
set(SDL2_LIBRARY /opt/homebrew/opt/sdl2/lib/libSDL2.dylib)

# Include SDL2 headers
include_directories(${SDL2_INCLUDE_DIR})


add_executable(Chapter2 main.cpp
        Actor.cpp
        Actor.h
        Component.cpp
        Component.h
        Game.cpp
        Game.h
        Math.cpp
        Math.h)

# Link SDL2 library
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})