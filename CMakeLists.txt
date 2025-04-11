cmake_minimum_required(VERSION 3.27)
project(torchcs_logger VERSION 1.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(TORCHCS_LOGGER_INSTALL "Enable installation of torchcs_logger" ON)
option(TORCHCS_LOGGER_SHARED "Build torchcs_logger as a shared library (.so/.dll)" OFF)
option(TORCHCS_LOGGER_STATIC "Build torchcs_logger as a static library (.a/.lib)" ON)
option(BUILD_EXAMPLE "Build example project in tests/your_project" OFF)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(spdlog)
include(fmt)

if(TORCHCS_LOGGER_SHARED AND TORCHCS_LOGGER_STATIC)
    message(FATAL_ERROR "Both TORCHCS_LOGGER_SHARED and TORCHCS_LOGGER_STATIC are enabled. Choose only one.")
endif()

if(TORCHCS_LOGGER_SHARED)
    set(LIBRARY_TYPE SHARED)
    message(STATUS "Building torchcs_logger as a shared library")
elseif(TORCHCS_LOGGER_STATIC)
    set(LIBRARY_TYPE STATIC)
    message(STATUS "Building torchcs_logger as a static library")
else()
    message(FATAL_ERROR "Either TORCHCS_LOGGER_SHARED or TORCHCS_LOGGER_STATIC must be enabled.")
endif()

add_library(torchcs_logger ${LIBRARY_TYPE}
    src/logger_manager.cpp
    src/logger_options.cpp
    src/custom_formatter.cpp
    src/log_color.cpp
)

target_include_directories(torchcs_logger PUBLIC include)
target_link_libraries(torchcs_logger PRIVATE fmt::fmt spdlog::spdlog)

if(TARGET torchcs_logger)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        target_compile_options(torchcs_logger PRIVATE -Wall -Wextra -Wpedantic -Werror)
    elseif(MSVC)
        target_compile_options(torchcs_logger PRIVATE /W4 /WX)
    endif()
endif()

if(BUILD_EXAMPLE)
    add_subdirectory(tests/your_project)
endif()

if(TORCHCS_LOGGER_INSTALL)
    message(STATUS "Installing torchcs_logger")

    install(TARGETS torchcs_logger
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        PUBLIC_HEADER DESTINATION include
    )

    install(DIRECTORY include/ DESTINATION include)
endif()