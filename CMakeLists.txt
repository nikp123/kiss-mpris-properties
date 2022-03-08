cmake_minimum_required(VERSION 3.0.2)
project(KISS_MPRIS_PROPERTIES C)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(src)
if(BUILD_MPRIS_DEMO)
    add_subdirectory(demo)
endif()

