set(TARGET "Sort-Test")

add_executable(${TARGET} "")

target_link_libraries(${TARGET}
PRIVATE
    Sort::Library
)

target_sources(${TARGET}
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/BottomUpMergeTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/HeapSortTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/InsertionTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/MergeTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/QuickTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/SelectionTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ShellTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ThreeWayQuickTest.cpp
)

target_add_tests(TARGET ${TARGET})
