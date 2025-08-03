cmake_minimum_required(VERSION 3.2)

project(ProjestWithGTest)

if (MSVC)
    # @see https://github.com/google/googletest/blob/master/googletest/README.md
    # Visual Studio Dynamic vs Static Runtimes
    #By default, new Visual Studio projects link the C runtimes dynamically
    #but GoogleTest links them statically. This will generate an error
    #Enabling this option will make gtest link the runtimes dynamically too
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

# Build googletest
add_subdirectory(
    "${CMAKE_CURRENT_SOURCE_DIR}/googletest" 
    "googletest"
)

# Test target
add_executable(
    containers_tests
    tests/containers_tests.cpp
    tests/list_tests.cpp
    tests/vector_tests.cpp
)

# Link test target against gtest libraries
target_link_libraries(
    containers_tests PRIVATE
    gtest
)

set_target_properties(containers_tests PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
