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

    template <typename Compare>
    Node* merge_sort(Node* node, Compare comp); // Recursive merge sort

    template <typename Compare>
    Node* merge(Node* left, Node* right, Compare comp); // Merge two sorted lists

    Node* find_middle(Node* node); // Helper to find the middle of the list


public:
    // Constructors and Destructor
    List();
    List(std::initializer_list<T> list); // Initializer list constructor
    ~List();

    // Sorting
    void sort(); // Default ascending sort
    template <typename Compare>
    void sort(Compare comp); // Custom comparator sort

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
    Node* rbegin();
    Node* rend();

    // Comparison ops
    bool operator==(const List& other) const;


};

} // namespace CustomCXX

#include "../src/List.tpp"

#endif // CUSTOMCXX_LIST_H
