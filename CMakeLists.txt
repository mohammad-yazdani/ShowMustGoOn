cmake_minimum_required(VERSION 3.10)
project(simorgh C)

set(CMAKE_C_STANDARD 99)

include_directories(src/include)
link_directories(src/lib)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "./bin")

add_executable(simorgh ./src/lib/page.c main.c)
