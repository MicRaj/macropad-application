cmake_minimum_required(VERSION 3.13)
project(macropad-application)

# Platform-specific HIDAPI settings
# if (WIN32)
#     set(BUILD_SHARED_LIBS OFF CACHE BOOL "Static link" FORCE)
#     set(HIDAPI_USE_DDK OFF CACHE BOOL "Use HIDAPI DDK backend" FORCE)
#     set(HIDAPI_WITH_HIDRAW OFF CACHE BOOL "" FORCE)
#     set(HIDAPI_WITH_LIBUSB OFF CACHE BOOL "" FORCE)
#     set(HIDAPI_WITH_HID OFF CACHE BOOL "" FORCE)
# endif()

# Add HIDAPI from subdirectory
add_subdirectory(lib/hidapi)

include_directories(
    ${CMAKE_CURRENT_LIST_DIR}/lib/hidapi
)

add_executable(macropad-application
    macro_programming/macro_programming.c
    parse_dsl/parse_dsl.c
    parse_dsl/read_dsl_file.c
    main.c
)

# Windows-specific linking
if (WIN32)
    target_link_libraries(macropad-application PRIVATE setupapi)
endif()

# Link against HIDAPI target
target_link_libraries(macropad-application PRIVATE hidapi::hidapi)
