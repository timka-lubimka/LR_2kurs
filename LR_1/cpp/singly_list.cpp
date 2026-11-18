#include "singly_list.h"
#include <iostream>

void addSingleListEnd(SingleList& list, std::string value) {
    ListNode* node = new ListNode{value, nullptr};
    if (list.head == nullptr) {
        list.head = node;
    } else {
        list.tail->next = node;
    }
    list.tail = node;
    list.size++;
}

void addSingleListStart(SingleList& list, std::string value) {
    list.head = new ListNode{value, list.head};
    if (list.tail == nullptr) {
        list.tail = list.head;
    }
    list.size++;
}

bool findInSingleList(const SingleList& list, std::string value) {
    for (ListNode* node = list.head; node != nullptr; node = node->next) {
        if (node->value == value) {
            return true;
        }
    }
    return false;
}

bool insertAfterSingleList(SingleList& list, std::string target, std::string value) {
    for (ListNode* node = list.head; node != nullptr; node = node->next) {
        if (node->value == target) {
            ListNode* added = new ListNode{value, node->next};
            node->next = added;
            if (list.tail == node) {
                list.tail = added;
            }
            list.size++;
            return true;
        }
    }
    return false;
}

bool insertBeforeSingleList(SingleList& list, std::string target, std::string value) {
    if (list.head == nullptr) {
        return false;
    }
    if (list.head->value == target) {
        addSingleListStart(list, value);
        return true;
    }

    for (ListNode* node = list.head; node->next != nullptr; node = node->next) {
        if (node->next->value == target) {
            node->next = new ListNode{value, node->next};
            list.size++;
            return true;
        }
    }
    return false;
}

bool deleteFromSingleList(SingleList& list, std::string value) {
    ListNode* node = list.head;
    ListNode* previous = nullptr;

    while (node != nullptr && node->value != value) {
        previous = node;
        node = node->next;
    }
    if (node == nullptr) {
        return false;
    }

    if (previous == nullptr) {
        list.head = node->next;
    } else {
        previous->next = node->next;
    }
    if (list.tail == node) {
        list.tail = previous;
    }

    delete node;
    list.size--;
    return true;
}

bool deleteSingleListHead(SingleList& list) {
    if (list.head == nullptr) {
        return false;
    }

    ListNode* node = list.head;
    list.head = node->next;
    if (list.head == nullptr) {
        list.tail = nullptr;
    }
    delete node;
    list.size--;
    return true;
}

bool deleteSingleListTail(SingleList& list) {
    if (list.tail == nullptr) {
        return false;
    }
    if (list.head == list.tail) {
        delete list.head;
        list.head = nullptr;
        list.tail = nullptr;
        list.size = 0;
        return true;
    }

    ListNode* node = list.head;
    while (node->next != list.tail) {
        node = node->next;
    }
    delete list.tail;
    list.tail = node;
    node->next = nullptr;
    list.size--;
    return true;
}

bool deleteAfterSingleList(SingleList& list, std::string value) {
    for (ListNode* node = list.head; node != nullptr; node = node->next) {
        if (node->value == value && node->next != nullptr) {
            ListNode* removed = node->next;
            node->next = removed->next;
            if (list.tail == removed) {
                list.tail = node;
            }
            delete removed;
            list.size--;
            return true;
        }
    }
    return false;
}

bool deleteBeforeSingleList(SingleList& list, std::string value) {
    if (list.head == nullptr || list.head == list.tail) {
        return false;
    }
    if (list.head->next->value == value) {
        return deleteSingleListHead(list);
    }

    for (ListNode* node = list.head;
         node->next != nullptr && node->next->next != nullptr;
         node = node->next) {
        if (node->next->next->value == value) {
            ListNode* removed = node->next;
            node->next = removed->next;
            delete removed;
            list.size--;
            return true;
        }
    }
    return false;
}

void printSingleList(const SingleList& list) {
    for (ListNode* node = list.head; node != nullptr; node = node->next) {
        std::cout << node->value << ' ';
    }
    std::cout << '\n';
}
