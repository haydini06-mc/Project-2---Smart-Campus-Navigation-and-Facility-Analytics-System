
#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <string>
#include <vector>
#include <cstddef>

class HashTable {
private:
    struct Entry {
        std::string key;
        std::size_t recordIndex;
    };

    static const std::size_t DEFAULT_CAPACITY = 17;
    std::vector<std::vector<Entry>> buckets;
    std::size_t entryCount;
    std::size_t collisionCount;
    std::size_t hashKey(const std::string& key) const;

public:
    explicit HashTable(std::size_t capacity = DEFAULT_CAPACITY);
    bool insert(const std::string& id, std::size_t recordIndex);
    bool find(const std::string& id, std::size_t& recordIndex) const;
    std::size_t capacity() const;
    std::size_t size() const;
    std::size_t collisions() const;
};

#endif
