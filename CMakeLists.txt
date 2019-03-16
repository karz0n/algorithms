cmake_minimum_required(VERSION 3.5)

#-------------------------------------------------------------------------------
# Project Configuration
#-------------------------------------------------------------------------------

project(algorithms)

include(CTest)

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
add_subdirectory(${PROJECT_SOURCE_DIR}/src/selection)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/list)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/sort)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/tools)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/event-driven)
