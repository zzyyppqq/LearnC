#所有源文件放入 rtmp_source 变量
file(GLOB source *.c)
#编译静态库
#add_library(mylib STATIC ${source} )
add_library(hello SHARED ${source} )

message("PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")
message("CMAKE_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}")

# 设置动态库的版本 为1.2
#SET_TARGET_PROPERTIES(hello PROPERTIES VERSION 1.2 SOVERSION 1)

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/dlsym)

install(CODE "MESSAGE(\"Sample install message.\")")
install(TARGETS hello DESTINATION ${PROJECT_SOURCE_DIR}/dlsym/lib)
install(FILES hello.h DESTINATION ${PROJECT_SOURCE_DIR}/dlsym/include)