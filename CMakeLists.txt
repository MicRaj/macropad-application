cmake_minimum_required(VERSION 3.13)


project(macropad-application)
# Initialize the Pico SDK


add_subdirectory(hidapi)

# Project wide include
include_directories(
        ${CMAKE_CURRENT_LIST_DIR}/hidapi
        )


add_executable(macropad-application
        send_hid_report.c
        )

target_link_libraries(macropad-application PRIVATE hidapi::hidapi)



