cmake_minimum_required(VERSION 4.2)
project(ryujinIII)

set(CMAKE_CXX_STANDARD 17)

find_program(CPPCHECK_PATH NAMES cppcheck)
if (CPPCHECK_PATH)
    set(CMAKE_CXX_CPPCHECK
            "${CPPCHECK_PATH}"
            "--enable=warning,performance,portability"
            "--check-level=exhaustive"
            "--suppress=missingIncludeSystem"
            "--suppress=checkersReport")
endif ()

find_library(libusb libusb NAMES libusb-1.0 usb-1.0 usb REQUIRED)

add_library(${PROJECT_NAME}_library
        src/ryujin_device.cpp
        src/libusb_wrapper.cpp
        src/commands/base_command.cpp
        src/commands/select_gif_command.cpp
        src/commands/turn_on_command.cpp
        src/commands/turn_off_command.cpp
        src/commands/delete_command.cpp
        src/commands/select_memory_space_command.cpp
        src/commands/delete_chain.cpp
        src/commands/transaction_command.cpp
        src/commands/start_transaction_command.cpp
        src/commands/start_upload_command.cpp
        src/commands/reported_size_command.cpp
        src/file_handle.cpp
        src/commands/upload_gif_command.cpp
        src/commands/end_upload_command.cpp
        src/commands/upload_chain.cpp
        src/commands/default_gif.cpp
        src/magick_tool.cpp
        src/commands/command_chain.cpp
        src/factory.cpp
        src/libusb_wrapper_base.cpp
        src/file_handle_base.cpp
)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME}_library PUBLIC inc)

target_link_libraries(${PROJECT_NAME}_library PUBLIC ${libusb})
target_link_libraries(${PROJECT_NAME} PUBLIC ${PROJECT_NAME}_library)

add_subdirectory(tests)