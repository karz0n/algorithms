set(TARGET "EventDriven-Library")

add_library(${TARGET})
add_library("EventDriven::Library" ALIAS ${TARGET})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

target_sources(
        ${TARGET}
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/CollisionSystem.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/DrawArea.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/DrawObject.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Event.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Particle.hpp
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/CollisionSystem.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/DrawArea.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/DrawObject.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Event.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Particle.cpp)

target_link_libraries(${TARGET} PUBLIC Queue::Library OpenGL::GLU GLUT::GLUT)

target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(ALG_ENABLE_TESTS)
    add_subdirectory(test)
endif()
