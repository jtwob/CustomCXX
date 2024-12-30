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
        Node* prev; // Add this for a doubly linked list
        Node(T val) : value(val), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    size_t list_size;

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
    void insert(size_t index, const T& value); // Insert at a specific position
    void erase(size_t index); // Remove at a specific position
    void reverse(); // Reverse the list

    // Access
    T& front();
    T& back();
    T& at(size_t index);

    // Utilities
    size_t size() const;
    bool empty() const;

    // Iterators
    Node* begin();
    Node* end();
};

} // namespace CustomCXX

#include "../src/List.tpp"

#endif // CUSTOMCXX_LIST_H
