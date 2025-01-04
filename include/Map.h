#ifndef CUSTOMCXX_MAP_H
#define CUSTOMCXX_MAP_H

#include <vector>
#include <list>
#include <utility> // For std::pair

namespace CustomCXX {

template <typename Key, typename Value>
class Map {
private:
    struct Node {
        Key key;
        Value value;
    };

    std::vector<std::list<Node>> buckets; // Hash table buckets
    size_t bucket_count;                  // Total number of buckets
    size_t size_;                         // Number of key-value pairs

    size_t hash(const Key& key) const;    // Hash function

public:
    Map(size_t bucket_count = 16);        // Constructor with bucket count
    ~Map() = default;

    Value& operator[](const Key& key);    // Access or insert a key
    bool contains(const Key& key) const; // Check if a key exists
    void erase(const Key& key);          // Remove a key-value pair
    size_t size() const;                 // Return number of elements
    bool empty() const;                  // Check if map is empty
};

} // namespace CustomCXX

#include "../src/Map.tpp"

#endif // CUSTOMCXX_MAP_H