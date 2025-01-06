# CustomCXX
A lightweight C++ library implementing core data structures (`Vector`, `List`, and `Map`) with robust features, sorting algorithms, and comprehensive test coverage.

## Features
- **Dynamic Array (`Vector`)**: Supports push-back, resizing, sorting, and iterator functionality.
- **Doubly Linked List (`List`)**: Provides efficient insertion, deletion, traversal, and sorting with merge sort.
- **Hash Map (`Map`)**: Implements key-value storage with dynamic rehashing, collision handling, and retrieval of all keys.
- Fully templated for generic use.
- Sorting support for `Vector` and `List` with default and custom comparator functions.

## Why CustomCXX?
This project is designed as a learning tool for aspiring C++ developers. It demonstrates:
- Advanced use of templates and generic programming.
- Efficient memory management techniques.
- Modern C++ best practices (C++17+).
- The integration of custom data structures into practical applications.

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
#include "Map.h"
```

## Example Vector

```
CustomCXX::Vector<int> vec = {1, 3, 2};
vec.push_back(4);
vec.sort(); // Default ascending sort
for (auto it = vec.begin(); it != vec.end(); ++it) {
    std::cout << *it << " ";
}
```

## Example List

```
CustomCXX::List<int> list = {3, 1, 2};
list.push_back(4);
list.sort([](int a, int b) { return a > b; }); // Custom descending sort
for (auto it = list.begin(); it != list.end(); ++it) {
    std::cout << it->value << " ";
}
```

## Example Map

```
CustomCXX::Map<int, std::string> map;
map[1] = "one";
map[2] = "two";
map.insert_or_assign(3, "three");
for (const auto& key : map.keys()) {
    std::cout << key << ": " << map[key] << std::endl;
}
```

## Running Tests
Build and run the tests:
```bash
 ctest --test-dir build -C Debug --output-on-failure
```

## Future Enhancements
- Additional Algorithms (e.g., binary search, quicksort)
- New Data Structures (e.g., tree-based maps, heaps, priority queues)
- Further Optimizations for Performance

## Author
**James Totah**  
Aspiring software developer with a passion for crossdisciplinary projects. This project showcases robust implementations of core data structures (`Vector`, `List`, and `Map`) as part of my journey to mastering modern C++. I aim to create tools and libraries that are educational, efficient, and reusable.

Feel free to connect with me on [GitHub](https://github.com/jtwob) or [LinkedIn](https://www.linkedin.com/in/james-totah-337714188/) to discuss ideas or collaborate on future projects!