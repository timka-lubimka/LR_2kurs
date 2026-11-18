#include "right_view.h"
#include "../LR-1/cpp/complete_tree.h"
#include "../LR-1/cpp/queue.h"
#include <functional>
#include <stdexcept>
#include <string>
#include <vector>
void right_view(std::istream &input, std::ostream &output) {
    // N followed by N BST insertion keys (no balancing). Uses LR1 TreeNode and queue.
    int count;
    if (!(input >> count) || count < 0) {
        throw std::runtime_error("Input: N followed by N BST values");
    }
    TreeNode *root = nullptr;
    for (int i = 0; i < count; i++) {
        int value;
        if (!(input >> value)) {
            throw std::runtime_error("Missing BST element");
        }
        TreeNode **current = &root;
        while (*current) {
            if ((*current)->value == value) {
                break;
            }
            current = value < (*current)->value ? &(*current)->left : &(*current)->right;
        }
        if (!*current) {
            *current = new TreeNode{value};
        }
    }
    Queue queue;
    if (root) {
        addQueueEnd(queue, "0");
    }
    std::vector<TreeNode *> nodes;
    if (root) {
        nodes.push_back(root);
    }
    bool first = true;
    while (queue.size) {
        int levelSize = queue.size;
        int right = 0;
        for (int i = 0; i < levelSize; i++) {
            std::string index;
            removeQueueFront(queue, index);
            TreeNode *node = nodes[std::stoull(index)];
            right = node->value;
            if (node->left) {
                nodes.push_back(node->left);
                addQueueEnd(queue, std::to_string(nodes.size() - 1));
            }
            if (node->right) {
                nodes.push_back(node->right);
                addQueueEnd(queue, std::to_string(nodes.size() - 1));
            }
        }
        output << (first ? "" : " ") << right;
        first = false;
    }
    output << '\n';
    std::function<void(TreeNode *)> clear = [&](TreeNode *current) {
        if (current) {
            clear(current->left);
            clear(current->right);
            delete current;
        }
    };
    clear(root);
}
