cmake_minimum_required(VERSION 3.25)
project(c_design_patterns C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

include_directories(.)
include_directories(./chap3/HardwareProxy)


add_executable(Sensor chap1/sensor.c)
add_executable(Queue chap1/queue.c chap1/cached_queue.c)

add_executable(TestBuilder chap2/TestBuilder.c
        chap2/ArrythmiaDetector.c
        chap2/ECG_Module.c
        chap2/HistogramDisplay.c
        chap2/QRSDelector.c
        chap2/TimeMarkedData.c
        chap2/TMDQueue.c
        chap2/WaveformDisplay.c
)

add_executable(code1 chap3/code1.c)
add_executable(code2 chap3/code2.c)

add_executable(HWProxyExample chap3/HardwareProxy/main.c chap3/HardwareProxy/MotorProxy.c)

