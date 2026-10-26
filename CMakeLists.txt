cmake_minimum_required(VERSION 3.30)
project(ryujinIII)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MAJOR_VERSION 1)
set(CMAKE_MINOR_VERSION 4)
set(CMAKE_PATCH_VERSION 0)
set(CMAKE_TWEAK_VERSION 0)
set(CMAKE_PROJECT_VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}.${CMAKE_PATCH_VERSION}.${CMAKE_TWEAK_VERSION})

configure_file(README.md ${CMAKE_CURRENT_BINARY_DIR}/README.md COPYONLY)
configure_file(inc/ryujinIII_library/commands/version_command.h.in ${CMAKE_CURRENT_SOURCE_DIR}/inc/ryujinIII_library/commands/version_command.h)

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
        src/ryujinIII_library/ryujin/ryujin_device.cpp
        src/ryujinIII_library/wrappers/libusb_wrapper.cpp
        src/ryujinIII_library/commands/base_command.cpp
        src/ryujinIII_library/commands/select_gif_command.cpp
        src/ryujinIII_library/commands/turn_on_command.cpp
        src/ryujinIII_library/commands/turn_off_command.cpp
        src/ryujinIII_library/commands/delete_command.cpp
        src/ryujinIII_library/commands/select_memory_space_command.cpp
        src/ryujinIII_library/commands/delete_chain.cpp
        src/ryujinIII_library/commands/transaction_command.cpp
        src/ryujinIII_library/commands/start_transaction_command.cpp
        src/ryujinIII_library/commands/start_upload_command.cpp
        src/ryujinIII_library/commands/reported_size_command.cpp
        src/ryujinIII_library/utils/file_handle.cpp
        src/ryujinIII_library/commands/upload_gif_command.cpp
        src/ryujinIII_library/commands/end_upload_command.cpp
        src/ryujinIII_library/commands/upload_chain.cpp
        src/ryujinIII_library/commands/default_gif_command.cpp
        src/ryujinIII_library/tools/magick_tool.cpp
        src/ryujinIII_library/commands/command_chain.cpp
        src/ryujinIII_library/commands/start_hardware_monitor_command.cpp
        src/ryujinIII_library/wrappers/libusb_wrapper_base.cpp
        src/ryujinIII_library/utils/file_handle_base.cpp
        src/ryujinIII_library/led_line/amd_core_line.cpp
        src/ryujinIII_library/led_line/kernel_hardware_monitor.cpp
        src/ryujinIII_library/led_line/ryujin_liquid_temp_line.cpp
        src/ryujinIII_library/utils/byte_utils.cpp
        src/ryujinIII_library/stores/hardware_status_store.cpp
        src/ryujinIII_library/commands/hardware_monitor_chain.cpp
        src/ryujinIII_library/commands/hardware_status_command.cpp
        src/ryujinIII_library/commands/hardware_monitor_style_command.cpp
        src/ryujinIII_library/commands/hardware_monitor_line_command.cpp
        src/ryujinIII_library/led_line/ryujin_status_line.cpp
        src/ryujinIII_library/led_line/led_line_factory.cpp
        src/ryujinIII_library/led_line/git_last_commiter_line.cpp
        src/ryujinIII_library/led_line/ryujin_pump_speed_line.cpp
        src/ryujinIII_library/led_line/ryujin_fan_speed_line.cpp
        src/ryujinIII_library/commands/hardware_monitor_chain_config.cpp
        src/ryujinIII_library/commands/speed_config_command.cpp
        src/ryujinIII_library/commands/select_memory_space_jpeg_command.cpp
        src/ryujinIII_library/commands/upload_chain_jpeg.cpp
        src/ryujinIII_library/commands/select_jpeg_command.cpp
        src/ryujinIII_library/tools/magick_tool_jpeg.cpp
        src/ryujinIII_library/commands/start_instruction_command.cpp
        src/ryujinIII_library/commands/show_jpeg_command.cpp
        src/ryujinIII_library/commands/end_instruction_command.cpp
        src/ryujinIII_library/commands/select_jpeg_chain.cpp
        src/ryujinIII_library/commands/clock_mode_command.cpp
        src/ryujinIII_library/commands/start_clock_command.cpp
        src/ryujinIII_library/commands/clock_chain.cpp
        src/ryujinIII_library/commands/slide_show_command.cpp
        src/ryujinIII_library/commands/slide_show_chain.cpp
        src/ryujinIII_library/commands/slide_show_jpeg_command.cpp
        src/ryujinIII_library/commands/slide_show_jpeg_chain.cpp
        src/ryujinIII_library/stores/memory_slots_store.cpp
        src/ryujinIII_library/utils/date_utils.cpp
        src/ryujinIII_library/commands/show_slots_command.cpp
        src/ryujinIII_library/commands/version_command.cpp
        src/ryujinIII_library/commands/load_jpeg_to_memory_command.cpp
)

add_library(${PROJECT_NAME}_args_library
        src/ryujinIII_args_library/build_args_parser.cpp
        src/ryujinIII_args_library/factory.cpp
)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME}_library PUBLIC inc/ryujinIII_library)
target_include_directories(${PROJECT_NAME}_args_library PUBLIC inc/ryujinIII_args_library inc/ryujinIII_library)

target_link_libraries(${PROJECT_NAME}_args_library PUBLIC ${PROJECT_NAME}_library)
target_link_libraries(${PROJECT_NAME}_library PUBLIC ${libusb})
target_link_libraries(${PROJECT_NAME} PUBLIC ${PROJECT_NAME}_library ${PROJECT_NAME}_args_library)

IF (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    message(STATUS "Release")
    target_link_options(${PROJECT_NAME}_library PRIVATE -Os -O3 -s)
    target_compile_options(${PROJECT_NAME}_library PRIVATE -Os -O3 -s)
    target_link_options(${PROJECT_NAME}_args_library PRIVATE -Os -O3 -s)
    target_compile_options(${PROJECT_NAME}_args_library PRIVATE -Os -O3 -s)
    target_link_options(${PROJECT_NAME} PRIVATE -Os -O3 -s)
    target_compile_options(${PROJECT_NAME} PRIVATE -Os -O3 -s)
ENDIF ()

install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION bin)

add_subdirectory(tests)
include(packaging.cmake)