set(TARGET "Compression-Test")

add_executable(${TARGET} "")

target_link_libraries(${TARGET} PRIVATE Compression::Library)

target_sources(
    ${TARGET}
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/HuffmanTest.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/LzwTest.cpp")

target_add_tests(TARGET ${TARGET})