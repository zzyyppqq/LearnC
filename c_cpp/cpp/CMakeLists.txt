cmake_minimum_required(VERSION 3.17)
cmake_policy(VERSION 3.17)
project(cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

add_executable(main_demo main.cpp)
add_executable(namespace_demo namespace/namespace_demo.cpp)
add_executable(object obj/object.cpp)
add_executable(object_demo obj/object_demo.cpp)
add_executable(object_point obj/objcet_point.cpp)
add_executable(object_extends obj/object_extends.cpp)
add_executable(strings strings/string_demo.cpp)
add_executable(struct_demo struct/struct_demo.cpp)
add_executable(date_demo date/date_demo.cpp)
add_executable(file_demo file/file_demo.cpp)
add_executable(exception_demo exception/exception_demo.cpp)
add_executable(memory_malloc_demo memory/memory_malloc_demo.cpp)
add_executable(template_demo template/template_demo.cpp)
#signal
add_executable(signal_demo signal/signal_demo.cpp)
add_executable(signal_catch signal/signal_catch.c)
add_executable(thread_demo thread/thread_demo.cpp)
#thread
add_executable(thread_std_demo thread/thread_std_demo.cpp)
add_executable(cgi_demo cgi/cgi_demo.cpp)
add_executable(stl_demo stl/stl_demo.cpp)
add_executable(static_cast_demo symbol/static_cast_demo.cpp)
add_executable(dirent_demo dirent/dirent_demo.cpp)
add_executable(macro_demo macro/macro_demo.cpp)
add_executable(macro_pragma macro/macro_pragma.cpp)
add_executable(define_demo define/define_demo.cpp)
add_executable(smart_ponit_demo smartpoint/smart_ponit_demo.cpp)
add_executable(typeof_demo typeof/typeof_demo.cpp)
add_executable(socket_simple_client socket/socket_simple_client.cpp)
add_executable(socket_simple_server socket/socket_simple_server.cpp)
add_executable(socket_select_client socket/socket_select_client.cpp)
add_executable(socket_select_server socket/socket_select_server.cpp)
add_executable(socket_kqueue_server socket/socket_kqueue_server.cpp)
# point
add_executable(point_demo point/point_demo.cpp)
add_executable(point_point_demo point/point_point_demo.cpp)
add_executable(point_func point/point_func.cpp)
add_executable(point_point point/point_point.cpp)
add_executable(point_point_2 point/point_point_2.cpp)
add_executable(point_point_array_get point/point_point_array_read_write.cpp)
add_executable(point_point_array_set point/point_point_array_read.cpp)

add_executable(cpp_test cpp_test.cpp)
add_executable(constructor constructor/constructor.cpp)
add_executable(version version/my_version.cpp)
add_executable(mutex mutex/my_mutex.cpp)
# single
add_executable(single single_instance/single.cpp)
add_executable(single_mutex single_instance/single_mutex.cpp)
add_executable(single_mutex_smart_point single_instance/single_mutex_smart_point.cpp)
add_executable(single_pro single_instance/single_pro.cpp)
add_executable(single_pro_call_onece single_instance/single_pro_call_onece.cpp)
# array
add_executable(array_demo array/array_demo.cpp)
add_executable(array_size array/array_size.cpp)
#event  linux - eventfd 的 OS X 替代品 pipe 和kqueue 的EVFILT_USER
add_executable(event_kqueue event/event_kqueue.cpp)
add_executable(event_pipe event/event_pipe.cpp)
add_executable(event_socket_client event/event_socket_client.cpp)
add_executable(event_socket_server event/event_socket_server.cpp)
# syscall
add_executable(syscall_demo syscall/syscall_demo.cpp)

add_executable(errno_demo errno/errno_demo.cpp)

add_executable(vector_demo c++11/vector_demo.cpp)

add_executable(handler_demo handler/handler.cpp)
add_executable(handler_pro_demo handler/handler_pro.cpp)




# --------------------------- rtp ---------------------------------
add_executable(simplest_mediadata_udp rtp/simplest_mediadata_udp.cpp)


# 依赖静态库
#add_library(
#        mylib
#        STATIC
#        IMPORTED
#)
#
#SET_TARGET_PROPERTIES(
#        mylib
#        PROPERTIES IMPORTED_LOCATION
#        ${CMAKE_SOURCE_DIR}/libmylib.a
#)
#include_directories(mylib)
#add_executable(mylibTest mylibTest.cpp)
#target_link_libraries(mylibTest mylib)

# 依赖源码
#引入指定目录下的CMakeLists.txt
add_subdirectory(mylib)
add_subdirectory(attribute)
#指定头文件查找路径
include_directories(mylib)

add_executable(test test.cpp)
target_link_libraries(test mylib)
