cmake_minimum_required(VERSION 3.17)
cmake_policy(VERSION 3.17)
project(c)


set(CMAKE_C_STANDARD 11)  # 将 C 标准设置为 C11
#add_executable(c11_thread_demo thread/c11_thread_demo.c)

set(CMAKE_C_STANDARD 99)

include_directories(interface)

add_executable(c_test c_test.c)

add_executable(extern_demo extern/extern_demo.c extern/extern_lib.c)

add_executable(func_pointer func_pointer/func_point.c)
add_executable(func_callback func_pointer/func_callback.c)
add_executable(c_define_demo define/define_demo.c)
add_executable(c_error_demo error/error_demo.c)
add_executable(c_thread_demo thread/c_thread_demo.c)
add_executable(union_demo union/union_demo.c)
add_executable(std_demo std/std_demo.c)

add_executable(c_sign_demo sign/sign_demo.c)
add_executable(c_sigsetjmp_siglongjmp_demo sign/sigsetjmp_siglongjmp_demo.c)

add_executable(callback_demo callback/callback_demo.c)
add_executable(va_list_demo va_list/va_list_demo.c)

add_executable(alarm_demo alarm/alarm_demo.c)
add_executable(alarm_pause_demo alarm/alarm_pause.c)

include_directories(lib)
add_executable(dlsym_demo dlsym/dlsym_demo.c)
target_link_libraries(dlsym_demo hello)


add_executable(dlsym_check dlsym/dlsym_check.c)



add_subdirectory(lib)
