#pragma once
#include "list_node.h"

struct Stack {
    ListNode* top = nullptr;
    int size = 0;
};

void pushStack(Stack& stack, std::string value);
bool popStack(Stack& stack, std::string& value);
bool getStackTop(const Stack& stack, std::string& value);
void printStack(const Stack& stack);