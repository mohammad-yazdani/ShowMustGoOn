cmake_minimum_required(VERSION 3.12)
project(s0 C)

set(CMAKE_C_STANDARD 99)

include_directories(src/include)
include_directories(src/include/usr)

add_executable(s0
        src/include/usr/analysis.h
        src/include/usr/iter_event.h
        src/include/io/fileio.h
        src/include/util/json.h
        src/include/page.h
        src/include/util/strutil.h
        src/lib/usr/iter_event.c
        src/lib/io/fileio.c
        src/lib/util/json.c
        src/lib/page.c
        src/lib/util/strutil.c
        src/test/json_test.c
        src/test/page_test.c
        main.c src/include/usr/contract.h src/lib/usr/contract.c src/include/usr/iter_event.h src/include/io/fileio.h src/include/util/json.h src/include/page.h src/include/util/strutil.h src/include/queue.h src/lib/queue.c src/include/linked.h src/lib/usr/analysis.c src/include/io/db.h src/lib/io/db.c src/test/db.c src/lib/tlb.c src/include/tlb.h)

include_directories(/usr/include)
link_directories(/usr/lib)
target_link_libraries(s0 sqlite3)