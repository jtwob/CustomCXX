#ifndef CUSTOMCXX_LIST_H
#define CUSTOMCXX_LIST_H

#include <stdexcept>

namespace CustomCXX {

template <typename T>
class List {
private:
    struct Node {
        T value;
        Node* next;
        Node(T val) : value(val), next(nullptr) {}
    };

    Node* head; // Pointer to the first node
    Node* tail; // Pointer to the last node
    size_t list_size; // Number of elements in the list

public:
    // Constructors and Destructor
    List();
    ~List();

    // Modifiers
    void push_front(const T& value);
    void push_back(const T& value);
    void pop_front();
    void pop_back();
    void clear();

    // Access
    T& front();
    T& back();
    T& at(size_t index);

    // Utilities
    size_t size() const;
    bool empty() const;

    // Iterators (Optional)
    // Add later if needed
};

} // namespace CustomCXX

#include "../src/List.tpp"

#endif // CUSTOMCXX_LIST_H
