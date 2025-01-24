cmake_minimum_required(VERSION 3.5)

project(hw3)

add_executable(
	guess_the_number
	functions.h
	check_value.cpp
	random_value.cpp
	read_from_file.cpp
	write_in_file.cpp
	main.cpp
)

