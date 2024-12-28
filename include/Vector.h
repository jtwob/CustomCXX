#ifndef CUSTOMCXX_VECTOR_H
#define CUSTOMCXX_VECTOR_H

#include <initializer_list>
#include <stdexcept>
#include <utility> // For std::move

namespace CustomCXX { // Open namespace

template <typename T>
class Vector {
private:
    T* _data;            // Pointer to dynamically allocated memory
    size_t _capacity;    // Total capacity of the vector
    size_t _size;        // Current number of elements in the vector

    void resize(size_t new_capacity); // Resizes the internal storage

public:
    // Constructors and Destructor
    Vector();                           // Default constructor
    explicit Vector(size_t initial_size); // Constructor with initial size
    Vector(std::initializer_list<T> list); // Initializer list constructor
    ~Vector();                          // Destructor

    // Element Access
    T& operator[](size_t index);             // Non-const subscript operator
    const T& operator[](size_t index) const; // Const subscript operator

    // Modifiers
    void push_back(const T& value); // Adds an element to the end
    void pop_back();                // Removes the last element

    // Capacity
    size_t size() const;    // Returns the number of elements
    size_t capacity() const; // Returns the total capacity

    // Iterators
    T* begin(); // Returns pointer to the first element
    T* end();   // Returns pointer to one past the last element

    // Future Enhancements (Optional)
    void clear(); // Removes all elements (to be implemented)
    void insert(size_t index, const T& value); // Inserts an element (to be implemented)
    void erase(size_t index); // Removes an element at a given index (to be implemented)

    // Move Semantics (Optional)
    Vector(Vector&& other) noexcept;            // Move constructor
    Vector& operator=(Vector&& other) noexcept; // Move assignment operator
};

} // namespace CustomCXX

#include "../src/Vector.tpp" // Include the implementation

#endif // CUSTOMCXX_VECTOR_H