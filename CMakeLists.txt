cmake_minimum_required(VERSION 3.12)
project(s0 C)

set(CMAKE_C_STANDARD 99)

include_directories(src/include)
include_directories(src/include/usr)

add_executable(s0
        src/include/usr/analysis.h
        src/include/usr/iter_event.h
        src/include/fileio.h
        src/include/json.h
        src/include/page.h
        src/include/stream.h
        src/include/strutil.h
        src/lib/usr/iter_event.c
        src/lib/fileio.c
        src/lib/json.c
        src/lib/page.c
        src/lib/strutil.c
        src/test/json_test.c
        src/test/page_test.c
        main.c src/include/usr/contract.h src/lib/usr/contract.c src/include/usr/iter_event.h src/include/fileio.h src/include/json.h src/include/page.h src/include/strutil.h)
