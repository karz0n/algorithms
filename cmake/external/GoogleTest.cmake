list(APPEND CMAKE_PREFIX_PATH "~/opt/googletest")

find_package(GTest CONFIG REQUIRED)

if (TARGET GTest::gtest)
    get_property(GTEST_LOCATION
        TARGET
            GTest::gtest
        PROPERTY
            LOCATION)
    message(STATUS "Found GTest :${GTEST_LOCATION}")
else()
    message(FATAL_ERROR "GTest library NOT found")
endif()

if (TARGET GTest::gmock)
    get_property(GMOCK_LOCATION
        TARGET
            GTest::gmock
        PROPERTY
            LOCATION)
    message(STATUS "Found GMock :${GMOCK_LOCATION}")
else()
    message(FATAL_ERROR "GMock library NOT found")
endif()
