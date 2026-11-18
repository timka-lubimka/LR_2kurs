#pragma once
#include <algorithm>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>
struct HashTable {
    struct Slot {
        std::string key;
        bool used = false, deleted = false;
    };
    std::vector<Slot> slots;

    size_t count = 0, probes = 0, collisions = 0;

    bool doubleHash;

    explicit HashTable(bool useDoubleHash = false, size_t capacity = 17)
        : slots(capacity), doubleHash(useDoubleHash) {
    }

    static uint64_t hash(const std::string &key) {
        uint64_t hashValue = 14695981039346656037ULL;
        for (unsigned char c : key) {
            hashValue ^= c;
            hashValue *= 1099511628211ULL;
        }
        return hashValue;
    }

    size_t step(const std::string &key) const {
        return doubleHash ? 1 + (hash("secondary:" + key) % (slots.size() - 1)) : 1;
    }

    size_t locate(const std::string &key, bool &found) {
        size_t hashValue = hash(key) % slots.size(), probeStep = step(key),
               firstDeletedIndex = slots.size();
        for (size_t i = 0; i < slots.size(); ++i) {
            size_t index = (hashValue + i * probeStep) % slots.size();
            ++probes;
            if (slots[index].used) {
                if (slots[index].key == key) {
                    found = true;
                    return index;
                }
                ++collisions;
            } else if (slots[index].deleted) {
                if (firstDeletedIndex == slots.size()) {
                    firstDeletedIndex = index;
                }
            } else {
                found = false;
                return firstDeletedIndex == slots.size() ? index : firstDeletedIndex;
            }
        }
        found = false;
        return firstDeletedIndex;
    }

    static bool prime(size_t count) {
        if (count < 2) {
            return false;
        }
        for (size_t divisor = 2; divisor <= count / divisor; ++divisor) {
            if (count % divisor == 0) {
                return false;
            }
        }
        return true;
    }

    void rehash() {
        auto old = std::move(slots);
        size_t capacity = old.size() * 2 + 1;
        while (!prime(capacity)) {
            ++capacity;
        }
        slots = std::vector<Slot>(capacity);
        count = 0;
        for (auto &slot : old) {
            if (slot.used) {
                add(slot.key);
            }
        }
    }

    bool add(const std::string &key) {
        if ((count + 1) * 10 >= slots.size() * 7) {
            rehash();
        }
        bool found = false;
        size_t index = locate(key, found);
        if (found) {
            return false;
        }
        if (index == slots.size()) {
            rehash();
            return add(key);
        }
        slots[index] = {key, true, false};
        ++count;
        return true;
    }

    bool contains(const std::string &key) {
        bool found = false;
        locate(key, found);
        return found;
    }

    bool remove(const std::string &key) {
        bool found = false;
        size_t index = locate(key, found);
        if (!found) {
            return false;
        }
        slots[index].used = false;
        slots[index].deleted = true;
        --count;
        return true;
    }
};
