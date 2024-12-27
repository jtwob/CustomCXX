#include "../include/Vector.h"

namespace CustomCXX {

template <typename T>
Vector<T>::Vector() : _data(nullptr), _capacity(0), _size(0) {}

template <typename T>
Vector<T>::~Vector() {
    delete[] _data;
}

template <typename T>
void Vector<T>::resize(size_t new_capacity) {
    T* new_data = new T[new_capacity];
    for (size_t i = 0; i < _size; ++i) {
        new_data[i] = std::move(_data[i]);
    }
    delete[] _data;
    _data = new_data;
    _capacity = new_capacity;
}

template <typename T>
void Vector<T>::push_back(const T& value) {
    if (_size == _capacity) {
        resize(_capacity == 0 ? 1 : _capacity * 2);
    }
    _data[_size++] = value;
}

template <typename T>
void Vector<T>::pop_back() {
    if (_size == 0) {
        throw std::underflow_error("Vector is empty");
    }
    --_size;
}

template <typename T>
T& Vector<T>::operator[](size_t index) {
    return _data[index];
}

// Add more methods...

} // namespace CustomCXX
