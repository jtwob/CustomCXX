cmake_minimum_required(VERSION 3.15)
project(CustomCXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directories
include_directories(include)

# Google Test
enable_testing()

# GoogleTest: Fetch the library automatically
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

# Define a function to run tests under Valgrind
function(add_valgrind_test TEST_NAME EXECUTABLE)
    add_test(
        NAME ${TEST_NAME}_Valgrind
        COMMAND valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 ./${EXECUTABLE}
    )
endfunction()

# Add Valgrind tests for each test executable
add_valgrind_test(CustomCXXTests_Vector CustomCXXTests_Vector)
add_valgrind_test(CustomCXXTests_List CustomCXXTests_List)
add_valgrind_test(CustomCXXTests_Map CustomCXXTests_Map)

# Add the header-only library
add_library(CustomCXX INTERFACE)
target_include_directories(CustomCXX INTERFACE include)

# Enable tests
enable_testing()

# Add the test executables
add_executable(CustomCXXTests_Vector
    tests/test_vector.cpp
)
target_link_libraries(CustomCXXTests_Vector PRIVATE CustomCXX gtest_main)

# Register Vector tests
add_test(NAME CustomCXXTests_Vector COMMAND CustomCXXTests_Vector)

add_executable(CustomCXXTests_List
    tests/test_list.cpp
)
target_link_libraries(CustomCXXTests_List PRIVATE CustomCXX gtest_main)

# Register List tests
add_test(NAME CustomCXXTests_List COMMAND CustomCXXTests_List)

# Add the Map test executables
add_executable(CustomCXXTests_Map
    tests/test_map.cpp
)
target_link_libraries(CustomCXXTests_Map PRIVATE CustomCXX gtest_main)

# Register Map tests
add_test(NAME CustomCXXTests_Map COMMAND CustomCXXTests_Map)

# Test Logging
add_custom_target(generate_log
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure -C $<CONFIG> > ${CMAKE_BINARY_DIR}/test_output.log
    COMMENT "Generating test log file..."
)