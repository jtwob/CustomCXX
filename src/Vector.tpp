#include "../include/Vector.h"
#include <iostream>

namespace CustomCXX {

    /**
     * @brief Default constructor for Vector.
     * Initializes an empty Vector with no allocated memory.
     */
    template <typename T>
    Vector<T>::Vector() : _data(nullptr), _capacity(0), _size(0) {}

    /**
     * @brief Destructor for Vector.
     * Releases allocated memory.
     */
    template <typename T>
    Vector<T>::~Vector() {
        delete[] _data;
    }

    /**
     * @brief Resizes the internal storage of the Vector.
     * @param new_capacity The new capacity for the Vector.
     */
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

    /**
     * @brief Adds an element to the end of the Vector.
     * @param value The value to add.
     */
    template <typename T>
    void Vector<T>::push_back(const T& value) {
        if (_size == _capacity) {
            resize(_capacity == 0 ? 1 : _capacity * 2);
        }
        _data[_size++] = value;
    }

    /**
     * @brief Removes the last element from the Vector.
     * @throws std::underflow_error If the Vector is empty.
     */
    template <typename T>
    void Vector<T>::pop_back() {
        if (_size == 0) {
            throw std::underflow_error("Vector is empty");
        }
        --_size;
    }

    /**
     * @brief Accesses an element at the given index (non-const).
     * @param index The index of the element.
     * @return Reference to the element at the index.
     * @throws std::out_of_range If the index is out of bounds.
     */
    template <typename T>
    T& Vector<T>::operator[](size_t index) {
        if (index >= _size) {
            throw std::out_of_range("Index out of range");
        }
        return _data[index];
    }

    /**
     * @brief Accesses an element at the given index (const).
     * @param index The index of the element.
     * @return Const reference to the element at the index.
     * @throws std::out_of_range If the index is out of bounds.
     */
    template <typename T>
    const T& Vector<T>::operator[](size_t index) const {
        if (index >= _size) {
            throw std::out_of_range("Index out of range");
        }
        return _data[index];
    }

    /**
     * @brief Constructs a Vector from an initializer list.
     * @param list An initializer list of elements.
     */
    template <typename T>
    Vector<T>::Vector(std::initializer_list<T> list)
        : _data(new T[list.size()]), _capacity(list.size()), _size(list.size()) {
        size_t i = 0;
        for (const auto& elem : list) {
            _data[i++] = elem;
        }
    }

    /**
     * @brief Returns the number of elements in the Vector.
     * @return The size of the Vector.
     */
    template <typename T>
    size_t Vector<T>::size() const {
        return _size;
    }

    /**
     * @brief Returns the total capacity of the Vector.
     * @return The capacity of the Vector.
     */
    template <typename T>
    size_t Vector<T>::capacity() const {
        return _capacity;
    }

    /**
     * @brief Returns an iterator to the beginning of the Vector.
     * @return Pointer to the first element.
     */
    template <typename T>
    T* Vector<T>::begin() {
        return _data;
    }

    /**
     * @brief Returns an iterator to the end of the Vector.
     * @return Pointer to one past the last element.
     */
    template <typename T>
    T* Vector<T>::end() {
        return _data + _size;
    }

    /**
     * @brief Clears all elements from the Vector.
     */
    template <typename T>
    void Vector<T>::clear() {
        _size = 0; // Reset the size to zero
    }

    /**
     * @brief Inserts an element at a specific index.
     * @param index The index where the element should be inserted.
     * @param value The value to insert.
     * @throws std::out_of_range If the index is out of bounds.
     */
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

    /**
     * @brief Removes an element at a specific index.
     * @param index The index of the element to remove.
     * @throws std::out_of_range If the index is out of bounds.
     */
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

    /**
     * @brief Move constructor for Vector.
     * Transfers ownership of resources from another Vector.
     * 
     * @param other The Vector to move from.
     * 
     * After the move, the source Vector will be in a valid but unspecified state.
     */
    template <typename T>
    Vector<T>::Vector(Vector&& other) noexcept
        : _data(other._data), _capacity(other._capacity), _size(other._size) {
        other._data = nullptr;
        other._capacity = 0;
        other._size = 0;
    }

    /**
     * @brief Move assignment operator for Vector.
     * Transfers ownership of resources from another Vector.
     * 
     * @param other The Vector to move from.
     * @return A reference to the assigned Vector.
     * 
     * After the move, the source Vector will be in a valid but unspecified state.
     */
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

    /**
     * @brief Copy constructor for Vector.
     * Creates a deep copy of another Vector.
     * 
     * @param other The Vector to copy from.
     */
    template <typename T>
    Vector<T>::Vector(const Vector& other)
        :_data(new T[other._capacity]), _capacity(other._capacity), _size(other._size) {
        for (size_t i = 0; i < _size; ++i) {
            _data[i] = other._data[i];
        }
    }

