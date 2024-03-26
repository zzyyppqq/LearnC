cmake_minimum_required(VERSION 3.17)
cmake_policy(VERSION 3.17)
project(assembly)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
enable_language(C ASM)
#enable_language(ASM_NASM)

add_executable(asm_hello mac_hello.S)
add_executable(asm_exit mac_exit.s)
#add_executable(asm_first mac_first.asm)

