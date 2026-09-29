cmake_minimum_required(VERSION 3.16)
project(library_catalog CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(library_catalog
    src/main.cpp
    src/Book.cpp
)
