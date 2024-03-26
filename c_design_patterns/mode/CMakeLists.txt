cmake_minimum_required(VERSION 3.25)
project(c_design_patterns C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)


add_executable(c_single single/c_single.c)
add_executable(cpp_single single/cpp_single.cpp)

add_executable(combination_file combination/file/file.c combination/file/folder.c combination/file/main.c)


