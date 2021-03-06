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
           "${CMAKE_CURRENT_SOURCE_DIR}/include/PrimsMinSpanningTree.hpp"
           "${CMAKE_CURRENT_SOURCE_DIR}/include/DirectedEdge.hpp"
           "${CMAKE_CURRENT_SOURCE_DIR}/include/EdgeWeightedDigraph.hpp"
           "${CMAKE_CURRENT_SOURCE_DIR}/include/DijkstraShortestPaths.hpp"
           "${CMAKE_CURRENT_SOURCE_DIR}/include/DirectedCycleFinder.hpp"
           "${CMAKE_CURRENT_SOURCE_DIR}/include/TopologicalOrderIterator.hpp"
           "${CMAKE_CURRENT_SOURCE_DIR}/include/AcyclicShortestPaths.hpp"
           "${CMAKE_CURRENT_SOURCE_DIR}/include/BellmanFordShortestPaths.hpp"
           "${CMAKE_CURRENT_SOURCE_DIR}/include/FlowEdge.hpp"
           "${CMAKE_CURRENT_SOURCE_DIR}/include/FlowNetwork.hpp"
           "${CMAKE_CURRENT_SOURCE_DIR}/include/FordFulkerson.hpp"
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
            "${CMAKE_CURRENT_SOURCE_DIR}/src/PrimsMinSpanningTree.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/DirectedEdge.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/EdgeWeightedDigraph.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/DijkstraShortestPaths.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/DirectedCycleFinder.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/TopologicalOrderIterator.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/AcyclicShortestPaths.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/BellmanFordShortestPaths.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/FlowEdge.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/FlowNetwork.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/FordFulkerson.cpp")

target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${TARGET} PUBLIC Queue::Library UnionFind::Library)

if(ALG_ENABLE_TESTS)
    add_subdirectory(test)
endif()
