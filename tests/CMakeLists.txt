cmake_minimum_required(VERSION 4.2)
project(ryujinIII)

set(CMAKE_CXX_STANDARD 17)
find_library(libgtest_main libgtest_main NAMES gtest_main)
find_library(libgtest libgtest NAMES gtest)
find_library(libgmock libgmock NAMES gmock)

enable_testing()

add_executable(${PROJECT_NAME}_gtest
        commands/base_command_test.cpp
        commands/command_chain_test.cpp
        commands/default_gif_test.cpp
        commands/delete_chain_test.cpp
        commands/delete_command_test.cpp
        commands/end_upload_command_test.cpp
        commands/reported_size_command_test.cpp
        commands/select_gif_command_test.cpp
        commands/select_memory_space_command_test.cpp
        commands/start_transaction_command_test.cpp
        commands/start_upload_command_test.cpp
        commands/transaction_command_test.cpp
        commands/turn_off_command_test.cpp
        commands/turn_on_command_test.cpp
        commands/upload_chain_test.cpp
        commands/upload_gif_command_test.cpp
)

target_link_libraries(${PROJECT_NAME}_gtest ${libgtest} ${libgtest_main} ${libgmock} ${libusb} ${PROJECT_NAME}_library)

target_include_directories(${PROJECT_NAME}_gtest PUBLIC ../inc mocks)