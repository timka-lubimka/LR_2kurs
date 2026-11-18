#pragma once

struct TreeNode {
    int value;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
};

struct CompleteTree {
    TreeNode* root = nullptr;
    int size = 0;
};

void insertInTree(CompleteTree& tree, int value);
bool findInTree(const CompleteTree& tree, int value);
bool isCompleteTree(const CompleteTree& tree);
void printTree(const CompleteTree& tree);