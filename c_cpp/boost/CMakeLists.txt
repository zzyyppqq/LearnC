cmake_minimum_required(VERSION 3.17)
cmake_policy(VERSION 3.17)
project(boost_sample)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)


# boost start
set(BOOST_ROOT /usr/local/Cellar/boost/1.84.0_1) # 设置boost库搜索路径
#set(BOOST_ROOT /opt/local/libexec/boost/1.76) # 设置boost库搜索路径
set(Boost_NO_SYSTEM_PATHS ON) #只搜索上语句设置的搜索路径
find_package(Boost COMPONENTS regex system iostreams filesystem REQUIRED)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})

    MESSAGE( STATUS "Boost_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}.")
    MESSAGE( STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}.")
    MESSAGE( STATUS "Boost_LIB_VERSION = ${Boost_LIB_VERSION}.")

    add_executable(fstream_demo fstream_demo.cpp)

    add_executable(mapped_file_demo mapped_file_demo.cpp)
    target_link_libraries (mapped_file_demo ${Boost_LIBRARIES})
endif()

#include_directories(${BOOST_ROOT}/include)
include_directories(Boost_INCLUDE_DIRS)
# boost end