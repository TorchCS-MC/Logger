cmake_minimum_required(VERSION 3.27)

project(sample)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(sample
    src/main.cpp
)

target_link_libraries(sample PRIVATE torchcs_logger)
