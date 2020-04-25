include(GoogleTest)

#------------------------------------------------------------------------------------------

set(BASE_PATH ${PROJECT_SOURCE_DIR}/src/geometry)

#------------------------------------------------------------------------------------------

set(TARGET_NAME "Geometry-Library")

add_library(${TARGET_NAME})

set_target_properties(${TARGET_NAME}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
)

target_sources(${TARGET_NAME}
    PUBLIC
        ${BASE_PATH}/include/Point.hpp
        ${BASE_PATH}/include/Points.hpp
        ${BASE_PATH}/include/LineSegment.hpp
        ${BASE_PATH}/include/LineSegments.hpp
        ${BASE_PATH}/include/KdTree.hpp
        ${BASE_PATH}/include/KdTreeEx.hpp
        ${BASE_PATH}/include/LineCrossFinder.hpp
        ${BASE_PATH}/include/IntervalSearchTree.hpp
        ${BASE_PATH}/include/Rect.hpp
        ${BASE_PATH}/include/Rects.hpp
        ${BASE_PATH}/include/RectCrossFinder.hpp
    PRIVATE
        ${BASE_PATH}/src/KdTree.cpp
        ${BASE_PATH}/src/KdTreeEx.cpp
        ${BASE_PATH}/src/LineSegment.cpp
        ${BASE_PATH}/src/LineSegments.cpp
        ${BASE_PATH}/src/Point.cpp
        ${BASE_PATH}/src/Points.cpp
        ${BASE_PATH}/src/LineCrossFinder.cpp
        ${BASE_PATH}/src/Rect.cpp
        ${BASE_PATH}/src/RectCrossFinder.cpp
)

target_include_directories(${TARGET_NAME}
    PUBLIC
        ${BASE_PATH}/include
)

target_link_libraries(${TARGET_NAME}
    PUBLIC
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
    GTest::gmock
    GTest::gmock_main
)

target_sources(${TARGET_NAME}
    PRIVATE
        ${BASE_PATH}/test/PointTest.cpp
        ${BASE_PATH}/test/PointsTest.cpp
        ${BASE_PATH}/test/LineSegmentTest.cpp
        ${BASE_PATH}/test/LineSegmentsTest
        ${BASE_PATH}/test/KdTreeTest.cpp
        ${BASE_PATH}/test/LineCrossFinderTest.cpp
        ${BASE_PATH}/test/IntervalSearchTreeTest.cpp
        ${BASE_PATH}/test/RectCrossFinderTest.cpp
)

gtest_discover_tests(${TARGET_NAME}
    WORKING_DIRECTORY
        ${PROJECT_OUTPUT_DIR}
)