     /**
     * @brief Copy assignment operator for Vector.
     * Creates a deep copy of another Vector.
     * 
     * @param other The Vector to copy from.
     * @return A reference to the assigned Vector.
     */
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

    /**
     * @brief Reserves memory for at least the given capacity.
     * @param new_capacity The new capacity to reserve.
     */
    template <typename T>
    void Vector<T>::reserve(size_t new_capacity) {
        if(new_capacity > _capacity){
            resize(new_capacity); // Use resize to handle memory reallocation
        }
    }

    /**
     * @brief Reduces capacity to fit the current size.
     */
    template <typename T>
    void Vector<T>::shrink_to_fit() {
        if (_capacity > _size) {
            resize(_size); // Reduce capacity to match size
        }
    }

    /**
     * @brief Returns a reverse iterator pointing to the last element of the Vector.
     * 
     * @return Pointer to the last element or `_data` if the Vector is empty.
     */
    template <typename T>
    T* Vector<T>::rbegin() {
        return _size > 0 ? (_data + _size - 1) : _data; // Pointer to the last element or Return _data if empty
    }

    /**
     * @brief Returns a reverse iterator pointing before the first element of the Vector.
     * 
     * @return Pointer to one position before `_data`.
     */
    template <typename T>
    T* Vector<T>::rend() {
        return _data - 1; // Pointer to one before the first element
    }

/**
     * @brief Performs a merge sort on the Vector within a specified range.
     * 
     * @tparam Compare A callable comparator to determine the sorting order.
     * @param left The starting index of the range.
     * @param right The ending index of the range.
     * @param comp The comparator function.
     * 
     * This function is a recursive implementation of merge sort that divides the range 
     * into smaller subranges and merges them in sorted order.
     */
    template <typename T>
    template <typename Compare>
    void Vector<T>::merge_sort(size_t left, size_t right, Compare comp) {
        if (left >= right) {
            return; // Base case: single element or invalid range
        }
        size_t mid = left + (right - left) / 2;

        merge_sort(left, mid, comp);
        merge_sort(mid + 1, right, comp);

        merge(left, mid, right, comp);
        
    }

    /**
     * @brief Merges two sorted subarrays within the Vector.
     * 
     * @tparam Compare A callable comparator to determine the sorting order.
     * @param left The starting index of the left subarray.
     * @param mid The ending index of the left subarray.
     * @param right The ending index of the right subarray.
     * @param comp The comparator function.
     * 
     * This function merges two sorted subarrays [left, mid] and [mid+1, right] into a single sorted array.
     */
    template <typename T>
    template <typename Compare>
    void Vector<T>::merge(size_t left, size_t mid, size_t right, Compare comp) {
        size_t n1 = mid - left + 1;
        size_t n2 = right - mid;

        T* leftArray = new T[n1];
        T* rightArray = new T[n2];

        for (size_t i = 0; i < n1; ++i) {
            leftArray[i] = _data[left + i];
        }
        for (size_t j = 0; j < n2; ++j) {
            rightArray[j] = _data[mid + 1 + j];
        }

        // Merge the temporary arrays back into _data
        size_t i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (comp(leftArray[i], rightArray[j])) {
                _data[k++] = leftArray[i++];
            } else {
                _data[k++] = rightArray[j++];
            }
        }
        while (i < n1) {
            _data[k++] = leftArray[i++];
        }
        while (j < n2) {
            _data[k++] = rightArray[j++];
        }

        delete[] leftArray;
        delete[] rightArray;
    }

    /**
     * @brief Sorts the Vector in ascending order.
     */
    template <typename T>
    void Vector<T>::sort() {
        if (_size == 0 || _size == 1) {
            return; // No need to sort
        }
        merge_sort(0, _size - 1, std::less<T>());
    }

    /**
     * @brief Sorts the Vector using a custom comparator.
     * @tparam Compare A callable comparator to determine the order.
     * @param comp The custom comparison function.
     */
    template <typename T>
    template <typename Compare>
    void Vector<T>::sort(Compare comp) {
        if (_size == 0 || _size == 1) {
            return; // No need to sort
        }
        merge_sort(0, _size - 1, comp);
    }

    /**
     * @brief Equality operator for Vector.
     * 
     * Compares two Vectors for equality.
     * 
     * @param other The Vector to compare with.
     * @return `true` if the two Vectors have the same size and all corresponding elements are equal, `false` otherwise.
     * 
     * The comparison is element-wise and checks both the size and the contents of the Vectors.
     */
    template <typename T>
    bool Vector<T>::operator==(const Vector<T>& other) const {
        if (_size != other._size) {
            return false; // Sizes must match
        }
        for (size_t i = 0; i < _size; ++i) {
            if (_data[i] != other._data[i]) {
                return false; // Elements must match
            }
        }
        return true; // All elements match
    }

// Add more methods...

} // namespace CustomCXX
