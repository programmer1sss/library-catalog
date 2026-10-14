cmake_minimum_required(VERSION 3.16)
project(library_catalog CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(library_catalog
    src/main.cpp
    src/book.cpp
)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(library_catalog PRIVATE
        -Wall
        -Wextra
        -fsanitize=address,undefined
        -fno-omit-frame-pointer
        -g
    )
    target_link_options(library_catalog PRIVATE
        -fsanitize=address,undefined
    )
endif()
