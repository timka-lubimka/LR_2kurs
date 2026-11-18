#include "complete_tree.h"
#include <iostream>
#include <queue>

void insertInTree(CompleteTree& tree, int value) {
    TreeNode* added = new TreeNode{value};
    if (tree.root == nullptr) {
        tree.root = added;
        tree.size++;
        return;
    }

    std::queue<TreeNode*> nodes;
    nodes.push(tree.root);

    while (!nodes.empty()) {
        TreeNode* node = nodes.front();
        nodes.pop();

        if (node->left == nullptr) {
            node->left = added;
            tree.size++;
            return;
        }
        nodes.push(node->left);

        if (node->right == nullptr) {
            node->right = added;
            tree.size++;
            return;
        }
        nodes.push(node->right);
    }
}

bool findInTree(const CompleteTree& tree, int value) {
    if (tree.root == nullptr) {
        return false;
    }

    std::queue<TreeNode*> nodes;
    nodes.push(tree.root);
    while (!nodes.empty()) {
        TreeNode* node = nodes.front();
        nodes.pop();
        if (node->value == value) {
            return true;
        }
        if (node->left != nullptr) {
            nodes.push(node->left);
        }
        if (node->right != nullptr) {
            nodes.push(node->right);
        }
    }
    return false;
}

bool isCompleteTree(const CompleteTree& tree) {
    if (tree.root == nullptr) {
        return false;
    }

    std::queue<TreeNode*> nodes;
    nodes.push(tree.root);
    bool foundEmptyPlace = false;

    while (!nodes.empty()) {
        TreeNode* node = nodes.front();
        nodes.pop();

        if (node->left != nullptr) {
            if (foundEmptyPlace) {
                return false;
            }
            nodes.push(node->left);
        } else {
            foundEmptyPlace = true;
        }

        if (node->right != nullptr) {
            if (foundEmptyPlace) {
                return false;
            }
            nodes.push(node->right);
        } else {
            foundEmptyPlace = true;
        }
    }
    return true;
}

void printTree(const CompleteTree& tree) {
    if (tree.root == nullptr) {
        std::cout << "(empty)\n";
        return;
    }

    std::queue<TreeNode*> nodes;
    nodes.push(tree.root);
    while (!nodes.empty()) {
        int count = static_cast<int>(nodes.size());
        while (count > 0) {
            TreeNode* node = nodes.front();
            nodes.pop();
            std::cout << node->value << ' ';
            if (node->left != nullptr) {
                nodes.push(node->left);
            }
            if (node->right != nullptr) {
                nodes.push(node->right);
            }
            count--;
        }
        std::cout << '\n';
    }
}
