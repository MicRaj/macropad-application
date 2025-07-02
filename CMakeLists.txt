cmake_minimum_required(VERSION 3.13)
project(macropad-application)

# Make sure hidapi builds static libs
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared libraries")

add_subdirectory(lib/hidapi)


include_directories(
    ${CMAKE_CURRENT_LIST_DIR}/lib/hidapi
)

add_executable(macropad-application
    macro_programming/macro_programming.c
    parse_dsl/parse_dsl.c
    parse_dsl/read_dsl_file.c
    parse_dsl/char_to_hid_map.c
    main.c
)

# Windows-specific linking
if (WIN32)
    target_link_libraries(macropad-application PRIVATE setupapi)
endif()

target_link_libraries(macropad-application PRIVATE hidapi::hidapi)
