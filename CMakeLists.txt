cmake_minimum_required(VERSION 3.14)
project(goober VERSION 0.1 LANGUAGES CXX) # Update this to include asm later

set(CMAKE_CXX_DEBUG_FLAGS "${CMAKE_CXX_DEBUG_FLAGS} -Wall -Og")
set(CMAKE_CXX_RELEASE_FLAGS "${CMAKE_CXX_RELEASE_FLAGS} -O3")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Catch2)

# Set up testing framework
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND Catch2_FOUND)
    include(CTest)

    # Prepare the "Catch" library
    include_directories(${Catch2_INCLUDE_DIR})
endif()

include_directories(./include)

add_subdirectory(core)