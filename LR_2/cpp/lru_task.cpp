#include "lru_task.h"
#include "../LR-1/cpp/doubly_list.h"
#include <stdexcept>
#include <string>
#include <unordered_map>
struct CacheEntry {
    std::string value;
    DoubleNode *node;
};

void lru_task(std::istream &input, std::ostream &output) {
    int capacity, commandCount;
    if (!(input >> capacity >> commandCount) || capacity < 0 || commandCount < 0) {
        throw std::runtime_error("Input: capacity Q followed by SET key value or GET key");
    }
    DoubleList order;
    std::unordered_map<std::string, CacheEntry> items;
    auto touch = [&](DoubleNode *node) {
        if (node == order.tail) {
            return;
        }
        if (node->prev) {
            node->prev->next = node->next;
        } else {
            order.head = node->next;
        }
        if (node->next) {
            node->next->prev = node->prev;
        }
        node->prev = order.tail;
        node->next = nullptr;
        if (order.tail) {
            order.tail->next = node;
        }
        order.tail = node;
        if (!order.head) {
            order.head = node;
        }
    };
    for (int i = 0; i < commandCount; i++) {
        std::string operation, key, value;
        if (!(input >> operation >> key)) {
            throw std::runtime_error("Missing command");
        }
        if (operation == "GET") {
            auto item = items.find(key);
            if (item == items.end()) {
                output << "-1\n";
            } else {
                touch(item->second.node);
                output << item->second.value << '\n';
            }
        } else if (operation == "SET") {
            if (!(input >> value)) {
                throw std::runtime_error("SET expects value");
            }
            if (!capacity) {
                continue;
            }
            auto item = items.find(key);
            if (item != items.end()) {
                item->second.value = value;
                touch(item->second.node);
                continue;
            }
            if ((int)items.size() == capacity) {
                auto *head = order.head;
                items.erase(head->value);
                removeDoubleListNode(order, head);
            }
            addDoubleListEnd(order, key);
            items[key] = {value, order.tail};
        } else {
            throw std::runtime_error("Unknown cache operation");
        }
    }
    while (order.head) {
        removeDoubleListNode(order, order.head);
    }
}
