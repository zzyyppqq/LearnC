cmake_minimum_required(VERSION 3.21)
project(CppForAndroid)
#project(CppForAndroid CXX)


set(CMAKE_CXX_STANDARD 11)

set(NDK_HOME /Users/zhangyipeng/Library/Android/sdk/ndk/21.1.6352462)
set(CMAKE_CXX_COMPILER ${NDK_HOME}/toolchains/llvm/prebuilt/darwin-x86_64/bin/clang++)
set(CMAKE_C_COMPILER ${NDK_HOME}/toolchains/llvm/prebuilt/darwin-x86_64/bin/clang)

set(CMAKE_CXX_FLAGS "--target=aarch64-none-linux-android21
                    --gcc-toolchain=${NDK_HOME}/toolchains/llvm/prebuilt/darwin-x86_64
                    --sysroot=${NDK_HOME}/toolchains/llvm/prebuilt/darwin-x86_64/sysroot")

set(CMAKE_C_FLAGS "--target=aarch64-none-linux-android21
                    --gcc-toolchain=${NDK_HOME}/toolchains/llvm/prebuilt/darwin-x86_64
                    --sysroot=${NDK_HOME}/toolchains/llvm/prebuilt/darwin-x86_64/sysroot")

#set(CMAKE_EXE_LINKER_FLAGS "-Wl,--exclude-libs,libgcc.a -Wl,--exclude-libs,libgcc_real.a -Wl,--exclude-libs,libatomic.a -static-libstdc++ -Wl,--build-id -Wl,--fatal-warnings -Wl,--no-undefined -Qunused-arguments -Wl,--gc-sections")
#set(CMAKE_EXE_LINKER_FLAGS "-static-libstdc++")
#LINK_LIBRARIES = -latomic -lm
#set(CMAKE_EXE_LINK_LIBRARIES "-latomic -lm")



include_directories(${NDK_HOME}/toolchains/llvm/prebuilt/darwin-x86_64/sysroot/usr/include)
#include_directories(${NDK_HOME}/toolchains/llvm/prebuilt/darwin-x86_64/sysroot/usr/include/c++/v1)
#/Users/zhangyipeng/Library/Android/sdk/ndk/21.1.6352462/toolchains/llvm/prebuilt/darwin-x86_64/sysroot/usr/include/c++/v1/stdio.h

add_executable(main_cpp main.cpp)
add_executable(main_c main.c)

target_link_libraries(main_cpp -static-libstdc++)
