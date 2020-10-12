find_program(CCACHE_PROGRAM ccache)
if (CCACHE_PROGRAM)
    # Set up wrapper scripts
    set(C_LAUNCHER "${CCACHE_PROGRAM}")
    set(CXX_LAUNCHER "${CCACHE_PROGRAM}")
    configure_file("${CMAKE_CURRENT_LIST_DIR}/launch-c.sh.in" launch-c.sh)
    configure_file("${CMAKE_CURRENT_LIST_DIR}/launch-cxx.sh.in" launch-cxx.sh)
    execute_process(COMMAND chmod a+rx "${CMAKE_BINARY_DIR}/launch-c.sh"
            "${CMAKE_BINARY_DIR}/launch-cxx.sh")

    if (CMAKE_GENERATOR STREQUAL "Xcode")
        # Set Xcode project attributes to route compilation and linking through
        # our scripts
        set(CMAKE_XCODE_ATTRIBUTE_CC "${CMAKE_BINARY_DIR}/launch-c.sh")
        set(CMAKE_XCODE_ATTRIBUTE_CXX "${CMAKE_BINARY_DIR}/launch-cxx.sh")
        set(CMAKE_XCODE_ATTRIBUTE_LD "${CMAKE_BINARY_DIR}/launch-c.sh")
        set(CMAKE_XCODE_ATTRIBUTE_LDPLUSPLUS
                "${CMAKE_BINARY_DIR}/launch-cxx.sh")
    else ()
        # Support Unix Makefiles and Ninja
        set(CMAKE_C_COMPILER_LAUNCHER "${CMAKE_BINARY_DIR}/launch-c.sh")
        set(CMAKE_CXX_COMPILER_LAUNCHER "${CMAKE_BINARY_DIR}/launch-cxx.sh")
    endif ()
endif ()
