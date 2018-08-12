# Import GoogleTest (gtest/gmock) library.
#
# Generated library target names contained in variable:
#   GMOCK_LIBRARY
#   GTEST_LIBRARY
#
# You have to include this file before using.
#
# After including you can link your target with these library
# targets as usual.

include(ExternalProject)

#-------------------------------------------------------------------------------
# Dependencies
#-------------------------------------------------------------------------------

find_package(Threads REQUIRED)

#-------------------------------------------------------------------------------
# Downloading source
#-------------------------------------------------------------------------------

ExternalProject_Add(googletest
    GIT_REPOSITORY
        https://github.com/google/googletest
    GIT_TAG
        master
    PREFIX
        googletest
    CONFIGURE_COMMAND
        ""
    BUILD_COMMAND
        ""
    INSTALL_COMMAND
        ""
    LOG_DOWNLOAD
        ON
)

ExternalProject_Get_property(googletest SOURCE_DIR)
set(GMAIN_SOURCE_DIR ${SOURCE_DIR})

set(GTEST_SOURCE_DIR ${GMAIN_SOURCE_DIR}/googletest)
set(GMOCK_SOURCE_DIR ${GMAIN_SOURCE_DIR}/googlemock)

set(GTEST_INCLUDE_DIR ${GTEST_SOURCE_DIR}/include)
set(GMOCK_INCLUDE_DIR ${GMOCK_SOURCE_DIR}/include)

#-------------------------------------------------------------------------------
# Compiling gtest
#-------------------------------------------------------------------------------

set(GTEST_LIBRARY gtest)

ExternalProject_Add(${GTEST_LIBRARY}_compile
    DEPENDS
        googletest
    PREFIX
        ${GTEST_LIBRARY}
    SOURCE_DIR
        ${GTEST_SOURCE_DIR}
    DOWNLOAD_COMMAND
        ""
    INSTALL_COMMAND
        ""
    LOG_CONFIGURE
        ON
    LOG_BUILD
        ON
)

ExternalProject_Get_property(${GTEST_LIBRARY}_compile BINARY_DIR)
set(GTEST_BINARY_DIR ${BINARY_DIR})

add_library(${GTEST_LIBRARY} INTERFACE)

target_link_libraries(${GTEST_LIBRARY}
    INTERFACE
        ${GTEST_BINARY_DIR}/${CMAKE_FIND_LIBRARY_PREFIXES}gtest.a
        ${GTEST_BINARY_DIR}/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main.a
        # Include thread library of the system to the final target
        ${CMAKE_THREAD_LIBS_INIT}
)

target_include_directories(${GTEST_LIBRARY}
    INTERFACE
        ${GTEST_INCLUDE_DIR}
)

#-------------------------------------------------------------------------------
# Compiling gmock
#-------------------------------------------------------------------------------

set(GMOCK_LIBRARY gmock)

ExternalProject_Add(${GMOCK_LIBRARY}_compile
    DEPENDS
        googletest
    PREFIX
        ${GMOCK_LIBRARY}
    SOURCE_DIR
        ${GMOCK_SOURCE_DIR}
    DOWNLOAD_COMMAND
        ""
    INSTALL_COMMAND
        ""
    LOG_CONFIGURE
        ON
    LOG_BUILD
        ON
)

ExternalProject_Get_property(${GMOCK_LIBRARY}_compile BINARY_DIR)
set(GMOCK_BINARY_DIR ${BINARY_DIR})

add_library(${GMOCK_LIBRARY} INTERFACE)

target_link_libraries(${GMOCK_LIBRARY}
    INTERFACE
        ${GMOCK_BINARY_DIR}/${CMAKE_FIND_LIBRARY_PREFIXES}gmock.a
        ${GMOCK_BINARY_DIR}/${CMAKE_FIND_LIBRARY_PREFIXES}gmock_main.a
        # Include thread library of the system to the final target
        ${CMAKE_THREAD_LIBS_INIT}
)

target_include_directories(${GMOCK_LIBRARY}
    INTERFACE
        ${GMOCK_INCLUDE_DIR}
)
