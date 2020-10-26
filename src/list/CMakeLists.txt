set(TARGET "List-Library")

add_library(${TARGET} INTERFACE)
add_library("List::Library" ALIAS ${TARGET})

target_sources(
    ${TARGET}
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include/LinkedList.hpp
              ${CMAKE_CURRENT_SOURCE_DIR}/include/LinkedListIterator.hpp
              ${CMAKE_CURRENT_SOURCE_DIR}/include/List.hpp
              ${CMAKE_CURRENT_SOURCE_DIR}/include/Node.hpp)

target_include_directories(${TARGET}
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(ALG_ENABLE_TESTS)
    add_subdirectory(test)
endif()
