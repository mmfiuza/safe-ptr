# Copyright (c) 2025 Matheus Machado Fiuza <matheusmachadofiuza@gmail.com>

cmake_minimum_required(VERSION 3.5)
project(SafePtr LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)

set(INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include)

# examples
if(BUILD_EXAMPLES)
    set(EXAMPLE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/examples/basic-usage.cpp)
    add_executable(basic-usage ${EXAMPLE_SOURCES})
    target_include_directories(basic-usage PUBLIC ${INCLUDE_DIRECTORIES})
endif()

# tests
if(BUILD_TESTS)
    set(TESTS_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tests/test-all.cpp)

    # Executable with SAFE_PTR_DEBUG defined
    add_executable(test-all-debug ${TESTS_SOURCES})
    target_include_directories(test-all-debug PUBLIC
        ${INCLUDE_DIRECTORIES}
        ${CMAKE_CURRENT_SOURCE_DIR}/tests
    )
    target_compile_definitions(test-all-debug PRIVATE SAFE_PTR_DEBUG)

    # Executable without SAFE_PTR_DEBUG
    add_executable(test-all ${TESTS_SOURCES})
    target_include_directories(test-all PUBLIC
        ${INCLUDE_DIRECTORIES}
        ${CMAKE_CURRENT_SOURCE_DIR}/tests
    )
    # no extra compile definitions
endif()