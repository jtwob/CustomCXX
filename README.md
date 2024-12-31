# CustomCXX
A lightweight C++ library implementing core data structures (`Vector` and `List`) with robust features and test coverage.

## Features
- Dynamic array (`Vector`) with push-back, resizing, and iterator support.
- Doubly linked list (`List`) with insertion, deletion, and traversal.
- Fully templated for generic use.

## Why CustomCXX?
This project is designed as a learning tool for aspiring C++ developers. It demonstrates:
- Advanced use of templates and generic programming.
- Efficient memory management techniques.
- Modern C++ best practices (C++17+).

## Getting Started
### Prerequisites
- C++17 or later
- CMake (for building the project)

### Installation
Clone the repository and build using CMake:
```bash
git clone https://github.com/jtwob/CustomCXX.git
cd CustomCXX
mkdir build && cd build
cmake ..
cmake --build .
```
## Usage
```
#include "Vector.h"
#include "List.h"
```
## Running Tests
Build and run the tests:
```bash
 ctest --test-dir build -C Debug --output-on-failure
```

