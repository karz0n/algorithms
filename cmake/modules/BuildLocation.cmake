set(PROJECT_OUTPUT_DIR "${CMAKE_BINARY_DIR}/bin")
message(STATUS "Project output dir: ${PROJECT_OUTPUT_DIR}")

if(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_OUTPUT_DIR}")
endif()
if(NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_OUTPUT_DIR}")
endif()
if(NOT CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_OUTPUT_DIR}")
endif()