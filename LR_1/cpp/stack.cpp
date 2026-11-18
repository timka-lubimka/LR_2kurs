#include "stack.h"
#include <iostream>

void pushStack(Stack& stack, std::string value) {
    stack.top = new ListNode{value, stack.top};
    stack.size++;
}

bool popStack(Stack& stack, std::string& value) {
    if (stack.top == nullptr) {
        return false;
    }

    ListNode* node = stack.top;
    value = node->value;
    stack.top = node->next;
    delete node;
    stack.size--;
    return true;
}

bool getStackTop(const Stack& stack, std::string& value) {
    if (stack.top == nullptr) {
        return false;
    }
    value = stack.top->value;
    return true;
}

void printStack(const Stack& stack) {
    for (ListNode* node = stack.top; node != nullptr; node = node->next) {
        std::cout << node->value << ' ';
    }
    std::cout << '\n';
}
