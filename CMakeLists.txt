cmake_minimum_required(VERSION 3.0)
project(main C)

option(CMAKE_VERBOSE_MAKEFILE OFF)

aux_source_directory(uart UART)
aux_source_directory(delay DELAY)

include_directories(uart delay)

set (SRC main.c ${UART} ${DELAY})

add_executable(${PROJECT_NAME} ${SRC})

generate_bin(${PROJECT_NAME})
