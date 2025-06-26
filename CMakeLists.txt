cmake_minimum_required(VERSION 3.15)
project(torchcs_logger)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(TORCHCS_LOGGER_INSTALL "Enable installation of torchcs_logger" ON)
option(TORCHCS_LOGGER_SHARED "Build torchcs_logger as a shared library (.so/.dll)" OFF)
option(TORCHCS_LOGGER_STATIC "Build torchcs_logger as a static library (.a/.lib)" ON)
option(BUILD_EXAMPLE "Build example project in sample" ON)

include(FetchContent)
include(cmake/fmt.cmake)
include(cmake/spdlog.cmake)

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
    src/formatter/level_formatter.cpp
    src/formatter/color_code_formatter.cpp
    src/formatter/anti_color_code_formatter.cpp

    src/sinks/console_sink.cpp
    src/sinks/file_sink.cpp

    src/log_color.cpp
    src/spdlog_provider.cpp
)

target_include_directories(torchcs_logger PRIVATE src)

target_link_libraries(torchcs_logger PUBLIC 
    spdlog::spdlog 
    fmt::fmt
)

target_include_directories(torchcs_logger PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

if(TARGET torchcs_logger)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        target_compile_options(torchcs_logger PRIVATE -Wall -Wextra -Wpedantic -Werror)
    elseif(MSVC)
        target_compile_options(torchcs_logger PRIVATE /W4 /WX)
    endif()
endif()

add_library(torchcs::logger ALIAS torchcs_logger)

if(BUILD_EXAMPLE)
    add_subdirectory(sample)
endif()

if(TORCHCS_LOGGER_INSTALL)
    message(STATUS "Installing torchcs_logger")

    install(TARGETS torchcs_logger
        EXPORT torchcs_loggerTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
    )

    install(DIRECTORY include/ DESTINATION include)

    install(EXPORT torchcs_loggerTargets
        FILE torchcs_loggerTargets.cmake
        NAMESPACE torchcs::
        DESTINATION lib/cmake/torchcs_logger
    )
endif()
