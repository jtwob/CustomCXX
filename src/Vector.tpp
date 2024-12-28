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
    _capacity = new_capacity; // Ensure capacity is updated
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
    if (index >= _size) {
        throw std::out_of_range("Index out of range");
    }
    return _data[index];
}

template <typename T>
const T& Vector<T>::operator[](size_t index) const {
    if (index >= _size) {
        throw std::out_of_range("Index out of range");
    }
    return _data[index];
}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> list)
    : _data(new T[list.size()]), _capacity(list.size()), _size(list.size()) {
    size_t i = 0;
    for (const auto& elem : list) {
        _data[i++] = elem;
    }
}

template <typename T>
size_t Vector<T>::size() const {
    return _size;
}

template <typename T>
size_t Vector<T>::capacity() const {
    return _capacity;
}

template <typename T>
T* Vector<T>::begin() {
    return _data;
}

template <typename T>
T* Vector<T>::end() {
    return _data + _size;
}

// Add more methods...

} // namespace CustomCXX
