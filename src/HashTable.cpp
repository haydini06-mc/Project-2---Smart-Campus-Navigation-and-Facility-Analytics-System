
#include "HashTable.h"
#include "Utils.h"

HashTable::HashTable(std::size_t capacity)
    : buckets(capacity == 0 ? 1 : capacity), entryCount(0), collisionCount(0) {}

std::size_t HashTable::hashKey(const std::string& key) const {
    std::size_t hash = 0;
    for (unsigned char c : key) {
        hash = (hash * 31 + c) % buckets.size();
    }
    return hash;
}

bool HashTable::insert(const std::string& id, std::size_t recordIndex) {
    std::string key = normalizeId(id);
    if (!isValidFacilityId(key)) return false;
    std::size_t index = hashKey(key);
    for (const Entry& entry : buckets[index]) {
        if (entry.key == key) return false;
    }
    if (!buckets[index].empty()) ++collisionCount;
    buckets[index].push_back({key, recordIndex});
    ++entryCount;
    return true;
}

bool HashTable::find(const std::string& id, std::size_t& recordIndex) const {
    std::string key = normalizeId(id);
    if (!isValidFacilityId(key)) return false;
    std::size_t index = hashKey(key);
    for (const Entry& entry : buckets[index]) {
        if (entry.key == key) {
            recordIndex = entry.recordIndex;
            return true;
        }
    }
    return false;
}

std::size_t HashTable::capacity() const { return buckets.size(); }
std::size_t HashTable::size() const { return entryCount; }
std::size_t HashTable::collisions() const { return collisionCount; }
