cmake_minimum_required(VERSION 3.15)
project(CustomCXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directories
include_directories(include)

# Enable testing framework
enable_testing()

# 🔹 GoogleTest: Fetch and build the library
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

# Ensure GoogleTest is included
include_directories(${gtest_SOURCE_DIR}/include)

# Create a header-only library for CustomCXX
add_library(CustomCXX INTERFACE)
target_include_directories(CustomCXX INTERFACE include)

# 🔹 Common function to add test executables
function(add_customcxx_test test_name source_file)
    add_executable(${test_name} ${source_file})
    target_link_libraries(${test_name} PRIVATE CustomCXX gtest gtest_main)
    gtest_discover_tests(${test_name})  # Auto-discover tests
    add_test(NAME ${test_name} COMMAND ${test_name}) # Register the test
endfunction()

# 🔹 Add Vector Tests
add_customcxx_test(CustomCXXTests_Vector tests/test_vector.cpp)

# 🔹 Add List Tests
add_customcxx_test(CustomCXXTests_List tests/test_list.cpp)

# 🔹 Add Map Tests
add_customcxx_test(CustomCXXTests_Map tests/test_map.cpp)

# 🔹 Test Logging
add_custom_target(generate_log
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure -C $<CONFIG> > ${CMAKE_BINARY_DIR}/test_output.log
    COMMENT "Generating test log file..."
)
