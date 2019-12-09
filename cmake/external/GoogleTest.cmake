include(FetchContent)

set(_NAME googletest)
set(_TAG master)
set(_URL https://github.com/google/googletest)

FetchContent_Declare(
  ${_NAME}
  GIT_REPOSITORY ${_URL}
  GIT_TAG ${_TAG}
)

FetchContent_GetProperties(${_NAME})
if(${_NAME}_POPULATED)
    message(STATUS "${_NAME} has already populated")
    return()
endif()
FetchContent_Populate(${_NAME})

set(_SOURCE_DIR ${${_NAME}_SOURCE_DIR})
set(_BINARY_DIR ${${_NAME}_BINARY_DIR})

#
# Configure and compile
#
execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" ${_SOURCE_DIR}
    WORKING_DIRECTORY "${_BINARY_DIR}" )
execute_process(COMMAND "${CMAKE_COMMAND}" --build . --parallel
    WORKING_DIRECTORY "${_BINARY_DIR}" )

find_package(Threads REQUIRED)

#
# Define GTest library target
#
add_library(${_NAME}-gtest INTERFACE IMPORTED GLOBAL)
target_link_libraries(${_NAME}-gtest
    INTERFACE
        ${_BINARY_DIR}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}gtest${CMAKE_STATIC_LIBRARY_SUFFIX}
        ${_BINARY_DIR}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}gtest_main${CMAKE_STATIC_LIBRARY_SUFFIX}
    )
target_include_directories(${_NAME}-gtest
    INTERFACE ${_SOURCE_DIR}/googletest/include)
set_property(TARGET ${_NAME}-gtest
             APPEND
             PROPERTY INTERFACE_LINK_LIBRARIES ${CMAKE_THREAD_LIBS_INIT})

#
# Define GMock library target
#
add_library(${_NAME}-gmock INTERFACE IMPORTED GLOBAL)
target_link_libraries(${_NAME}-gmock
    INTERFACE
        ${_BINARY_DIR}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}gmock${CMAKE_STATIC_LIBRARY_SUFFIX}
        ${_BINARY_DIR}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}gmock_main${CMAKE_STATIC_LIBRARY_SUFFIX}
    )
target_include_directories(${_NAME}-gmock
    INTERFACE ${_SOURCE_DIR}/googlemock/include)
set_property(TARGET ${_NAME}-gmock
             APPEND
             PROPERTY INTERFACE_LINK_LIBRARIES ${CMAKE_THREAD_LIBS_INIT})
