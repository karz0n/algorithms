set(TARGET "Sort-Test")

add_executable(${TARGET} "")

target_link_libraries(${TARGET} PRIVATE Sort::Library)

target_sources(
    ${TARGET}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/BottomUpMergeSortTest.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/HeapSortTest.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/InsertionSortTest.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/MergeSortTest.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/QuickSortTest.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/SelectionSortTest.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/ShellSortTest.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/ThreeWayQuickSortTest.cpp)

target_add_tests(TARGET ${TARGET})
