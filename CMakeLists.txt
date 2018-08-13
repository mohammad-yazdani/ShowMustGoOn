cmake_minimum_required(VERSION 3.5)
project(simorgh C)

set(CMAKE_C_STANDARD 11)

include_directories(src/include)

add_executable(simorgh
    src/include/json.h
    src/include/page.h
    src/include/fileio.h
    src/include/usr/iter_event.h
    src/lib/json.c
    src/lib/page.c
    src/lib/fileio.c
    src/lib/usr/iter_event.c
    main.c src/lib/strutil.c src/include/strutil.h)

