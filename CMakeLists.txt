cmake_minimum_required(VERSION 4.2)
project(ryujinIII)

set(CMAKE_CXX_STANDARD 17)
find_library(libusb libusb NAMES libusb-1.0 usb-1.0 usb REQUIRED)
find_library(libgtest_main libgtest_main NAMES gtest_main)
find_library(libgtest libgtest NAMES gtest)
find_library(libgmock libgmock NAMES gmock)

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

enable_testing()

add_executable(${PROJECT_NAME}_gtest
        src/commands/tests/base_command_test.cpp
        src/commands/tests/command_chain_test.cpp
        src/commands/tests/default_gif_test.cpp
        src/commands/tests/delete_chain_test.cpp
        src/commands/tests/delete_command_test.cpp
        src/commands/tests/end_upload_command_test.cpp
        src/commands/tests/reported_size_command_test.cpp
        src/commands/tests/select_gif_command_test.cpp
        src/commands/tests/select_memory_space_command_test.cpp
        src/commands/tests/start_transaction_command_test.cpp
        src/commands/tests/start_upload_command_test.cpp
        src/commands/tests/transaction_command_test.cpp
        src/commands/tests/turn_off_command_test.cpp
        src/commands/tests/turn_on_command_test.cpp
        src/commands/tests/upload_chain_test.cpp
        src/commands/tests/upload_gif_command_test.cpp
)

target_link_libraries(${PROJECT_NAME}_gtest ${libgtest} ${libgtest_main} ${libgmock} ${libusb} ${PROJECT_NAME}_library)

target_include_directories(${PROJECT_NAME}_gtest PUBLIC inc src/commands/tests/mocks)