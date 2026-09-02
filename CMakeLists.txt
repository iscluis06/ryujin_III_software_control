cmake_minimum_required(VERSION 4.2)
project(ryujinIII)

set(CMAKE_CXX_STANDARD 17)
find_library(libusb libusb NAMES libusb-1.0 usb-1.0 usb REQUIRED)
add_executable(${PROJECT_NAME}
        main.cpp
        src/ryujin_device.cpp
        src/libusb_wrapp.cpp
        src/commands/base_command.cpp
        src/commands/select_gif_command.cpp
        src/commands/turn_on_command.cpp
        src/commands/turn_off_command.cpp
        src/commands/delete_command.cpp
        src/commands/select_memory_space_command.cpp
        src/commands/delete_chain.cpp
        src/commands/transaction_state.cpp
        src/commands/start_transaction_command.cpp
        src/commands/start_upload_command.cpp
        src/commands/reported_size_command.cpp
        src/file_handle.cpp
        src/commands/upload_gif_command.cpp
        src/commands/end_upload_command.cpp
        src/commands/upload_chain.cpp
        src/commands/default_gif.cpp
        src/magick_validation.cpp
        src/commands/command_chain.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC inc)

target_link_libraries(${PROJECT_NAME} PUBLIC ${libusb})
