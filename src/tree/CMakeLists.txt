set(TARGET "Tree-Library")

add_library(${TARGET} INTERFACE)
add_library("Tree::Library" ALIAS ${TARGET})

target_sources(
        ${TARGET}
        INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/traverse/BreadthOrderTraverse.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/traverse/DepthInOrderTraverse.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/traverse/DepthPostOrderTraverse.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/traverse/DepthPreOrderTraverse.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/BinaryTree.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/RedBlackTree.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Traverse.hpp)

target_include_directories(${TARGET}
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(ALG_ENABLE_TESTS)
    add_subdirectory(test)
endif()
