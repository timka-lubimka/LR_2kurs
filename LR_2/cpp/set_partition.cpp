#include "set_partition.h"
#include "../LR-1/cpp/array.h"
#include "hash_table.h"
#include <algorithm>
#include <functional>
#include <numeric>
#include <stdexcept>
#include <vector>
void set_partition(std::istream &input, std::ostream &output) {
    int count;
    long long target;
    if (!(input >> count >> target) || count < 0 || target <= 0) {
        throw std::runtime_error("Input: N target followed by N distinct natural numbers");
    }
    HashTable set;
    Array values;
    std::vector<long long> numbers;
    for (int i = 0; i < count; i++) {
        long long value;
        if (!(input >> value) || value <= 0) {
            throw std::runtime_error("Invalid element");
        }
        if (!set.add(std::to_string(value))) {
            throw std::runtime_error("Not a set: duplicate element");
        }
        addArrayEnd(values, std::to_string(value));
        numbers.push_back(value);
    }
    long long sum = std::accumulate(numbers.begin(), numbers.end(), 0LL);
    if (count == 0 || sum % target || *std::max_element(numbers.begin(), numbers.end()) > target) {
        output << "Impossible\n";
        delete[] values.data;
        return;
    }
    std::sort(numbers.rbegin(), numbers.rend());
    int groupCount = (int)(sum / target);
    if (groupCount > count) {
        output << "Impossible\n";
        delete[] values.data;
        return;
    }
    std::vector<long long> groupSums(groupCount, 0);
    std::vector<std::vector<long long>> groups(groupCount);
    std::function<bool(int)> findPartition = [&](int i) {
        if (i == count) {
            return std::all_of(groupSums.begin(), groupSums.end(),
                               [&](long long value) { return value == target; });
        }
        for (int j = 0; j < groupCount; j++) {
            if (groupSums[j] + numbers[i] > target) {
                continue;
            }
            bool alreadyTried = false;
            for (int h = 0; h < j; h++) {
                if (groupSums[h] == groupSums[j]) {
                    alreadyTried = true;
                    break;
                }
            }
            if (alreadyTried) {
                continue;
            }
            groupSums[j] += numbers[i];
            groups[j].push_back(numbers[i]);
            if (findPartition(i + 1)) {
                return true;
            }
            groups[j].pop_back();
            groupSums[j] -= numbers[i];
            if (groupSums[j] == 0) {
                break;
            }
        }
        return false;
    };
    if (!findPartition(0)) {
        output << "Impossible\n";
    } else {
        for (auto &group : groups) {
            output << '{';
            for (size_t i = 0; i < group.size(); i++) {
                output << (i ? " " : "") << group[i];
            }
            output << "}\n";
        }
    }
    delete[] values.data;
}
