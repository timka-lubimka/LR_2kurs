#include "queue.h"
#include <iostream>

void addQueueEnd(Queue& queue, std::string value) {
    ListNode* node = new ListNode{value, nullptr};

    if (queue.back == nullptr) {
        queue.front = node;
    } else {
        queue.back->next = node;
    }

    queue.back = node;
    queue.size++;
}

bool removeQueueFront(Queue& queue, std::string& value) {
    if (queue.front == nullptr) {
        return false;
    }

    ListNode* node = queue.front;
    value = node->value;
    queue.front = node->next;

    if (queue.front == nullptr) {
        queue.back = nullptr;
    }

    delete node;
    queue.size--;
    return true;
}

bool getQueueFront(const Queue& queue, std::string& value) {
    if (queue.front == nullptr) {
        return false;
    }
    value = queue.front->value;
    return true;
}

void printQueue(const Queue& queue) {
    for (ListNode* node = queue.front; node != nullptr; node = node->next) {
        std::cout << node->value << ' ';
    }
    std::cout << '\n';
}
