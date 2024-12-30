#include "../include/List.h"

namespace CustomCXX {

template <typename T>
List<T>::List() : head(nullptr), tail(nullptr), list_size(0) {}

template <typename T>
List<T>::~List() {
    clear(); // Delete all nodes
}

template <typename T>
void List<T>::push_front(const T& value) {
    Node* new_node = new Node(value);
    new_node->next = head;
    head = new_node;
    if (!tail) tail = new_node; // If list was empty, tail is also updated
    ++list_size;
}

template <typename T>
void List<T>::push_back(const T& value) {
    Node* new_node = new Node(value);
    if (tail) {
        tail->next = new_node;
    } else {
        head = new_node; // If list was empty, head is also updated
    }
    tail = new_node;
    ++list_size;
}

template <typename T>
void List<T>::pop_front() {
    if (!head) throw std::underflow_error("List is empty");
    Node* temp = head;
    head = head->next;
    delete temp;
    if (!head) tail = nullptr; // If the list becomes empty
    --list_size;
}

template <typename T>
void List<T>::pop_back() {
    if (!tail) throw std::underflow_error("List is empty");
    if (head == tail) {
        delete head;
        head = tail = nullptr;
    } else {
        Node* current = head;
        while (current->next != tail) {
            current = current->next;
        }
        delete tail;
        tail = current;
        tail->next = nullptr;
    }
    --list_size;
}

template <typename T>
void List<T>::clear() {
    while (head) {
        pop_front();
    }
}

template <typename T>
T& List<T>::front() {
    if (!head) throw std::underflow_error("List is empty");
    return head->value;
}

template <typename T>
T& List<T>::back() {
    if (!tail) throw std::underflow_error("List is empty");
    return tail->value;
}

template <typename T>
T& List<T>::at(size_t index) {
    if (index >= list_size) throw std::out_of_range("Index out of range");
    Node* current = head;
    for (size_t i = 0; i < index; ++i) {
        current = current->next;
    }
    return current->value;
}

template <typename T>
size_t List<T>::size() const {
    return list_size;
}

template <typename T>
bool List<T>::empty() const {
    return list_size == 0;
}

} // namespace CustomCXX
