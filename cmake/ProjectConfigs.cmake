list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/modules")

include(BuildLocation)
include(BuildType)
include(EnableCcache)

include(CxxTestCompiler)
checkforcxx20compiler(CXX20_COMPILER)
if(CXX20_COMPILER)
    enablecxx20()
else()
    message(FATAL_ERROR "The C++20 standard not supported")
endif()

if(ALG_ENABLE_TESTS)
    include(AddGoogleTest)
endif()
