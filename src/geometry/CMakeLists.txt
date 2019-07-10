include(GoogleTest)

#------------------------------------------------------------------------------------------

set(BASE_PATH ${PROJECT_SOURCE_DIR}/src/geometry)

#------------------------------------------------------------------------------------------

set(TARGET_NAME "Geometry-Library")

add_library(${TARGET_NAME} INTERFACE)

target_sources(${TARGET_NAME}
    INTERFACE
        ${BASE_PATH}/include/Point.hpp
        ${BASE_PATH}/include/Segment.hpp
        ${BASE_PATH}/include/SweepLine.hpp
        ${BASE_PATH}/src/SweepLine.cpp
)

target_include_directories(${TARGET_NAME}
    INTERFACE
        ${BASE_PATH}/include
)

target_link_libraries(${TARGET_NAME}
    INTERFACE
        "Queue-Library"
)

#------------------------------------------------------------------------------------------

set(TARGET_NAME "Geometry-Test")

add_executable(${TARGET_NAME} "")

set_target_properties(${TARGET_NAME}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
)

target_link_libraries(${TARGET_NAME}
    ${GTEST_LIBRARY}
    "Geometry-Library"
)

target_sources(${TARGET_NAME}
    PRIVATE
        ${BASE_PATH}/test/PointTest.cpp
        ${BASE_PATH}/test/SegmentTest.cpp
        ${BASE_PATH}/test/SweepLineTest.cpp
)

gtest_discover_tests(${TARGET_NAME}
    WORKING_DIRECTORY
        ${PROJECT_OUTPUT_DIR}
)