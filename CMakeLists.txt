cmake_minimum_required(VERSION 4.2)
project(ryujinIII)

set(CMAKE_CXX_STANDARD 17)
FIND_LIBRARY(libusb libusb NAMES libusb-1.0 usb-1.0 usb REQUIRED)
add_executable(ryujinIII main.cpp ryujin_device.cpp libusb_wrapp.cpp)
message(STATUS "Library: ${libusb}")

target_link_libraries(ryujinIII PUBLIC ${libusb})
