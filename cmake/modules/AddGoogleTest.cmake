include(GoogleTest)

if(DEFINED ENV{GTEST_ROOT})
    list(APPEND CMAKE_PREFIX_PATH $ENV{GTEST_ROOT})
endif()

find_package(GTest CONFIG REQUIRED)

if (TARGET GTest::gtest)
    get_property(
            GTEST_LOCATION
            TARGET GTest::gtest
            PROPERTY LOCATION)
    message(STATUS "Found GTest: ${GTEST_LOCATION}")
else ()
    message(FATAL_ERROR "GTest library NOT found")
endif ()

if (TARGET GTest::gmock)
    get_property(
            GMOCK_LOCATION
            TARGET GTest::gmock
            PROPERTY LOCATION)
    message(STATUS "Found GMock: ${GMOCK_LOCATION}")
else ()
    message(FATAL_ERROR "GMock library NOT found")
endif ()

function(TARGET_ADD_TESTS)
    set(options)
    set(oneValueArgs TARGET)
    set(multiValueArgs)
    cmake_parse_arguments(P "${options}" "${oneValueArgs}" "${multiValueArgs}"
            ${ARGN})
    target_link_libraries(${P_TARGET} PRIVATE GTest::gtest GTest::gtest_main
            GTest::gmock GTest::gmock_main)
    gtest_add_tests(TARGET ${P_TARGET})
endfunction()
