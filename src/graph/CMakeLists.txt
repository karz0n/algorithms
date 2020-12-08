set(TARGET "Graph-Library" "")

add_library(${TARGET})
add_library("Graph::Library" ALIAS ${TARGET})

target_sources(
    ${TARGET}
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/Graph.hpp"
           "${CMAKE_CURRENT_SOURCE_DIR}/include/Digraph.hpp"
           "${CMAKE_CURRENT_SOURCE_DIR}/include/UndirectedGraph.hpp"
           "${CMAKE_CURRENT_SOURCE_DIR}/include/Routes.hpp"
           "${CMAKE_CURRENT_SOURCE_DIR}/include/DepthFirstRoutes.hpp"
           "${CMAKE_CURRENT_SOURCE_DIR}/include/BreadthFirstRoutes.hpp"
           "${CMAKE_CURRENT_SOURCE_DIR}/include/ComponentSpreader.hpp"
           "${CMAKE_CURRENT_SOURCE_DIR}/include/StrongComponentSpreader.hpp"
           "${CMAKE_CURRENT_SOURCE_DIR}/include/MultiSourceShortestPaths.hpp"
           "${CMAKE_CURRENT_SOURCE_DIR}/include/DepthFirstOrder.hpp"
           "${CMAKE_CURRENT_SOURCE_DIR}/include/Edge.hpp"
           "${CMAKE_CURRENT_SOURCE_DIR}/include/EdgeWeightedGraph.hpp"
           "${CMAKE_CURRENT_SOURCE_DIR}/include/KruskalMinSpanningTree.hpp"
           "${CMAKE_CURRENT_SOURCE_DIR}/include/EagerPrimsMinSpanningTree.hpp"
           "${CMAKE_CURRENT_SOURCE_DIR}/include/DirectedEdge.hpp"
           "${CMAKE_CURRENT_SOURCE_DIR}/include/EdgeWeightedDigraph.hpp"
           "${CMAKE_CURRENT_SOURCE_DIR}/include/DijkstraShortestPaths.hpp"
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/Graph.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/Digraph.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/UndirectedGraph.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/Routes.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/DepthFirstRoutes.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/BreadthFirstRoutes.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/ComponentSpreader.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/StrongComponentSpreader.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/MultiSourceShortestPaths.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/DepthFirstOrder.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/Edge.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/EdgeWeightedGraph.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/KruskalMinSpanningTree.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/EagerPrimsMinSpanningTree.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/DirectedEdge.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/EdgeWeightedDigraph.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/DijkstraShortestPaths.cpp")

target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${TARGET} PUBLIC Queue::Library UnionFind::Library)

if(ALG_ENABLE_TESTS)
    add_subdirectory(test)
endif()
