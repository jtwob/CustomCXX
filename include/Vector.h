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
    Vector();                              // Default constructor
    explicit Vector(size_t initial_size);  // Constructor with initial size
    Vector(std::initializer_list<T> list); // Initializer list constructor
    Vector(const Vector& other);           // Copy constructor
    Vector(Vector&& other) noexcept;       // Move constructor
    ~Vector();                             // Destructor

    // Sorting
    void sort(); // Default ascending sort
    template <typename Compare>
    void sort(Compare comp); // Custom comparator sort

    // Assignment Operators
    Vector& operator=(const Vector& other); // Copy assignment operator
    Vector& operator=(Vector&& other) noexcept; // Move assignment operator

    // Element Access
    T& operator[](size_t index);             // Non-const subscript operator
    const T& operator[](size_t index) const; // Const subscript operator

    // Modifiers
    void push_back(const T& value); // Adds an element to the end
    void pop_back();                // Removes the last element
    void clear(); // Removes all elements
    void insert(size_t index, const T& value); // Inserts an element 
    void erase(size_t index); // Removes an element at a given index 

    // Capacity
    size_t size() const;    // Returns the number of elements
    size_t capacity() const; // Returns the total capacity
    void reserve(size_t new_capacity); // Reserves memory
    void shrink_to_fit();   // Shrinks capacity to fit size

    // Iterators
    T* begin();  // Returns pointer to the first element
    T* end();    // Returns pointer to one past the last element
    T* rbegin(); // Returns pointer to the last element
    T* rend();   // Returns pointer to one before the first element


    // Copy Semantics
};

} // namespace CustomCXX

#include "../src/Vector.tpp" // Include the implementation

#endif // CUSTOMCXX_VECTOR_H