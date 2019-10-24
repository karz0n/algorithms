#------------------------------------------------------------------------------------------

set(BASE_PATH ${PROJECT_SOURCE_DIR}/src/union-find)

#------------------------------------------------------------------------------

set(TARGET_NAME "UF-QuickFind-Main")

add_executable(${TARGET_NAME} "")

set_target_properties(${TARGET_NAME}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
)

target_link_libraries(${TARGET_NAME}
    "googletest-gtest"
)

target_sources(${TARGET_NAME}
    PRIVATE
        "Common.hpp"
        "Common.cpp"
        "QuickFind.hpp"
        "QuickFind.cpp"
        "QuickFindMain.cpp"
)

add_test(
    NAME
        ${TARGET_NAME}
    COMMAND
        ${TARGET_NAME}
    WORKING_DIRECTORY
        ${PROJECT_OUTPUT_DIR}
)

#------------------------------------------------------------------------------

set(TARGET_NAME "UF-QuickUnion-Main")

add_executable(${TARGET_NAME} "")

set_target_properties(${TARGET_NAME}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
)

target_link_libraries(${TARGET_NAME}
    "googletest-gtest"
)

target_sources(${TARGET_NAME}
    PRIVATE
        "Common.hpp"
        "Common.cpp"
        "QuickUnion.hpp"
        "QuickUnion.cpp"
        "QuickUnionMain.cpp"
)

add_test(
    NAME
        ${TARGET_NAME}
    COMMAND
        ${TARGET_NAME}
    WORKING_DIRECTORY
        ${PROJECT_OUTPUT_DIR}
)

#------------------------------------------------------------------------------

set(TARGET_NAME "UF-UnionFind-Main")

add_executable(${TARGET_NAME} "")

set_target_properties(${TARGET_NAME}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
)

target_link_libraries(${TARGET_NAME}
    "googletest-gtest"
)

target_sources(${TARGET_NAME}
    PRIVATE
        "Common.hpp"
        "Common.cpp"
        "UnionFind.hpp"
        "UnionFind.cpp"
        "UnionFindMain.cpp"
)

add_test(
    NAME
        ${TARGET_NAME}
    COMMAND
        ${TARGET_NAME}
    WORKING_DIRECTORY
        ${PROJECT_OUTPUT_DIR}
)

#------------------------------------------------------------------------------

set(TARGET_NAME "Percolation-Main")

add_executable(${TARGET_NAME} "")

set_target_properties(${TARGET_NAME}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
)

target_link_libraries(${TARGET_NAME}
    "googletest-gtest"
)

target_sources(${TARGET_NAME}
    PRIVATE
        "Common.hpp"
        "Common.cpp"
        "UnionFind.hpp"
        "UnionFind.cpp"
        "Percolation.hpp"
        "Percolation.cpp"
        "PercolationMain.cpp"
)

add_test(
    NAME
        ${TARGET_NAME}
    COMMAND
        ${TARGET_NAME}
    WORKING_DIRECTORY
        ${PROJECT_OUTPUT_DIR}
)
