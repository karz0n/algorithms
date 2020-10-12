set(TARGET "Geometry-Test")

add_executable(${TARGET} "")

target_link_libraries(${TARGET} PRIVATE Geometry::Library Tools::Library)

target_sources(
        ${TARGET}
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/PointTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/PointsTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/LineSegmentTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/LineSegmentsTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/KdTreeTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/LineCrossFinderTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/IntervalSearchTreeTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/RectCrossFinderTest.cpp)

target_add_tests(TARGET ${TARGET})
