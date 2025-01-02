#include "../include/List.h"

namespace CustomCXX {

template <typename T>
List<T>::List() : head(nullptr), tail(nullptr), list_size(0) {}

template <typename T>
List<T>::List(std::initializer_list<T> list) : head(nullptr), tail(nullptr), list_size(0) {
    for (const auto& value : list) {
        push_back(value); // Reuse push_back to add elements
    }
}

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
        new_node->prev = tail;
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
    if (index >= list_size) {
        throw std::out_of_range("Index out of range");
    }

    Node* current = head;
    for (size_t i = 0; i < index; ++i) {
        if (!current) {
            throw std::runtime_error("Invalid traversal: encountered nullptr");
        }
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

template <typename T>
void List<T>::insert(size_t index, const T& value) {
    if (index > list_size) {
        throw std::out_of_range("Index out of range");
    }

    Node* new_node = new Node(value);

    if (index == 0) { // Insert at the beginning
        new_node->next = head;
        if (head) {
            head->prev = new_node;
        }
        head = new_node;
        if (!tail) {
            tail = new_node; // Update tail if list was empty
        }
    } else if (index == list_size) { // Insert at the end
        new_node->prev = tail;
        if (tail) {
            tail->next = new_node;
        }
        tail = new_node;
    } else { // Insert in the middle
        Node* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        new_node->next = current;
        new_node->prev = current->prev;
        if (current->prev) {
            current->prev->next = new_node;
        }
        current->prev = new_node;
    }
    ++list_size;
}

template <typename T>
void List<T>::erase(size_t index) {
    if (index >= list_size) {
        throw std::out_of_range("Index out of range");
    }

    Node* current = head;

    // Traverse to the node at the specified index
    for (size_t i = 0; i < index; ++i) {
        current = current->next;
    }

    // Case 1: Erase the first node
    if (current == head) {
        head = current->next;
        if (head) {
            head->prev = nullptr;
        } else {
            tail = nullptr; // List becomes empty
        }
    }
    // Case 2: Erase the last node
    else if (current == tail) {
        tail = current->prev;
        if (tail) {
            tail->next = nullptr;
        } else {
            head = nullptr; // List becomes empty
        }
    }
    // Case 3: Erase a middle node
    else {
        Node* prev_node = current->prev;
        Node* next_node = current->next;

        if (prev_node) {
            prev_node->next = next_node; // Link previous node to next
        }

        if (next_node) {
            next_node->prev = prev_node; // Link next node to previous
        }
    }

    delete current; // Free the memory of the erased node
    --list_size;

    // Ensure consistency when the list becomes empty
    if (list_size == 0) {
        head = tail = nullptr;
    }
}

template <typename T>
void List<T>::reverse() {
    Node* current = head;
    Node* temp = nullptr;

    while (current) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev; // Move to the next node in the original order
    }

    // Swap head and tail
    temp = head;
    head = tail;
    tail = temp;
}

template <typename T>
typename List<T>::Node* List<T>::begin() {
    return head;
}

template <typename T>
typename List<T>::Node* List<T>::end() {
    return nullptr; // End iterator points to one past the last element
}

template <typename T>
typename List<T>::Node* List<T>::rbegin() {
    return tail;
}

template <typename T>
typename List<T>::Node* List<T>::rend() {
    return nullptr; // Reverse end iterator points before the first element
}

template <typename T>
void List<T>::sort() {
    // TODO: Implement ascending sort
    throw std::logic_error("Not implemented");
}

template <typename T>
template <typename Compare>
void List<T>::sort(Compare comp) {
    // TODO: Implement custom comparator sort
    throw std::logic_error("Not implemented");
}

} // namespace CustomCXX
