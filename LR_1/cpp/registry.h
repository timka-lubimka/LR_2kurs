#pragma once
#include <map>
#include <string>

#include "array.h"
#include "singly_list.h"
#include "stack.h"
#include "queue.h"
#include "doubly_list.h"
#include "complete_tree.h"

extern std::map<std::string, Array> arrays;
extern std::map<std::string, SingleList> singleLists;
extern std::map<std::string, DoubleList> doubleLists;
extern std::map<std::string, Stack> stacks;
extern std::map<std::string, Queue> queues;
extern std::map<std::string, CompleteTree> trees;