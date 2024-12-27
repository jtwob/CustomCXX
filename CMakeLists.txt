cmake_minimum_required(VERSION 3.15)
project(CustomCXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include source and header files
include_directories(include)

# Add library target
add_library(CustomCXX src/Vector.tpp)

# Add executable target for tests
add_executable(CustomCXXTests tests/test_vector.cpp)
target_link_libraries(CustomCXXTests PRIVATE CustomCXX)