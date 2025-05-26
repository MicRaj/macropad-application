cmake_minimum_required(VERSION 3.13)


project(macropad-application)
# Initialize the Pico SDK


add_subdirectory(lib/hidapi)

# Project wide include
include_directories(
        ${CMAKE_CURRENT_LIST_DIR}/lib/hidapi
        )


add_executable(macropad-application
        macro_programming/macro_programming.c
        parse_dsl/parse_dsl.c
        parse_dsl/read_dsl_file.c
        main.c
        )

target_link_libraries(macropad-application PRIVATE hidapi::hidapi)



