#所有源文件放入 rtmp_source 变量
file(GLOB source *.cpp)
#编译静态库
add_library(mylib STATIC ${source} )