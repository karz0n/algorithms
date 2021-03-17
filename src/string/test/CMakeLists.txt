set(TARGET "String-Test")

add_executable(${TARGET} "")

target_link_libraries(${TARGET} PRIVATE String::Library)

target_sources(
    ${TARGET}
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/LsdRadixSortTest.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/MsdRadixSortTest.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/ThreeWayRadixSortTest.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/LongestCommonPrefixTest.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/TernarySearchTriesTest.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/TrioSubstringSearchTest.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/BoyerMooreSubstringSearchTest.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/RabinKarpSubstringSearchTest.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/RegExpMatcherTest.cpp")

target_add_tests(TARGET ${TARGET})
