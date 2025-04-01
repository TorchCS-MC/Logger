cmake_minimum_required(VERSION 3.27)
project(your_project)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(your_project 
    src/main.cpp
)

target_link_libraries(your_project PRIVATE torchcs_logger spdlog::spdlog fmt::fmt)

target_include_directories(your_project PRIVATE
    ${CMAKE_BINARY_DIR}/include
)