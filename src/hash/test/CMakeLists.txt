set(TARGET "Hash-Test")

add_executable(${TARGET} "")

target_link_libraries(${TARGET} PRIVATE Hash::Library)

target_include_directories(${TARGET}
                           PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_sources(
    ${TARGET}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/HashTest.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/ChainingHashTreeTest.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/LinearProbingHashTree.cpp)

target_add_tests(TARGET ${TARGET})
