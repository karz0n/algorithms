#------------------------------------------------------------------------------------------

set(BASE_PATH ${PROJECT_SOURCE_DIR}/src/graph)

#------------------------------------------------------------------------------------------

set(TARGET_NAME "Graph-Library")

add_library(${TARGET_NAME})

target_sources(${TARGET_NAME}
    PUBLIC
        ${BASE_PATH}/include/Graph.hpp
        ${BASE_PATH}/include/DirectedGraph.hpp
        ${BASE_PATH}/include/UndirectedGraph.hpp
        ${BASE_PATH}/include/Routes.hpp
        ${BASE_PATH}/include/DepthFirstRoutes.hpp
        ${BASE_PATH}/include/BreadthFirstSearchRoutes.hpp
        ${BASE_PATH}/include/Connector.hpp
    PRIVATE
        ${BASE_PATH}/src/Graph.cpp
        ${BASE_PATH}/src/DirectedGraph.cpp
        ${BASE_PATH}/src/UndirectedGraph.cpp
        ${BASE_PATH}/src/Routes.cpp
        ${BASE_PATH}/src/DepthFirstRoutes.cpp
        ${BASE_PATH}/src/BreadthFirstSearchRoutes.cpp
        ${BASE_PATH}/src/Connector.cpp
)

target_include_directories(${TARGET_NAME}
    PUBLIC
        ${BASE_PATH}/include
)

#------------------------------------------------------------------------------------------

set(TARGET_NAME "Graph-Test")

add_executable(${TARGET_NAME} "")

set_target_properties(${TARGET_NAME}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
)

target_link_libraries(${TARGET_NAME}
    "Graph-Library"
    GTest::gtest
    GTest::gtest_main
    GTest::gmock
    GTest::gmock_main
)

target_include_directories(${TARGET_NAME}
    PRIVATE
        ${BASE_PATH}/test/include
)

target_sources(${TARGET_NAME}
    PRIVATE
        ${BASE_PATH}/test/include/Common.hpp
        ${BASE_PATH}/test/src/Common.cpp
        ${BASE_PATH}/test/src/ConnectorTest.cpp
        ${BASE_PATH}/test/src/DirectedGraphTest.cpp
        ${BASE_PATH}/test/src/DirectedRoutesTest.cpp
        ${BASE_PATH}/test/src/UndirectedGraphTest.cpp
        ${BASE_PATH}/test/src/UndirectedRoutesTest.cpp
)

add_test(
    NAME
        ${TARGET_NAME}
    COMMAND
        ${TARGET_NAME}
    WORKING_DIRECTORY
        ${PROJECT_OUTPUT_DIR}
)
