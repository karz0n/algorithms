set(TARGET "UnionFind-Library")

add_library(${TARGET})
add_library("UnionFind::Library" ALIAS ${TARGET})

target_sources(${TARGET}
PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include/Percolation.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/QuickFind.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/QuickUnion.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/UnionFind.hpp"
        PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src/Percolation.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QuickFind.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/QuickUnion.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/UnionFind.cpp"
)

target_include_directories(${TARGET}
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(ALG_ENABLE_TESTS)
    add_subdirectory(test)
endif()