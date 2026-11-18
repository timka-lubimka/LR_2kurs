#include "doubly_list.h"
#include <iostream>

void addDoubleListEnd(DoubleList& list, std::string value) {
    DoubleNode* node = new DoubleNode{value, list.tail, nullptr};
    if (list.tail == nullptr) {
        list.head = node;
    } else {
        list.tail->next = node;
    }
    list.tail = node;
    list.size++;
}

void addDoubleListStart(DoubleList& list, std::string value) {
    DoubleNode* node = new DoubleNode{value, nullptr, list.head};
    if (list.head == nullptr) {
        list.tail = node;
    } else {
        list.head->prev = node;
    }
    list.head = node;
    list.size++;
}

bool findInDoubleList(const DoubleList& list, std::string value) {
    for (DoubleNode* node = list.head; node != nullptr; node = node->next) {
        if (node->value == value) {
            return true;
        }
    }
    return false;
}

bool insertAfterDoubleList(DoubleList& list, std::string target, std::string value) {
    for (DoubleNode* node = list.head; node != nullptr; node = node->next) {
        if (node->value == target) {
            DoubleNode* added = new DoubleNode{value, node, node->next};
            if (node->next == nullptr) {
                list.tail = added;
            } else {
                node->next->prev = added;
            }
            node->next = added;
            list.size++;
            return true;
        }
    }
    return false;
}

bool insertBeforeDoubleList(DoubleList& list, std::string target, std::string value) {
    for (DoubleNode* node = list.head; node != nullptr; node = node->next) {
        if (node->value == target) {
            DoubleNode* added = new DoubleNode{value, node->prev, node};
            if (node->prev == nullptr) {
                list.head = added;
            } else {
                node->prev->next = added;
            }
            node->prev = added;
            list.size++;
            return true;
        }
    }
    return false;
}

void removeDoubleListNode(DoubleList& list, DoubleNode* node) {
    if (node->prev == nullptr) {
        list.head = node->next;
    } else {
        node->prev->next = node->next;
    }
    if (node->next == nullptr) {
        list.tail = node->prev;
    } else {
        node->next->prev = node->prev;
    }
    delete node;
    list.size--;
}

bool deleteFromDoubleList(DoubleList& list, std::string value) {
    for (DoubleNode* node = list.head; node != nullptr; node = node->next) {
        if (node->value == value) {
            removeDoubleListNode(list, node);
            return true;
        }
    }
    return false;
}

bool deleteDoubleListHead(DoubleList& list) {
    if (list.head == nullptr) {
        return false;
    }
    removeDoubleListNode(list, list.head);
    return true;
}

bool deleteDoubleListTail(DoubleList& list) {
    if (list.tail == nullptr) {
        return false;
    }
    removeDoubleListNode(list, list.tail);
    return true;
}

bool deleteAfterDoubleList(DoubleList& list, std::string value) {
    for (DoubleNode* node = list.head; node != nullptr; node = node->next) {
        if (node->value == value && node->next != nullptr) {
            removeDoubleListNode(list, node->next);
            return true;
        }
    }
    return false;
}

bool deleteBeforeDoubleList(DoubleList& list, std::string value) {
    for (DoubleNode* node = list.head; node != nullptr; node = node->next) {
        if (node->value == value && node->prev != nullptr) {
            removeDoubleListNode(list, node->prev);
            return true;
        }
    }
    return false;
}

void printDoubleList(const DoubleList& list, bool reverse) {
    if (!reverse) {
        for (DoubleNode* node = list.head; node != nullptr; node = node->next) {
            std::cout << node->value << ' ';
        }
    } else {
        for (DoubleNode* node = list.tail; node != nullptr; node = node->prev) {
            std::cout << node->value << ' ';
        }
    }
    std::cout << '\n';
}
