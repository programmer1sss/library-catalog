cmake_minimum_required(VERSION 3.16)
project(Cookbook LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ── Опції ──
option(ENABLE_SANITIZERS "Build with ASan and UBSan" OFF)

# ── Спільні попередження ──
set(PROJECT_WARNINGS -Wall -Wextra -Wpedantic)

# ── Допоміжна функція для застосування санітайзерів (має бути до викликів!) ──
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
#  ДЕМО-ЦІЛІ (Кроки 1–6)
# ════════════════════════════════════════════════════════════════

# Демо Book (використовує TagList)
add_executable(book_demo
    src/main.cpp
    src/book.cpp
    src/TagList.cpp
)
target_compile_features(book_demo PRIVATE cxx_std_17)
target_include_directories(book_demo PRIVATE src)
apply_warnings_and_sanitizers(book_demo)

# Демо TagList (Кроки 1–4)
add_executable(taglist_demo
    taglist_demo.cpp
    src/TagList.cpp
)
target_compile_features(taglist_demo PRIVATE cxx_std_17)
target_include_directories(taglist_demo PRIVATE src)
apply_warnings_and_sanitizers(taglist_demo)

# Демо Move (Крок 5)
add_executable(move_demo
    move_demo.cpp
    src/TagList.cpp
)
target_compile_features(move_demo PRIVATE cxx_std_17)
target_include_directories(move_demo PRIVATE src)
apply_warnings_and_sanitizers(move_demo)

# Демо Library (Крок 6)
add_executable(library_demo
    library_demo.cpp
    src/book.cpp
    src/TagList.cpp
)
target_compile_features(library_demo PRIVATE cxx_std_17)
target_include_directories(library_demo PRIVATE src)
apply_warnings_and_sanitizers(library_demo)

# ════════════════════════════════════════════════════════════════
#  ТЕСТИ (Крок 7)
# ════════════════════════════════════════════════════════════════
enable_testing()

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.14.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# INTERFACE-бібліотека для TagListV2 (він header-only у src/taglistv2.h)
add_library(taglistv2 INTERFACE)
target_include_directories(taglistv2 INTERFACE src)

# Тест для TagList (Rule of Five)
add_executable(taglist_test
    tests/taglist_test.cpp
    src/TagList.cpp
)
target_compile_features(taglist_test PRIVATE cxx_std_17)
target_include_directories(taglist_test PRIVATE src)
target_link_libraries(taglist_test PRIVATE GTest::gtest_main)
apply_warnings_and_sanitizers(taglist_test)

# Тест для TagListV2 (Rule of Zero)
add_executable(taglistv2_test
    tests/taglistv2_test.cpp
)
target_compile_features(taglistv2_test PRIVATE cxx_std_17)
target_link_libraries(taglistv2_test PRIVATE GTest::gtest_main taglistv2)
apply_warnings_and_sanitizers(taglistv2_test)

include(GoogleTest)
gtest_discover_tests(taglist_test)
gtest_discover_tests(taglistv2_test)
