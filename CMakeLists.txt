cmake_minimum_required(VERSION 3.16)
project(Cookbook LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENABLE_SANITIZERS "Build with ASan and UBSan" OFF)
set(PROJECT_WARNINGS -Wall -Wextra -Wpedantic)

function(apply_warnings_and_sanitizers target)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(${target} PRIVATE ${PROJECT_WARNINGS} -g)
        if(ENABLE_SANITIZERS)
            target_compile_options(${target} PRIVATE
                -fsanitize=address,undefined
                -fno-omit-frame-pointer -g
            )
            target_link_options(${target} PRIVATE
                -fsanitize=address,undefined
            )
        endif()
    endif()
endfunction()

# ════════════════════════════════════════════════════════════════
#  ДЕМО-ЦІЛІ (Кроки 1–6 ЛР4 + Кроки 1-5 ЛР5)
# ════════════════════════════════════════════════════════════════

# Демо Book (використовує TagList та Money)
add_executable(book_demo
    src/main.cpp
    src/book.cpp
    src/TagList.cpp
    src/Money.cpp
)
target_compile_features(book_demo PRIVATE cxx_std_17)
target_include_directories(book_demo PRIVATE src)
apply_warnings_and_sanitizers(book_demo)

# Тести (якщо є)
enable_testing()

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.14.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(taglistv2 INTERFACE)
target_include_directories(taglistv2 INTERFACE src)

add_executable(taglist_test
    tests/taglist_test.cpp
    src/TagList.cpp
)
target_compile_features(taglist_test PRIVATE cxx_std_17)
target_include_directories(taglist_test PRIVATE src)
target_link_libraries(taglist_test PRIVATE GTest::gtest_main)
apply_warnings_and_sanitizers(taglist_test)

add_executable(taglistv2_test
    tests/taglistv2_test.cpp
)
target_compile_features(taglistv2_test PRIVATE cxx_std_17)
target_link_libraries(taglistv2_test PRIVATE GTest::gtest_main taglistv2)
apply_warnings_and_sanitizers(taglistv2_test)

include(GoogleTest)
gtest_discover_tests(taglist_test)
gtest_discover_tests(taglistv2_test)