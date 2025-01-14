#include "../include/List.h"

namespace CustomCXX {

    /**
     * @brief Constructs an empty List.
     */
    template <typename T>
    List<T>::List() : head(nullptr), tail(nullptr), list_size(0) {}

    /**
     * @brief Constructs a List from an initializer list.
     * @param list An initializer list of elements to populate the List.
     */
    template <typename T>
    List<T>::List(std::initializer_list<T> list) : head(nullptr), tail(nullptr), list_size(0) {
        for (const auto& value : list) {
            push_back(value); // Reuse push_back to add elements
        }
    }

    /**
     * @brief Destructor to clean up all nodes in the List.
     */
    template <typename T>
    List<T>::~List() {
        clear(); // Delete all nodes
    }

    /**
     * @brief Inserts a value at the front of the List.
     * @param value The value to insert.
     */
    template <typename T>
    void List<T>::push_front(const T& value) {
        Node* new_node = new Node(value);
        new_node->next = head;
        head = new_node;
        if (!tail) tail = new_node; // If list was empty, tail is also updated
        ++list_size;
    }

    /**
     * @brief Inserts a value at the back of the List.
     * @param value The value to insert.
     */
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

    /**
     * @brief Removes the front element of the List.
     * @throws std::underflow_error If the List is empty.
     */
    template <typename T>
    void List<T>::pop_front() {
        if (!head) throw std::underflow_error("List is empty");
        Node* temp = head;
        head = head->next;
        delete temp;
        if (!head) tail = nullptr; // If the list becomes empty
        --list_size;
    }

    /**
     * @brief Removes the last element of the List.
     * @throws std::underflow_error If the List is empty.
     */
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

    /**
     * @brief Clears all elements from the List.
     */
    template <typename T>
    void List<T>::clear() {
        while (head) {
            pop_front();
        }
    }

    /**
     * @brief Returns the first element in the List.
     * @return A reference to the first element.
     * @throws std::underflow_error If the List is empty.
     */
    template <typename T>
    T& List<T>::front() {
        if (!head) throw std::underflow_error("List is empty");
        return head->value;
    }

    /**
     * @brief Returns the last element in the List.
     * @return A reference to the last element.
     * @throws std::underflow_error If the List is empty.
     */
    template <typename T>
    T& List<T>::back() {
        if (!tail) throw std::underflow_error("List is empty");
        return tail->value;
    }

    /**
     * @brief Accesses the element at a specific index.
     * @param index The index of the element.
     * @return A reference to the element at the given index.
     * @throws std::out_of_range If the index is out of bounds.
     */
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

    /**
     * @brief Returns the number of elements in the List.
     * @return The size of the List.
     */
    template <typename T>
    size_t List<T>::size() const {
        return list_size;
    }

    /**
     * @brief Checks if the List is empty.
     * @return true if the List is empty, false otherwise.
     */
    template <typename T>
    bool List<T>::empty() const {
        return list_size == 0;
    }

    /**
     * @brief Inserts a value at a specific index.
     * @param index The index at which to insert.
     * @param value The value to insert.
     * @throws std::out_of_range If the index is invalid.
     */
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

    /**
     * @brief Removes an element at a specific index.
     * @param index The index of the element to remove.
     * @throws std::out_of_range If the index is invalid.
     */
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

    /**
     * @brief Reverses the List in place.
     */
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

    /**
     * @brief Returns an iterator pointing to the beginning of the List.
     * @return A pointer to the first node in the List.
     */
    template <typename T>
    typename List<T>::Node* List<T>::begin() {
        return head;
    }

    /**
     * @brief Returns an iterator pointing to one past the last element of the List.
     * @return A null pointer indicating the end of the List.
     */
    template <typename T>
    typename List<T>::Node* List<T>::end() {
        return nullptr; // End iterator points to one past the last element
    }

    /**
     * @brief Returns a reverse iterator pointing to the last element of the List.
     * @return A pointer to the last node in the List.
     */
    template <typename T>
    typename List<T>::Node* List<T>::rbegin() {
        return tail;
    }

    /**
     * @brief Returns a reverse iterator pointing before the first element of the List.
     * @return A null pointer indicating the reverse end of the List.
     */
    template <typename T>
    typename List<T>::Node* List<T>::rend() {
        return nullptr; // Reverse end iterator points before the first element
    }

     /**
     * @brief Recursively sorts a sublist using merge sort.
     * @tparam Compare A callable comparator to determine the order.
     * @param node Pointer to the head of the sublist to sort.
     * @param comp Comparator function for custom sorting.
     * @return A pointer to the head of the sorted sublist.
     */
    template <typename T>
    template <typename Compare>
    typename List<T>::Node* List<T>::merge_sort(Node* node, Compare comp) {
        if (!node || !node->next) {
            return node; // Base case: empty or single node
        }

        // Split the list into two halves
        Node* middle = find_middle(node);
        Node* second_half = middle->next;
        middle->next = nullptr;

        // Sort each half recursively
        Node* left = merge_sort(node, comp);
        Node* right = merge_sort(second_half, comp);

        // Merge the sorted halves
        return merge(left, right, comp);
    }

    /**
     * @brief Finds the middle node of a linked list.
     * @param node Pointer to the head of the list to find the middle of.
     * @return A pointer to the middle node.
     */
    template <typename T>
    typename List<T>::Node* List<T>::find_middle(Node* node) {
        Node* slow = node;
        Node* fast = node;

        while (fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow;
    }

     /**
     * @brief Merges two sorted sublists into one sorted list.
     * @tparam Compare A callable comparator to determine the order.
     * @param left Pointer to the head of the left sublist.
     * @param right Pointer to the head of the right sublist.
     * @param comp Comparator function for custom sorting.
     * @return A pointer to the head of the merged list.
     */
    template <typename T>
    template <typename Compare>
    typename List<T>::Node* List<T>::merge(Node* left, Node* right, Compare comp) {
        if (!left) return right;
        if (!right) return left;

        Node* result = nullptr;

        if (comp(left->value, right->value)) {
            result = left;
            result->next = merge(left->next, right, comp);
        } else {
            result = right;
            result->next = merge(left, right->next, comp);
        }

        return result;
    }

    /**
     * @brief Sorts the List in ascending order using merge sort.
     */
    template <typename T>
    void List<T>::sort() {
        head = merge_sort(head, std::less<T>());
    }

    /**
     * @brief Sorts the List using a custom comparator and merge sort.
     * @tparam Compare A callable comparator to determine the order.
     * @param comp The custom comparison function.
     */
    template <typename T>
    template <typename Compare>
    void List<T>::sort(Compare comp) {
        head = merge_sort(head, comp);
    }

    /**
     * @brief Compares two Lists for equality.
     * @param other The List to compare with.
     * @return true if the Lists are equal, false otherwise.
     */
    template <typename T>
    bool List<T>::operator==(const List& other) const {
        Node* this_current = head;
        Node* other_current = other.head;

        while (this_current && other_current) {
            if (this_current->value != other_current->value) {
                return false; // Mismatched elements
            }
            this_current = this_current->next;
            other_current = other_current->next;
        }

        // Lists are equal if both pointers are null
        return this_current == nullptr && other_current == nullptr;
    }


} // namespace CustomCXX
