#pragma once
#include "list_node.h"

struct SingleList {
    ListNode* head = nullptr;
    ListNode* tail = nullptr;
    int size = 0;
};

void addSingleListEnd(SingleList& list, std::string value);
void addSingleListStart(SingleList& list, std::string value);
bool findInSingleList(const SingleList& list, std::string value);
bool insertAfterSingleList(SingleList& list, std::string target, std::string value);
bool insertBeforeSingleList(SingleList& list, std::string target, std::string value);
bool deleteFromSingleList(SingleList& list, std::string value);
bool deleteSingleListHead(SingleList& list);
bool deleteSingleListTail(SingleList& list);
bool deleteAfterSingleList(SingleList& list, std::string value);
bool deleteBeforeSingleList(SingleList& list, std::string value);
void printSingleList(const SingleList& list);