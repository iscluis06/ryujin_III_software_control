cmake_minimum_required(VERSION 3.30)
project(ryujinIII)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MAJOR_VERSION 0)
set(CMAKE_MINOR_VERSION 2)
set(CMAKE_PATCH_VERSION 1)
set(CMAKE_TWEAK_VERSION 0)
set(CMAKE_PROJECT_VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}.${CMAKE_PATCH_VERSION}.${CMAKE_TWEAK_VERSION})

configure_file(README.md README.md COPYONLY)

find_program(CPPCHECK_PATH NAMES cppcheck)
if (CPPCHECK_PATH)
    set(CMAKE_CXX_CPPCHECK
            "${CPPCHECK_PATH}"
            "--enable=warning,performance,portability"
            "--check-level=exhaustive"
            "--suppress=missingIncludeSystem"
            "--suppress=checkersReport"
            "--error-exitcode=1")
endif ()

message(STATUS "PROFILE: ${CMAKE_BUILD_TYPE}")

find_library(libusb libusb NAMES libusb-1.0 usb-1.0 usb REQUIRED)

add_library(${PROJECT_NAME}_library
        src/ryujin_device.cpp
        src/wrappers/libusb_wrapper.cpp
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
        src/commands/default_gif_command.cpp
        src/magick_tool.cpp
        src/commands/command_chain.cpp
        src/commands/start_hardware_monitor_command.cpp
        src/factory.cpp
        src/wrappers/libusb_wrapper_base.cpp
        src/file_handle_base.cpp
        src/led_line/amd_core_line.cpp
        src/led_line/kernel_hardware_monitor.cpp
        src/led_line/ryujin_liquid_temp_line.cpp
        src/byte_utils.cpp
        src/stores/hardware_status_store.cpp
        src/commands/hardware_monitor_chain.cpp
        src/commands/hardware_status_command.cpp
        src/commands/hardware_monitor_style_command.cpp
        src/commands/hardware_monitor_line_command.cpp
        src/led_line/ryujin_status_line.cpp
        src/led_line/led_line_factory.cpp
        src/led_line/git_last_commiter_line.cpp
        src/led_line/ryujin_pump_speed_line.cpp
        src/led_line/ryujin_fan_speed_line.cpp
        src/commands/hardware_monitor_chain_config.cpp
        src/build_args_parser.cpp
        src/commands/speed_config_command.cpp
        src/commands/select_memory_space_jpeg_command.cpp
        src/commands/upload_chain_jpeg.cpp
        src/commands/select_jpeg_command.cpp
        src/magick_tool_jpeg.cpp
        src/commands/start_jpeg_selection_command.cpp
        src/commands/show_jpeg_command.cpp
        src/commands/end_jpeg_mode_command.cpp
        src/commands/select_jpeg_chain.cpp
)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME}_library PUBLIC inc)

target_link_libraries(${PROJECT_NAME}_library PUBLIC ${libusb})
target_link_libraries(${PROJECT_NAME} PUBLIC ${PROJECT_NAME}_library)

IF (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    message(STATUS "Release")
    target_link_options(${PROJECT_NAME}_library PRIVATE -Os -O3 -s)
    target_compile_options(${PROJECT_NAME}_library PRIVATE -Os -O3 -s)
    target_link_options(${PROJECT_NAME} PRIVATE -Os -O3 -s)
    target_compile_options(${PROJECT_NAME} PRIVATE -Os -O3 -s)
ENDIF ()

install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION bin)

add_subdirectory(tests)
include(packaging.cmake)