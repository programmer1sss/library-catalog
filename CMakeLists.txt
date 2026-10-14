cmake_minimum_required(VERSION 3.16)
project(library_catalog CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ─── Основна ціль ───
add_executable(library_catalog
    src/main.cpp
    src/book.cpp
)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(library_catalog PRIVATE
        -Wall -Wextra
        -fsanitize=address,undefined
        -fno-omit-frame-pointer
        -g
    )
    target_link_options(library_catalog PRIVATE
        -fsanitize=address,undefined
    )
endif()

# ─── Тести ───
enable_testing()

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.14.0
)
# Для Windows: уникнути конфлікту CRT
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(book_test
    tests/book_test.cpp
    src/book.cpp
)

target_include_directories(book_test PRIVATE src)

target_link_libraries(book_test
    PRIVATE
        GTest::gtest_main
)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(book_test PRIVATE
        -Wall -Wextra
        -fsanitize=address,undefined
        -fno-omit-frame-pointer
        -g
    )
    target_link_options(book_test PRIVATE
        -fsanitize=address,undefined
    )
endif()

include(GoogleTest)
gtest_discover_tests(book_test)
