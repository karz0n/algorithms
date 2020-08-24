set(TARGET "EventDriven-Test")

add_executable(${TARGET} "")

target_link_libraries(${TARGET}
PRIVATE
    EventDriven::Library
)

target_sources(${TARGET}
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/EventDrivenTest.cpp
)
