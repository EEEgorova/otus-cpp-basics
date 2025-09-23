cmake_minimum_required(VERSION 3.7.2)

project(grep)

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

add_executable(GrepMain GrepMain.cpp)
add_executable(TestGrep 
               TestGrep.cpp
               TestsList.cpp)

# Link test target against gtest libraries
target_link_libraries(
    TestGrep PRIVATE
    gtest
)

set_target_properties(GrepMain PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
set_target_properties(TestGrep PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)