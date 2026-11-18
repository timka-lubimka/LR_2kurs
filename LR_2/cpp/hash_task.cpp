#include "hash_task.h"
#include "hash_table.h"
#include <chrono>
#include <stdexcept>
#include <string>
#include <vector>
static long long fold(const std::string &key) {
    if (key.empty() || key.find_first_not_of("0123456789") != std::string::npos) {
        throw std::runtime_error("Fold key must consist of decimal digits");
    }
    long long result = 0;
    for (size_t i = 0; i < key.size(); i += 3) {
        result += std::stoll(key.substr(i, 3));
    }
    return result;
}
void hash_task(std::istream &input, std::ostream &output) {
    std::string key;
    if (!(input >> key)) {
        throw std::runtime_error("Input: decimal key [N more keys]");
    }
    auto foldedKey = fold(key);
    output << "Fold: ";
    for (size_t i = 0; i < key.size(); i += 3) {
        output << (i ? "+" : "") << key.substr(i, 3);
    }
    output << " = " << foldedKey << '\n';
    std::vector<std::string> keys{std::to_string(foldedKey)};
    int count = 0;
    if (input >> count) {
        if (count < 0) {
            throw std::runtime_error("N must be nonnegative");
        }
        for (int i = 0; i < count; i++) {
            std::string key;
            if (!(input >> key)) {
                throw std::runtime_error("Missing key");
            }
            keys.push_back(std::to_string(fold(key)));
        }
    }
    for (bool useDoubleHash : {false, true}) {
        HashTable table(useDoubleHash);
        auto start = std::chrono::steady_clock::now();
        for (auto &key : keys) {
            table.add(key);
        }
        for (auto &key : keys) {
            if (!table.contains(key)) {
                throw std::runtime_error("Hash table lookup failed");
            }
        }
        auto elapsedMicroseconds = std::chrono::duration_cast<std::chrono::microseconds>(
                                       std::chrono::steady_clock::now() - start)
                                       .count();
        output << (useDoubleHash ? "Double hashing" : "Linear probing") << ": count=" << table.count
               << " collisions=" << table.collisions << " probes=" << table.probes
               << " time_us=" << elapsedMicroseconds << '\n';
    }
}
