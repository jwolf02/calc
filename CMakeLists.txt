cmake_minimum_required(VERSION 3.5.1)

project(calc CXX)

set(CMAKE_CXX_STANDARD  11)
set(CMAKE_CXX_FLAGS     "${CMAKE_CXX_FLAGS} -Wall -pedantic -O3 -mtune=native -march=native -lm")

set(SOURCES   src/main.cpp
        src/print_stl.hpp
              src/calc.hpp
              src/calc.cpp
        src/expression.hpp
        src/expression.cpp
              src/token.hpp
              src/token.cpp)

add_executable(calc ${SOURCES})
target_include_directories(calc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

install(TARGETS calc DESTINATION /usr/bin)
