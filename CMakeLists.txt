

cmake_minimum_required(VERSION 2.6)

# Creates a cmake project

project(game_project)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${game_project_SOURCE_DIR}/cmake")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${game_project_SOURCE_DIR}/bin)

# could add support for other compilers
set(CMAKE_CXX_FLAGS "-W -I -Wall -Wextra -pedantic -std=c++0x")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIR})

# Add a subdirectory to the project.

add_subdirectory(src)


