# Copyright (c) 2025 Matheus Machado Fiuza <matheusmachadofiuza@gmail.com>

cmake_minimum_required(VERSION 3.5) # TODO: check the minimum required
project(SafePtr LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20) # TODO: check the minimum required 

set(EXAMPLE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/examples/basic-usage.cpp)
set(INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(basic-usage ${EXAMPLE_SOURCES})

target_include_directories(basic-usage PUBLIC ${INCLUDE_DIRECTORIES})
