CMAKE_MINIMUM_REQUIRED(VERSION 3.14)
project(chip8)

set(CMAKE_CXX_STANDARD 11)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})

ADD_EXECUTABLE(
    chip8
    src/main.cpp
    src/Chip8.cpp
    src/Platform.cpp)

target_compile_options(chip8 PRIVATE -Wall)

target_link_libraries(chip8 ${SDL2_LIBRARY} )

#target_link_libraries(chip8 PRIVATE SDL2::SDL2)