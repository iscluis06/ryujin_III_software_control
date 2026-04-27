cmake_minimum_required(VERSION 4.2)
project(ryujinIII)

set(CMAKE_CXX_STANDARD 17)
find_library(libusb libusb NAMES libusb-1.0 usb-1.0 usb REQUIRED)
add_executable(${PROJECT_NAME}
        main.cpp
        src/ryujin_device.cpp
        src/libusb_wrapp.cpp
        src/states/base_state.cpp
        src/states/select_gif_state.cpp
        src/states/turn_on_state.cpp
        src/states/turn_off_state.cpp
        src/states/delete_state.cpp
        src/states/select_memory_space_state.cpp
        src/states/state_chain.cpp
        src/states/delete_chain.cpp
        src/states/transaction_state.cpp
        src/states/start_transaction_state.cpp
        src/states/start_upload_state.cpp
        src/states/reported_size_state.cpp
        src/file_handle.cpp
        src/states/upload_gif_state.cpp
        src/states/end_upload_state.cpp
        src/states/upload_chain.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC inc)

target_link_libraries(${PROJECT_NAME} PUBLIC ${libusb})
