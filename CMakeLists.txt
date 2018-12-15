cmake_minimum_required(VERSION 3.5.1)

project(eval CXX)

set(CMAKE_CXX_STANDARD  11)
set(CMAKE_CXX_FLAGS     "${CMAKE_CXX_FLAGS} -Wall -pedantic -O3 -mtune=native -march=native -lm")

set(SOURCES   src/main.cpp
              src/Parser.hpp
              src/Parser.cpp
              src/print_stl.hpp
              src/ShuntingYard.hpp
              src/ShuntingYard.cpp
              src/Calculator.hpp
              src/Calculator.cpp)

add_executable(eval ${SOURCES})
target_include_directories(eval PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

install(TARGETS eval DESTINATION /usr/bin)
