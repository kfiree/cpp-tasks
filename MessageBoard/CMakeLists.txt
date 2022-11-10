cmake_minimum_required(VERSION 3.19)
project(MessageBoard)

set(CMAKE_CXX_STANDARD 14)

add_executable(MessageBoard main.cpp Board.cpp Board.hpp Direction.hpp)