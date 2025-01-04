#include "../include/Map.h"

namespace CustomCXX {

    // Constructor and Destructor Stub
    template <typename Key, typename Value>
    Map<Key, Value>::Map(size_t bucket_count)
        : buckets(bucket_count), bucket_count(bucket_count), size_(0) {}

    template <typename Key, typename Value>
    bool Map<Key, Value>::contains(const Key& key) const {
        size_t bucket_index = hash(key);
        const auto& bucket = buckets[bucket_index];

        for (const auto& node : bucket) {
            if (node.key == key) {
                return true; // Key found
            }
        }

        return false; // Key not found
    }

    template <typename Key, typename Value>
    void Map<Key, Value>::erase(const Key& key) {
        size_t bucket_index = hash(key);
        auto& bucket = buckets[bucket_index];

        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->key == key) {
                bucket.erase(it); // Remove the node from the bucket
                --size_;          // Decrement size
                return;           // Exit after erasing
            }
        }

        // Key not found
        throw std::out_of_range("Key not found in Map");
    }

    template <typename Key, typename Value>
    size_t Map<Key, Value>::size() const {
        return size_; // Placeholder
    }

    template <typename Key, typename Value>
    bool Map<Key, Value>::empty() const {
        return size_ == 0; // Placeholder
    }


    template <typename Key, typename Value>
    size_t Map<Key, Value>::hash(const Key& key) const {
        return std::hash<Key>{}(key) % bucket_count;
    }

    template <typename Key, typename Value>
    Value& Map<Key, Value>::operator[](const Key& key) {
        size_t bucket_index = hash(key);

        // Search for the key in the bucket
        for (auto& node : buckets[bucket_index]) {
            if (node.key == key) {
                return node.value; // Key exists, return the value
            }
        }

        // Key does not exist, create a new node
        buckets[bucket_index].push_back({key, Value{}});
        ++size_;

        return buckets[bucket_index].back().value; // Return reference to the new value
    }


}