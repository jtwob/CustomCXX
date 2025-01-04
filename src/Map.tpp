#include "../include/Map.h"

namespace CustomCXX {

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