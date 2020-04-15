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
        ${BASE_PATH}/include/KdTree.hpp
        ${BASE_PATH}/include/KdTreeEx.hpp
        ${BASE_PATH}/src/SweepLine.cpp
        ${BASE_PATH}/src/KdTree.cpp
        ${BASE_PATH}/src/KdTreeEx.cpp
)

target_include_directories(${TARGET_NAME}
    INTERFACE
        ${BASE_PATH}/include
)

target_link_libraries(${TARGET_NAME}
    INTERFACE
        "Queue-Library"
        "Sort-Library"
        "Select-Library"
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
    "Geometry-Library"
    "Tools-Library"
    GTest::gtest
    GTest::gtest_main
)

target_sources(${TARGET_NAME}
    PRIVATE
        ${BASE_PATH}/test/PointTest.cpp
        ${BASE_PATH}/test/SegmentTest.cpp
        ${BASE_PATH}/test/SweepLineTest.cpp
        ${BASE_PATH}/test/KdTreeTest.cpp
)

gtest_discover_tests(${TARGET_NAME}
    WORKING_DIRECTORY
        ${PROJECT_OUTPUT_DIR}
)



