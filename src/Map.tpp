#include "../include/Map.h"
#include "../include/Vector.h"

namespace CustomCXX {

    /**
     * @brief Constructs a Map with a given bucket count.
     * @param bucket_count Number of buckets for the hash table. Defaults to 16.
     */
    template <typename Key, typename Value>
    Map<Key, Value>::Map(size_t bucket_count)
        : buckets(bucket_count), bucket_count(bucket_count), size_(0) {}

    /**
     * @brief Checks if a given key exists in the Map.
     * @param key The key to search for.
     * @return true if the key exists, false otherwise.
     */
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

    /**
     * @brief Removes a key-value pair from the Map by key.
     * @param key The key to erase.
     * @throws std::out_of_range if the key is not found.
     */
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

    /**
     * @brief Returns the number of key-value pairs in the Map.
     * @return The size of the Map.
     */
    template <typename Key, typename Value>
    size_t Map<Key, Value>::size() const {
        return size_; // Placeholder
    }

    /**
     * @brief Checks if the Map is empty.
     * @return true if the Map contains no elements, false otherwise.
     */
    template <typename Key, typename Value>
    bool Map<Key, Value>::empty() const {
        return size_ == 0; // Placeholder
    }


    /**
     * @brief Computes the hash for a given key.
     * @param key The key to hash.
     * @return The hash value modulo the bucket count.
     */
    template <typename Key, typename Value>
    size_t Map<Key, Value>::hash(const Key& key) const {
        return std::hash<Key>{}(key) % bucket_count;
    }

    /**
     * @brief Accesses or inserts a key-value pair.
     * If the key exists, returns the associated value.
     * If the key does not exist, inserts it with a default-constructed value.
     * @param key The key to access or insert.
     * @return A reference to the value associated with the key.
     */
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

    /**
     * @brief Rehashes the Map to use a new bucket count.
     * This redistributes all existing key-value pairs into new buckets.
     * @param new_bucket_count The new number of buckets.
     */
    template <typename Key, typename Value>
    void Map<Key, Value>::rehash(size_t new_bucket_count) {
        std::vector<std::list<Node>> new_buckets(new_bucket_count);

        for (const auto& bucket : buckets) {
            for (const auto& node : bucket) {
                size_t new_index = std::hash<Key>{}(node.key) % new_bucket_count;
                new_buckets[new_index].push_back(node);
            }
        }

        buckets = std::move(new_buckets);
        bucket_count = new_bucket_count;
    }

    /**
     * @brief Inserts or assigns a value to a key.
     * If the key exists, updates its value. Otherwise, inserts a new key-value pair.
     * @param key The key to insert or assign.
     * @param value The value to associate with the key.
     */
    template <typename Key, typename Value>
    void Map<Key, Value>::insert_or_assign(const Key& key, const Value& value) {
        if (size_ > 0.75 * bucket_count) {
            rehash(bucket_count * 2);
        }

        // Insert or overwrite logic
        size_t index = hash(key);
        auto& bucket = buckets[index];

        for (auto& node : bucket) {
            if (node.key == key) {
                node.value = value; // Overwrite
                return;
            }
        }

        bucket.push_back({key, value});
        ++size_;
    }

    /**
     * @brief Returns all keys in the Map.
     * @return A CustomCXX::Vector containing all keys.
     */
    template <typename Key, typename Value>
    CustomCXX::Vector<Key> Map<Key, Value>::keys() const {
        CustomCXX::Vector<Key> result;

        for (const auto& bucket : buckets) {
            for (const auto& node : bucket) {
                result.push_back(node.key);
            }
        }

        return result;
    }
}