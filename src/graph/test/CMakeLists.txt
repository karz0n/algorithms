set(TARGET "Graph-Test")

add_executable(${TARGET} "")

target_link_libraries(${TARGET}
PRIVATE
    Graph::Library
)

target_include_directories(${TARGET}
PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_sources(${TARGET}
        PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/include/Common.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/Common.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/DirectedGraphTest.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/DirectedRoutesTest.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/UndirectedGraphTest.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/UndirectedRoutesTest.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/MultiSourceShortestPathsTest.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/DepthFirstOrderTest.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/ComponentSpreaderTest.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/StrongComponentSpreaderTest.cpp"
        )

target_add_tests(TARGET ${TARGET})
