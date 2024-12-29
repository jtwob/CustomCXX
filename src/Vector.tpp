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

template <typename T>
void Vector<T>::clear() {
    _size = 0; // Reset the size to zero
}

template <typename T>
void Vector<T>::insert(size_t index, const T& value) {
    if (index > _size) {
        throw std::out_of_range("Index out of range");
    }

    if (_size == _capacity) {
        resize(_capacity == 0 ? 1 : _capacity * 2); // Ensure capacity
    }

    // Shift elements to the right
    for (size_t i = _size; i > index; --i) {
        _data[i] = std::move(_data[i - 1]);
    }

    _data[index] = value; // Insert the value
    ++_size;
}

template <typename T>
void Vector<T>::erase(size_t index) {
    if (index >= _size) {
        throw std::out_of_range("Index out of range");
    }

    // Shift elements to the left
    for (size_t i = index; i < _size - 1; ++i) {
        _data[i] = std::move(_data[i + 1]);
    }

    --_size; // Decrease the size
}

template <typename T>
Vector<T>::Vector(Vector&& other) noexcept
    : _data(other._data), _capacity(other._capacity), _size(other._size) {
    other._data = nullptr;
    other._capacity = 0;
    other._size = 0;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept {
    if (this != &other) {
        delete[] _data; // Clean up existing resources

        _data = other._data;
        _capacity = other._capacity;
        _size = other._size;

        other._data = nullptr;
        other._capacity = 0;
        other._size = 0;
    }
    return *this;
}

template <typename T>
Vector<T>::Vector(const Vector& other)
    :_data(new T[other._capacity]), _capacity(other._capacity), _size(other._size) {
    for (size_t i = 0; i < _size; ++i) {
        _data[i] = other._data[i];
    }
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
    if (this != &other) { // Avoid self-assignment
        delete[] _data;

        _data = new T[other._capacity];
        _capacity = other._capacity;
        _size = other._size;

        for (size_t i = 0; i < _size; ++i) {
            _data[i] = other._data[i];
        }
    }
    return *this;
}

template <typename T>
void Vector<T>::reserve(size_t new_capacity) {
    if(new_capacity > _capacity){
        resize(new_capacity); // Use resize to handle memory reallocation
    }
}

template <typename T>
void Vector<T>::shrink_to_fit() {
    if (_capacity > _size) {
        resize(_size); // Reduce capacity to match size
    }
}

template <typename T>
T* Vector<T>::rbegin() {
    return _size > 0 ? (_data + _size - 1) : _data; // Pointer to the last element or Return _data if empty
}

template <typename T>
T* Vector<T>::rend() {
    return _data - 1; // Pointer to one before the first element
}
// Add more methods...

} // namespace CustomCXX
