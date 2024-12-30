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

# Enable tests
enable_testing()

# Add the test executables
add_executable(CustomCXXTests_Vector
    tests/test_vector.cpp
)
target_link_libraries(CustomCXXTests_Vector PRIVATE CustomCXX)

# Register Vector tests
add_test(NAME CustomCXXTests_Vector COMMAND CustomCXXTests_Vector)

add_executable(CustomCXXTests_List
    tests/test_list.cpp
)
target_link_libraries(CustomCXXTests_List PRIVATE CustomCXX)

# Register List tests
add_test(NAME CustomCXXTests_List COMMAND CustomCXXTests_List)

