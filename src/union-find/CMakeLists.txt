#------------------------------------------------------------------------------
# Targets Configuration
#------------------------------------------------------------------------------

set(TARGET_PREFIX "uf-")

#---------------------
# Quick Find Target
#---------------------

set(TARGET_NAME "${TARGET_PREFIX}quick-find")

add_executable(${TARGET_NAME} "")

set_target_properties(${TARGET_NAME}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
)

target_link_libraries(${TARGET_NAME}
    stdc++fs
    ${GTEST_LIBRARY}
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

#---------------------
# Quick Union Target
#---------------------

set(TARGET_NAME "${TARGET_PREFIX}quick-union")

add_executable(${TARGET_NAME} "")

set_target_properties(${TARGET_NAME}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
)

target_link_libraries(${TARGET_NAME}
    stdc++fs
    ${GTEST_LIBRARY}
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

#---------------------
# Union Find Target
#---------------------

set(TARGET_NAME "${TARGET_PREFIX}union-find")

add_executable(${TARGET_NAME} "")

set_target_properties(${TARGET_NAME}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
)

target_link_libraries(${TARGET_NAME}
    stdc++fs
    ${GTEST_LIBRARY}
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

#---------------------
# Percolation Target
#---------------------

set(TARGET_NAME "${TARGET_PREFIX}percolation")

add_executable(${TARGET_NAME} "")

set_target_properties(${TARGET_NAME}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
)

target_link_libraries(${TARGET_NAME}
    stdc++fs
    ${GTEST_LIBRARY}
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
