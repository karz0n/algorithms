set(TARGET "String-Library")

add_library(${TARGET})
add_library("String::Library" ALIAS ${TARGET})

target_sources(
    ${TARGET}
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/Types.hpp"
           "${CMAKE_CURRENT_SOURCE_DIR}/include/LsdRadixSort.hpp"
           "${CMAKE_CURRENT_SOURCE_DIR}/include/MsdRadixSort.hpp"
           "${CMAKE_CURRENT_SOURCE_DIR}/include/ThreeWayRadixSort.hpp"
           "${CMAKE_CURRENT_SOURCE_DIR}/include/LongestCommonPrefix.hpp"
           "${CMAKE_CURRENT_SOURCE_DIR}/include/TernarySearchTries.hpp"
           "${CMAKE_CURRENT_SOURCE_DIR}/include/TrioSubstringSearch.hpp"
           "${CMAKE_CURRENT_SOURCE_DIR}/include/BoyerMooreSubstringSearch.hpp"
           "${CMAKE_CURRENT_SOURCE_DIR}/include/RabinKarpSubstringSearch.hpp"
           "${CMAKE_CURRENT_SOURCE_DIR}/include/RegExpMatcher.hpp"
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/LsdRadixSort.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/MsdRadixSort.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/ThreeWayRadixSort.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/LongestCommonPrefix.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/TernarySearchTries.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/RegExpMatcher.cpp")

target_include_directories(${TARGET} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries(${TARGET} PUBLIC Graph::Library)

if(ALG_ENABLE_TESTS)
    add_subdirectory(test)
endif()