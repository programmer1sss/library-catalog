cmake_minimum_required(VERSION 3.16)
project(LibraryCatalog LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ── Опції ──
option(ENABLE_SANITIZERS "Build with ASan and UBSan" OFF)

# ── Спільні попередження ──
set(PROJECT_WARNINGS -Wall -Wextra -Wpedantic)

# ── Допоміжна функція для санітайзерів ──
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
#  ГОЛОВНА ПРОГРАМА (ЛР5 + ЛР6 крок 1)
# ════════════════════════════════════════════════════════════════

add_executable(book_demo
    src/main.cpp
    src/book.cpp
    src/TagList.cpp
    src/Money.cpp
    src/library.cpp
    src/LibraryItem.cpp        # ← додано на Кроці 1 ЛР6
)
target_compile_features(book_demo PRIVATE cxx_std_17)
target_include_directories(book_demo PRIVATE src)
apply_warnings_and_sanitizers(book_demo)

# ════════════════════════════════════════════════════════════════
#  ТЕСТИ (GoogleTest)
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

# ── Тести операторів (Крок 7 ЛР5) ──
add_executable(test_operators
    tests/test_operators.cpp
    src/Money.cpp
    src/book.cpp
    src/TagList.cpp
    src/LibraryItem.cpp        # ← додано на Кроці 1 ЛР6
)
target_compile_features(test_operators PRIVATE cxx_std_17)
target_include_directories(test_operators PRIVATE src)
target_link_libraries(test_operators PRIVATE GTest::gtest_main)
apply_warnings_and_sanitizers(test_operators)

include(GoogleTest)
gtest_discover_tests(test_operators)