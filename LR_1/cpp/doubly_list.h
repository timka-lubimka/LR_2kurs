#pragma once
#include <string>

struct DoubleNode {
    std::string value;
    DoubleNode* prev = nullptr;
    DoubleNode* next = nullptr;
};

struct DoubleList {
    DoubleNode* head = nullptr;
    DoubleNode* tail = nullptr;
    int size = 0;
};

void addDoubleListEnd(DoubleList& list, std::string value);
void addDoubleListStart(DoubleList& list, std::string value);
bool findInDoubleList(const DoubleList& list, std::string value);
bool insertAfterDoubleList(DoubleList& list, std::string target, std::string value);
bool insertBeforeDoubleList(DoubleList& list, std::string target, std::string value);
void removeDoubleListNode(DoubleList& list, DoubleNode* node);
bool deleteFromDoubleList(DoubleList& list, std::string value);
bool deleteDoubleListHead(DoubleList& list);
bool deleteDoubleListTail(DoubleList& list);
bool deleteAfterDoubleList(DoubleList& list, std::string value);
bool deleteBeforeDoubleList(DoubleList& list, std::string value);
void printDoubleList(const DoubleList& list, bool reverse = false);