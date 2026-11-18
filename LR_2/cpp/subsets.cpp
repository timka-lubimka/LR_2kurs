#include "subsets.h"
#include "../LR-1/cpp/array.h"
#include <set>
#include <stdexcept>
#include <string>
void subsets(std::istream &input, std::ostream &output) {
    int count;
    if (!(input >> count) || count < 0 || count > 20) {
        throw std::runtime_error("Input: N (0..20), followed by N unique values");
    }
    Array values;
    std::set<std::string> unique;
    for (int i = 0; i < count; i++) {
        std::string value;
        if (!(input >> value) || !unique.insert(value).second) {
            throw std::runtime_error("Duplicate or missing value");
        }
        addArrayEnd(values, value);
    }
    for (unsigned long long mask = 0; mask < (1ULL << count); mask++) {
        output << '{';
        bool first = true;
        for (int index = 0; index < count; index++) {
            if (mask & (1ULL << index)) {
                std::string value;
                getArrayAt(values, index, value);
                if (!first) {
                    output << ' ';
                }
                output << value;
                first = false;
            }
        }
        output << "}\n";
    }
    delete[] values.data;
}
