cmake_minimum_required(VERSION 3.17)
cmake_policy(VERSION 3.17)
project(gtk)


set(CMAKE_C_STANDARD 99)

#find_package(PkgConfig REQUIRED)
#pkg_check_modules(GTK4 REQUIRED gtk4)
#include_directories(${GTK4_INCLUDE_DIRS})
#link_directories(${GTK4_LIBRARY_DIRS})
#message("GTK4_INCLUDE_DIRS: ${GTK4_INCLUDE_DIRS}")
#message("GTK4_LIBRARY_DIRS: ${GTK4_LIBRARY_DIRS}")
#message("GTK4_LIBRARIES: ${GTK4_LIBRARIES}")


find_package(PkgConfig REQUIRED)
#pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
message("GTK3_INCLUDE_DIRS: ${GTK3_INCLUDE_DIRS}")
message("GTK3_LIBRARY_DIRS: ${GTK3_LIBRARY_DIRS}")
message("GTK3_LIBRARIES: ${GTK3_LIBRARIES}")


# 查找 libcurl 库
find_package(CURL REQUIRED)
# 包含 libcurl 头文件路径
include_directories(${CURL_INCLUDE_DIRS})
link_directories(${CURL_LIBRARY_DIRS})
message("CURL_INCLUDE_DIRS: ${CURL_INCLUDE_DIRS}")
message("CURL_LIBRARY_DIRS: ${CURL_LIBRARY_DIRS}")
message("CURL_LIBRARIES: ${CURL_LIBRARIES}")

add_executable(gtk_demo gtk_demo.c)
add_executable(gtk_ui gtk_ui.c)

target_link_libraries(gtk_demo ${GTK3_LIBRARIES} ${CURL_LIBRARIES})
target_link_libraries(gtk_ui ${GTK3_LIBRARIES})