cmake_minimum_required(VERSION 3.5)

#-------------------------------------------------------------------------------
# Project Configuration
#-------------------------------------------------------------------------------

project(algorithms
    VERSION
        0.1
    DESCRIPTION
        "Surfing through algorithms project"
)

set(PROJECT_OUTPUT_DIR ${PROJECT_BINARY_DIR}/out)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_OUTPUT_DIR})

enable_testing()

#-------------------------------------------------------------------------------
# Resources Configuration
#-------------------------------------------------------------------------------

file(COPY
        ${PROJECT_SOURCE_DIR}/resources
     DESTINATION
        ${PROJECT_OUTPUT_DIR}
     USE_SOURCE_PERMISSIONS)

#-------------------------------------------------------------------------------
# External Dependencies Configuration
#-------------------------------------------------------------------------------

include(${PROJECT_SOURCE_DIR}/external/googletest.cmake)

#-------------------------------------------------------------------------------
# Structure Configuration
#-------------------------------------------------------------------------------

add_subdirectory(${PROJECT_SOURCE_DIR}/src/union-find)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/stack)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/queue)
