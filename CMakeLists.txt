cmake_minimum_required(VERSION 3.18)

project(sync_container)

set(CMAKE_C_STANDARD 11)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} \
        -fsanitize=address -fsanitize=undefined -g3 -O0 -Wno-ignored-qualifiers\
        -Wall -Werror -Wextra -Wpedantic -Wconversion -Wcast-align -Wunused -Wshadow \
        -Wpointer-arith -Wcast-qual -Wmissing-declarations -Wno-missing-braces \
        -Wstrict-prototypes -Wmissing-prototypes \
    ")
else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Ofast -funroll-loops")
endif()

add_subdirectory(lib)
add_subdirectory(tests)
