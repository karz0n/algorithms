set(TARGET "Geometry-Library")

add_library(${TARGET})
add_library("Geometry::Library" ALIAS ${TARGET})

target_sources(
    ${TARGET}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/Point.hpp
           ${CMAKE_CURRENT_SOURCE_DIR}/include/Points.hpp
           ${CMAKE_CURRENT_SOURCE_DIR}/include/LineSegment.hpp
           ${CMAKE_CURRENT_SOURCE_DIR}/include/LineSegments.hpp
           ${CMAKE_CURRENT_SOURCE_DIR}/include/KdTree.hpp
           ${CMAKE_CURRENT_SOURCE_DIR}/include/KdTreeEx.hpp
           ${CMAKE_CURRENT_SOURCE_DIR}/include/LineCrossFinder.hpp
           ${CMAKE_CURRENT_SOURCE_DIR}/include/IntervalSearchTree.hpp
           ${CMAKE_CURRENT_SOURCE_DIR}/include/Rect.hpp
           ${CMAKE_CURRENT_SOURCE_DIR}/include/Rects.hpp
           ${CMAKE_CURRENT_SOURCE_DIR}/include/RectCrossFinder.hpp
           ${CMAKE_CURRENT_SOURCE_DIR}/include/GrahamScan.hpp
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/KdTree.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/KdTreeEx.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/LineSegment.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/LineSegments.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/Point.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/Points.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/LineCrossFinder.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/Rect.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/RectCrossFinder.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/GrahamScan.cpp)

target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${TARGET} PUBLIC Queue::Library Sort::Library
                                       Select::Library)

if(ALG_ENABLE_TESTS)
    add_subdirectory(test)
endif()
