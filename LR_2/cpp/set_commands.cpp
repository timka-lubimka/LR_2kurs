#include "set_commands.h"
#include "hash_table.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
void set_commands(const std::string &file, const std::string &query, std::ostream &output) {
    HashTable set;
    std::ifstream input(file);
    if (input) {
        std::string value;
        while (input >> value) {
            set.add(value);
        }
    } else {
        std::ofstream create(file);
        if (!create) {
            throw std::runtime_error("Cannot create data file");
        }
    }
    std::istringstream command(query);
    std::string operation, key, extra;
    command >> operation >> key;
    if (key.empty() || (command >> extra)) {
        throw std::runtime_error("Query: SETADD/SETDEL/SET_AT value");
    }
    if (operation == "SETADD") {
        output << (set.add(key) ? "ADDED" : "EXISTS") << '\n';
    } else if (operation == "SETDEL") {
        output << (set.remove(key) ? "DELETED" : "NOT FOUND") << '\n';
    } else if (operation == "SET_AT") {
        output << (set.contains(key) ? "YES" : "NO") << '\n';
        return;
    } else {
        throw std::runtime_error("Unknown set operation");
    }
    std::ofstream save(file, std::ios::trunc);
    if (!save) {
        throw std::runtime_error("Cannot save file");
    }
    // Deterministic file order.
    std::vector<std::string> items;
    for (auto &slot : set.slots) {
        if (slot.used) {
            items.push_back(slot.key);
        }
    }
    std::sort(items.begin(), items.end());
    for (auto &slot : items) {
        save << slot << '\n';
    }
}
