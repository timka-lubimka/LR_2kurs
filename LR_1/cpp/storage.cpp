#include "storage.h"
#include "registry.h"

#include <fstream>
#include <queue>
#include <sstream>
#include <vector>

void loadDataFromFile(const std::string& file) {
    std::ifstream input(file);
    std::string line;

    while (std::getline(input, line)) {
        std::istringstream row(line);
        char type;
        std::string name;
        std::string value;

        if (!(row >> type >> name)) {
            continue;
        }

        std::vector<std::string> values;
        while (row >> value) {
            values.push_back(value);
        }

        if (type == 'M') arrays[name];
        else if (type == 'F') singleLists[name];
        else if (type == 'L') doubleLists[name];
        else if (type == 'S') stacks[name];
        else if (type == 'Q') queues[name];
        else if (type == 'T') trees[name];
        else continue;

        for (const std::string& item : values) {
            if (type == 'M') addArrayEnd(arrays[name], item);
            else if (type == 'F') addSingleListEnd(singleLists[name], item);
            else if (type == 'L') addDoubleListEnd(doubleLists[name], item);
            else if (type == 'S') pushStack(stacks[name], item);
            else if (type == 'Q') addQueueEnd(queues[name], item);
            else if (type == 'T') {
                std::istringstream number(item);
                int treeValue;
                if (number >> treeValue && number.eof()) {
                    insertInTree(trees[name], treeValue);
                }
            }
        }
    }
}

void saveDataToFile(const std::string& file) {
    std::ofstream output(file);

    for (auto& entry : arrays) {
        output << "M " << entry.first;
        for (int i = 0; i < entry.second.size; i++) {
            output << ' ' << entry.second.data[i];
        }
        output << '\n';
    }

    for (auto& entry : singleLists) {
        output << "F " << entry.first;
        for (ListNode* node = entry.second.head; node != nullptr; node = node->next) {
            output << ' ' << node->value;
        }
        output << '\n';
    }

    for (auto& entry : doubleLists) {
        output << "L " << entry.first;
        for (DoubleNode* node = entry.second.head; node != nullptr; node = node->next) {
            output << ' ' << node->value;
        }
        output << '\n';
    }

    for (auto& entry : stacks) {
        output << "S " << entry.first;
        std::vector<std::string> values;
        for (ListNode* node = entry.second.top; node != nullptr; node = node->next) {
            values.push_back(node->value);
        }
        for (int i = static_cast<int>(values.size()) - 1; i >= 0; i--) {
            output << ' ' << values[i];
        }
        output << '\n';
    }

    for (auto& entry : queues) {
        output << "Q " << entry.first;
        for (ListNode* node = entry.second.front; node != nullptr; node = node->next) {
            output << ' ' << node->value;
        }
        output << '\n';
    }

    for (auto& entry : trees) {
        output << "T " << entry.first;
        if (entry.second.root != nullptr) {
            std::queue<TreeNode*> nodes;
            nodes.push(entry.second.root);
            while (!nodes.empty()) {
                TreeNode* node = nodes.front();
                nodes.pop();
                output << ' ' << node->value;
                if (node->left != nullptr) nodes.push(node->left);
                if (node->right != nullptr) nodes.push(node->right);
            }
        }
        output << '\n';
    }
}

void clearTree(TreeNode* node) {
    if (node == nullptr) {
        return;
    }
    clearTree(node->left);
    clearTree(node->right);
    delete node;
}

void freeMemory() {
    for (auto& entry : arrays) {
        delete[] entry.second.data;
    }
    for (auto& entry : singleLists) {
        while (entry.second.head != nullptr) {
            ListNode* node = entry.second.head;
            entry.second.head = node->next;
            delete node;
        }
    }
    for (auto& entry : doubleLists) {
        while (entry.second.head != nullptr) {
            DoubleNode* node = entry.second.head;
            entry.second.head = node->next;
            delete node;
        }
    }
    for (auto& entry : stacks) {
        while (entry.second.top != nullptr) {
            ListNode* node = entry.second.top;
            entry.second.top = node->next;
            delete node;
        }
    }
    for (auto& entry : queues) {
        while (entry.second.front != nullptr) {
            ListNode* node = entry.second.front;
            entry.second.front = node->next;
            delete node;
        }
    }
    for (auto& entry : trees) {
        clearTree(entry.second.root);
    }
}
