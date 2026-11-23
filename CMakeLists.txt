cmake_minimum_required(VERSION 3.16)
project(LibraryCatalog LANGUAGES CXX)

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

add_executable(book_demo
    src/main.cpp
    src/book.cpp
    src/TagList.cpp
    src/Money.cpp
    src/library.cpp
    src/LibraryItem.cpp
    src/Periodical.cpp
    src/Newspaper.cpp
    src/printCard.cpp
    src/Reader.cpp
    src/Loan.cpp
)
target_compile_features(book_demo PRIVATE cxx_std_17)
target_include_directories(book_demo PRIVATE src)
apply_warnings_and_sanitizers(book_demo)

enable_testing()

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.14.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(test_operators
    tests/test_operators.cpp
    src/Money.cpp
    src/book.cpp
    src/TagList.cpp
    src/LibraryItem.cpp
    src/Periodical.cpp
    src/Newspaper.cpp
    src/printCard.cpp
    src/Reader.cpp
    src/Loan.cpp
)
target_compile_features(test_operators PRIVATE cxx_std_17)
target_include_directories(test_operators PRIVATE src)
target_link_libraries(test_operators PRIVATE GTest::gtest_main)
apply_warnings_and_sanitizers(test_operators)

add_executable(test_loan_reader
    tests/test_loan_reader.cpp
    src/Reader.cpp
    src/Loan.cpp
    src/book.cpp
    src/TagList.cpp
    src/LibraryItem.cpp
)
target_compile_features(test_loan_reader PRIVATE cxx_std_17)
target_include_directories(test_loan_reader PRIVATE src)
target_link_libraries(test_loan_reader PRIVATE GTest::gtest_main)
apply_warnings_and_sanitizers(test_loan_reader)

include(GoogleTest)
gtest_discover_tests(test_operators)
gtest_discover_tests(test_loan_reader)