set(TARGET "Tools-Test")

add_executable(${TARGET} "")

target_link_libraries(${TARGET} PRIVATE Tools::Library)

target_sources(
    ${TARGET}
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/CsvFileReaderTest.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/SequenceTest.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/PartitionTest.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/MemoryStreamBufferTest.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/DynamicBitSetTest.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/ByteOrderTest.cpp")

target_add_tests(TARGET ${TARGET})
