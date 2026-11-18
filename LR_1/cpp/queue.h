#pragma once
#include "list_node.h"

struct Queue {
    ListNode* front = nullptr;
    ListNode* back = nullptr;
    int size = 0;
};

void addQueueEnd(Queue& queue, std::string value);
bool removeQueueFront(Queue& queue, std::string& value);
bool getQueueFront(const Queue& queue, std::string& value);
void printQueue(const Queue& queue);