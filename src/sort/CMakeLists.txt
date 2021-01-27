set(TARGET "Sort-Library")

add_library(${TARGET})
add_library("Sort::Library" ALIAS ${TARGET})

target_sources(
    ${TARGET}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/BottomUpMergeSort.hpp
           ${CMAKE_CURRENT_SOURCE_DIR}/include/InsertionSort.hpp
           ${CMAKE_CURRENT_SOURCE_DIR}/include/MergeSort.hpp
           ${CMAKE_CURRENT_SOURCE_DIR}/include/QuickSort.hpp
           ${CMAKE_CURRENT_SOURCE_DIR}/include/SelectionSort.hpp
           ${CMAKE_CURRENT_SOURCE_DIR}/include/ShellSort.hpp
           ${CMAKE_CURRENT_SOURCE_DIR}/include/ThreeWayQuickSort.hpp)

target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${TARGET} PUBLIC Tools::Library)

if(ALG_ENABLE_TESTS)
    add_subdirectory(test)
endif()
