set(TARGET "Stack-Test")

add_executable(${TARGET} "")

target_link_libraries(${TARGET} PRIVATE Stack::Library)

target_include_directories(${TARGET}
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_sources(
        ${TARGET}
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/ArithmeticEvaluator.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ArithmeticEvaluator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/StackTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ArithmeticEvaluatorTest.cpp)

target_add_tests(TARGET ${TARGET})
