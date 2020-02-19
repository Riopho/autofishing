cmake_minimum_required(VERSION 3.6)
project (AutoFishing)

SET(CMAKE_COLOR_MAKEFILE OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin")
AUX_SOURCE_DIRECTORY(. DIR_SRCS)
ADD_EXECUTABLE(AutoFishing ${DIR_SRCS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_WIN32_WINNT=0x0601")

include_directories("C:/Boost/include/boost-1_72"
  "D:/cygwin64/home/ASUS/opencv_build/install/include")

TARGET_LINK_LIBRARIES(AutoFishing
  gdi32
  "C:/Boost/lib/libboost_date_time-vc142-mt-gd-x64-1_72.lib"
  "C:/Boost/lib/libboost_log-vc142-mt-gd-x64-1_72.lib"
  "C:/Boost/lib/libboost_filesystem-vc142-mt-gd-x64-1_72.lib"
  "C:/Boost/lib/libboost_thread-vc142-mt-gd-x64-1_72.lib"
  "C:/Boost/lib/libboost_atomic-vc142-mt-gd-x64-1_72.lib"
  "C:/Boost/lib/libboost_chrono-vc142-mt-gd-x64-1_72.lib"
  "C:/Boost/lib/libboost_regex-vc142-mt-gd-x64-1_72.lib"
   "D:/cygwin64/home/ASUS/opencv_build/lib/Debug/opencv_core420d.lib"
   "D:/cygwin64/home/ASUS/opencv_build/lib/Debug/opencv_imgcodecs420d.lib"
   "D:/cygwin64/home/ASUS/opencv_build/lib/Debug/opencv_imgproc420d.lib"
   "D:/cygwin64/home/ASUS/opencv_build/lib/Debug/opencv_highgui420d.lib"
   "D:/cygwin64/home/ASUS/opencv_build/lib/Debug/opencv_features2d420d.lib")
