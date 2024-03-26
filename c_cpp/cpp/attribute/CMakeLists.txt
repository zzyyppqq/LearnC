cmake_minimum_required(VERSION 3.17)
project(attribute)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

include_directories(.)


option(FBC_EXPORT "fbc_export" ON)
message("FBC_EXPORT:" ${FBC_EXPORT})
if (FBC_EXPORT)
    message("FBC_EXPORT:" ${FBC_EXPORT})
    # 添加编译参数，添加-D预编译宏定义，可以一次添加多个
    add_definitions(-DFBC_EXPORT)
    add_library(attribute SHARED library.cpp)
elseif ()
    add_library(attribute STATIC library.cpp)
endif ()

add_executable(attribute_test library_test.cpp)
target_link_libraries(attribute_test attribute)
