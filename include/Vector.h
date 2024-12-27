#ifndef CUSTOMCXX_VECTOR_H
#define CUSTOMCXX_VECTOR_H

#include <initializer_list>
#include <stdexcept>

namespace CustomCXX { // Open namespace

template <typename T>
class Vector {
private:
    T* _data;
    size_t _capacity;
    size_t _size;

    void resize(size_t new_capacity);

public:
    Vector();
    explicit Vector(size_t initial_size);
    Vector(std::initializer_list<T> list);
    ~Vector();

    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    void push_back(const T& value);
    void pop_back();

    size_t size() const;
    size_t capacity() const;

    T* begin();
    T* end();
};

} // namespace CustomCXX // Close namespace

#include "../src/Vector.tpp"

#endif // CUSTOMCXX_VECTOR_H
