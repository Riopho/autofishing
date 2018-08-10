cmake_minimum_required(VERSION 3.6)
project (AutoFishing)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin")
set(CMAKE_CXX_FLAGS "-O0 -gdwarf-2  -std=gnu++11 -Wall")
AUX_SOURCE_DIRECTORY(. DIR_SRCS)
ADD_EXECUTABLE(AutoFishing ${DIR_SRCS})
TARGET_LINK_LIBRARIES(AutoFishing boost_log boost_log_setup boost_thread boost_system gdi32 opencv_core opencv_imgproc opencv_imgcodecs opencv_highgui)
