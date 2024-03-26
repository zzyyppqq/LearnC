cmake_minimum_required(VERSION 3.17)
cmake_policy(VERSION 3.17)
project(CppStudy)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# --------------------------- add_subdirectory ---------------------------------

add_subdirectory(c)
add_subdirectory(cpp)
add_subdirectory(assembly)

#add_subdirectory(gtk)
add_subdirectory(boost)

