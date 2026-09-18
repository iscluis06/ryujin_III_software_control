cmake_minimum_required(VERSION 3.30)
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
        factory_test.cpp
        led_line/amd_core_line_test.cpp
        led_line/ryujin_liquid_temp_line_test.cpp
        byte_utils_test.cpp
        ryujin_device_test.cpp
        commands/hardware_monitor_chain_test.cpp
        commands/hardware_monitor_chain_config_test.cpp
        commands/hardware_monitor_line_command_test.cpp
        commands/hardware_monitor_style_command_test.cpp
        commands/hardware_status_command_test.cpp
        commands/start_hardware_monitor_command_test.cpp
        led_line/ryujin_status_line_test.cpp
        led_line/ryujin_pump_speed_line_test.cpp
        led_line/git_last_commiter_line_test.cpp
        mocks/led_line/kernel_hardware_monitor_mock.h
        led_line/kernel_hardware_monitor_test.cpp
        led_line/ryujin_fan_speed_line_test.cpp
        led_line/led_line_factory_test.cpp
)

target_link_libraries(${PROJECT_NAME}_gtest ${libgtest} ${libgtest_main} ${libgmock} ${libusb} ${PROJECT_NAME}_library)

target_include_directories(${PROJECT_NAME}_gtest PUBLIC ../inc mocks)