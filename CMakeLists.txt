cmake_minimum_required(VERSION 3.15)
project(CustomCXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directories
include_directories(include)

# Add the header-only library
add_library(CustomCXX INTERFACE)
target_include_directories(CustomCXX INTERFACE include)

# Add the test executable
add_executable(CustomCXXTests tests/test_vector.cpp)
target_link_libraries(CustomCXXTests PRIVATE CustomCXX)

# Enable testing and register the test
enable_testing()
add_test(NAME CustomCXXTests COMMAND CustomCXXTests)