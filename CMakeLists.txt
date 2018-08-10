cmake_minimum_required(VERSION 3.5)
project(simorgh C)

set(CMAKE_C_STANDARD 11)

include_directories(src/include)

add_subdirectory(./src/usr)

add_executable(simorgh
    src/include/json.h
    src/include/page.h
    src/include/fileio.h
    src/lib/json.c
    src/lib/page.c
    src/lib/fileio.c
    main.c src/lib/strutil.c src/include/strutil.h)
target_link_libraries(simorgh simorgh_user)
