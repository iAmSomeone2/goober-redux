cmake_minimum_required(VERSION 3.14)
project(goober VERSION 0.1 LANGUAGES CXX) # Update this to include asm later

set(CMAKE_CXX_DEBUG_FLAGS "${CMAKE_CXX_DEBUG_FLAGS} -Wall -Og")
set(CMAKE_CXX_RELEASE_FLAGS "${CMAKE_CXX_RELEASE_FLAGS} -O3 -march=native")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(GTest)

if(NOT GTEST_FOUND)
    set(BUILD_TESTING OFF)
endif()

# Set up testing framework
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND GTEST_FOUND)
    include(CTest)

    # Prepare the "GTest" library
    include_directories(${GTEST_INCLUDE_DIRS})
endif()

include_directories(./include)

add_subdirectory(core)