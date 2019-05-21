cmake_minimum_required(VERSION 3.0)
project(main C)
set(CMAKE_VERBOSE_MAKEFILE OFF)
include_directories(
	uart
	delay
)
aux_source_directory(uart UART)
aux_source_directory(delay DELAY)
set (SRC
	main.c
	${UART}
	${DELAY}
)
add_executable(main ${SRC})
generate_bin(main)

