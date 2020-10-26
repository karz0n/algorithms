set(TARGET "Sort-Library")

add_library(${TARGET} INTERFACE)
add_library("Sort::Library" ALIAS ${TARGET})

target_sources(
    ${TARGET}
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include/BottomUpMerge.hpp
              ${CMAKE_CURRENT_SOURCE_DIR}/include/Insertion.hpp
              ${CMAKE_CURRENT_SOURCE_DIR}/include/Merge.hpp
              ${CMAKE_CURRENT_SOURCE_DIR}/include/Quick.hpp
              ${CMAKE_CURRENT_SOURCE_DIR}/include/Selection.hpp
              ${CMAKE_CURRENT_SOURCE_DIR}/include/Shell.hpp
              ${CMAKE_CURRENT_SOURCE_DIR}/include/ThreeWayQuick.hpp)

target_include_directories(${TARGET}
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${TARGET} INTERFACE Tools::Library)

if(ALG_ENABLE_TESTS)
    add_subdirectory(test)
endif()
