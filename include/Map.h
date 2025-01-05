#ifndef CUSTOMCXX_MAP_H
#define CUSTOMCXX_MAP_H

#include <vector>
#include <list>
#include <utility> // For std::pair
#include <cstddef>
#include <stdexcept>

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

    static constexpr double LOAD_FACTOR_THRESHOLD = 0.75; // Load factor threshold for rehashing

public:
    Map(size_t bucket_count = 16);        // Constructor with bucket count
    ~Map() = default;

    Value& operator[](const Key& key);    // Access or insert a key
    bool contains(const Key& key) const; // Check if a key exists
    void erase(const Key& key);          // Remove a key-value pair
    size_t size() const;                 // Return number of elements
    bool empty() const;                  // Check if map is empty
    
    void rehash(size_t new_bucket_count);// Rehash to a new bucket count
    void insert_or_assign(const Key& key, const Value& value);// Insert or update a key-value pair
};

} // namespace CustomCXX

#include "../src/Map.tpp"

#endif // CUSTOMCXX_MAP_H