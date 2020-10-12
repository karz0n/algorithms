set(TARGET "List-Test")

add_executable(${TARGET} "")

target_link_libraries(${TARGET} PRIVATE List::Library)

target_include_directories(${TARGET}
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_sources(
        ${TARGET} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/LinkedListTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/LinkedListIteratorTest.cpp)

target_add_tests(TARGET ${TARGET})
