cmake_minimum_required(VERSION 3.10)
project(simorgh C)

set(CMAKE_C_STANDARD 11)

include_directories(src/include)

add_executable(simorgh
    src/include/json.h
    src/include/page.h
    src/lib/json.c
    src/lib/page.c
    main.c)
