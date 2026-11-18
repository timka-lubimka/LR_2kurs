#include "commands.h"
#include "storage.h"
#include "registry.h"

#include <iostream>
#include <map>
#include <sstream>
#include <vector>

enum class Command {
    MPUSH, MINSERT, MGET, MDEL, MSET, MLEN, MPRINT,
    FPUSH, FHEAD, FBEFORE, FAFTER, FDEL,
    FDELHEAD, FDELTAIL, FDELBEFORE, FDELAFTER,
    FMEMBER, FGET, FPRINT,
    LPUSH, LHEAD, LBEFORE, LAFTER, LDEL,
    LDELHEAD, LDELTAIL, LDELBEFORE, LDELAFTER,
    LMEMBER, LGET, LPRINT, LREVERSE,
    SPUSH, SPOP, SGET, SPRINT,
    QPUSH, QPOP, QGET, QPRINT,
    TINSERT, TGET, ISMEMBER, TCHECK, TPRINT,
    PRINT, Unknown
};

// Перевод текстовой команды в значение enum.
Command findCommand(const std::string& text) {
    static const std::map<std::string, Command> commands = {
        {"MPUSH", Command::MPUSH},
        {"MINSERT", Command::MINSERT},
        {"MGET", Command::MGET},
        {"MDEL", Command::MDEL},
        {"MSET", Command::MSET},
        {"MLEN", Command::MLEN},
        {"MPRINT", Command::MPRINT},

        {"FPUSH", Command::FPUSH},
        {"FHEAD", Command::FHEAD},
        {"FBEFORE", Command::FBEFORE},
        {"FAFTER", Command::FAFTER},
        {"FDEL", Command::FDEL},
        {"FDELHEAD", Command::FDELHEAD},
        {"FDELTAIL", Command::FDELTAIL},
        {"FDELBEFORE", Command::FDELBEFORE},
        {"FDELAFTER", Command::FDELAFTER},
        {"FMEMBER", Command::FMEMBER},
        {"FGET", Command::FGET},
        {"FPRINT", Command::FPRINT},

        {"LPUSH", Command::LPUSH},
        {"LHEAD", Command::LHEAD},
        {"LBEFORE", Command::LBEFORE},
        {"LAFTER", Command::LAFTER},
        {"LDEL", Command::LDEL},
        {"LDELHEAD", Command::LDELHEAD},
        {"LDELTAIL", Command::LDELTAIL},
        {"LDELBEFORE", Command::LDELBEFORE},
        {"LDELAFTER", Command::LDELAFTER},
        {"LMEMBER", Command::LMEMBER},
        {"LGET", Command::LGET},
        {"LPRINT", Command::LPRINT},
        {"LREVERSE", Command::LREVERSE},

        {"SPUSH", Command::SPUSH},
        {"SPOP", Command::SPOP},
        {"SGET", Command::SGET},
        {"SPRINT", Command::SPRINT},

        {"QPUSH", Command::QPUSH},
        {"QPOP", Command::QPOP},
        {"QGET", Command::QGET},
        {"QPRINT", Command::QPRINT},

        {"TINSERT", Command::TINSERT},
        {"TGET", Command::TGET},
        {"ISMEMBER", Command::ISMEMBER},
        {"TCHECK", Command::TCHECK},
        {"TPRINT", Command::TPRINT},

        {"PRINT", Command::PRINT}
    };

    auto found = commands.find(text);

    if (found == commands.end()) {
        return Command::Unknown;
    }

    return found->second;
}

// Для общей команды PRINT определяем тип структуры.
Command findPrintCommand(const std::string& name) {
    if (arrays.count(name)) return Command::MPRINT;
    if (singleLists.count(name)) return Command::FPRINT;
    if (doubleLists.count(name)) return Command::LPRINT;
    if (stacks.count(name)) return Command::SPRINT;
    if (queues.count(name)) return Command::QPRINT;
    if (trees.count(name)) return Command::TPRINT;

    return Command::Unknown;
}

bool readNumber(const std::vector<std::string>& words, int place, int& value) {
    if (place >= static_cast<int>(words.size())) {
        return false;
    }

    try {
        std::size_t used = 0;
        value = std::stoi(words[place], &used);
        return used == words[place].size();
    } catch (...) {
        return false;
    }
}

bool readText(const std::vector<std::string>& words,
              int place, std::string& value) {
    if (place >= static_cast<int>(words.size())) {
        return false;
    }

    value = words[place];
    return true;
}

void usage() {
    std::cout << "NE TO CHTO-TO NAPISAL\n";
}

int runQuery(const std::string& file, const std::string& query) {
    loadDataFromFile(file);

    std::istringstream input(query);
    std::vector<std::string> words;
    std::string word;

    while (input >> word) {
        words.push_back(word);
    }

    if (words.size() < 2) {
        usage();
        freeMemory();
        return 1;
    }

    std::string name = words[1];
    int first = 0;
    std::string second;
    std::string result;
    std::string text;

    bool changed = false;
    bool ok = true;

    Command command = findCommand(words[0]);

    if (command == Command::PRINT) {
        command = findPrintCommand(name);

        if (command == Command::Unknown) {
            ok = false;
        }
    }

    switch (command) {
        // Массив
        case Command::MPUSH: {
            if (!readText(words, 2, text)) {
                usage();
                ok = false;
                break;
            }

            addArrayEnd(arrays[name], text);
            changed = true;
            break;
        }

        case Command::MINSERT: {
            if (!readNumber(words, 2, first) ||
                !readText(words, 3, second)) {
                usage();
                ok = false;
                break;
            }

            ok = insertArrayAt(arrays[name], first, second);
            changed = ok;
            break;
        }

        case Command::MGET: {
            if (!readNumber(words, 2, first)) {
                usage();
                ok = false;
                break;
            }

            ok = getArrayAt(arrays[name], first, result);

            if (ok) {
                std::cout << result << '\n';
            }
            break;
        }

        case Command::MDEL: {
            if (!readNumber(words, 2, first)) {
                usage();
                ok = false;
                break;
            }

            ok = deleteArrayAt(arrays[name], first);
            changed = ok;
            break;
        }

        case Command::MSET: {
            if (!readNumber(words, 2, first) ||
                !readText(words, 3, second)) {
                usage();
                ok = false;
                break;
            }

            ok = replaceArrayAt(arrays[name], first, second);
            changed = ok;
            break;
        }

        case Command::MLEN:
            std::cout << arrays[name].size << '\n';
            break;

        case Command::MPRINT:
            printArray(arrays[name]);
            break;

        // Односвязный список
        case Command::FPUSH: {
            if (!readText(words, 2, text)) {
                usage();
                ok = false;
                break;
            }

            addSingleListEnd(singleLists[name], text);
            changed = true;
            break;
        }

        case Command::FHEAD: {
            if (!readText(words, 2, text)) {
                usage();
                ok = false;
                break;
            }

            addSingleListStart(singleLists[name], text);
            changed = true;
            break;
        }

        case Command::FBEFORE: {
            if (!readText(words, 2, text) ||
                !readText(words, 3, second)) {
                usage();
                ok = false;
                break;
            }

            ok = insertBeforeSingleList(singleLists[name], text, second);
            changed = ok;
            break;
        }

        case Command::FAFTER: {
            if (!readText(words, 2, text) ||
                !readText(words, 3, second)) {
                usage();
                ok = false;
                break;
            }

            ok = insertAfterSingleList(singleLists[name], text, second);
            changed = ok;
            break;
        }

        case Command::FDEL: {
            if (!readText(words, 2, text)) {
                usage();
                ok = false;
                break;
            }

            ok = deleteFromSingleList(singleLists[name], text);
            changed = ok;
            break;
        }

        case Command::FDELHEAD:
            ok = deleteSingleListHead(singleLists[name]);
            changed = ok;
            break;

        case Command::FDELTAIL:
            ok = deleteSingleListTail(singleLists[name]);
            changed = ok;
            break;

        case Command::FDELBEFORE: {
            if (!readText(words, 2, text)) {
                usage();
                ok = false;
                break;
            }

            ok = deleteBeforeSingleList(singleLists[name], text);
            changed = ok;
            break;
        }

        case Command::FDELAFTER: {
            if (!readText(words, 2, text)) {
                usage();
                ok = false;
                break;
            }

            ok = deleteAfterSingleList(singleLists[name], text);
            changed = ok;
            break;
        }

        case Command::FMEMBER: {
            if (!readText(words, 2, text)) {
                usage();
                ok = false;
                break;
            }

            bool found = findInSingleList(singleLists[name], text);
            std::cout << (found ? "TRUE" : "FALSE") << '\n';
            break;
        }

        case Command::FGET: {
            if (!readNumber(words, 2, first)) {
                usage();
                ok = false;
                break;
            }

            ListNode* node = singleLists[name].head;

            for (int i = 0; node != nullptr && i < first; i++) {
                node = node->next;
            }

            if (first < 0 || node == nullptr) {
                ok = false;
            } else {
                std::cout << node->value << '\n';
            }
            break;
        }

        case Command::FPRINT:
            printSingleList(singleLists[name]);
            break;

        // Двусвязный список
        case Command::LPUSH: {
            if (!readText(words, 2, text)) {
                usage();
                ok = false;
                break;
            }

            addDoubleListEnd(doubleLists[name], text);
            changed = true;
            break;
        }

        case Command::LHEAD: {
            if (!readText(words, 2, text)) {
                usage();
                ok = false;
                break;
            }

            addDoubleListStart(doubleLists[name], text);
            changed = true;
            break;
        }

        case Command::LBEFORE: {
            if (!readText(words, 2, text) ||
                !readText(words, 3, second)) {
                usage();
                ok = false;
                break;
            }

            ok = insertBeforeDoubleList(doubleLists[name], text, second);
            changed = ok;
            break;
        }

        case Command::LAFTER: {
            if (!readText(words, 2, text) ||
                !readText(words, 3, second)) {
                usage();
                ok = false;
                break;
            }

            ok = insertAfterDoubleList(doubleLists[name], text, second);
            changed = ok;
            break;
        }

        case Command::LDEL: {
            if (!readText(words, 2, text)) {
                usage();
                ok = false;
                break;
            }

            ok = deleteFromDoubleList(doubleLists[name], text);
            changed = ok;
            break;
        }

        case Command::LDELHEAD:
            ok = deleteDoubleListHead(doubleLists[name]);
            changed = ok;
            break;

        case Command::LDELTAIL:
            ok = deleteDoubleListTail(doubleLists[name]);
            changed = ok;
            break;

        case Command::LDELBEFORE: {
            if (!readText(words, 2, text)) {
                usage();
                ok = false;
                break;
            }

            ok = deleteBeforeDoubleList(doubleLists[name], text);
            changed = ok;
            break;
        }

        case Command::LDELAFTER: {
            if (!readText(words, 2, text)) {
                usage();
                ok = false;
                break;
            }

            ok = deleteAfterDoubleList(doubleLists[name], text);
            changed = ok;
            break;
        }

        case Command::LMEMBER: {
            if (!readText(words, 2, text)) {
                usage();
                ok = false;
                break;
            }

            bool found = findInDoubleList(doubleLists[name], text);
            std::cout << (found ? "TRUE" : "FALSE") << '\n';
            break;
        }

        case Command::LGET: {
            if (!readNumber(words, 2, first)) {
                usage();
                ok = false;
                break;
            }

            DoubleNode* node = doubleLists[name].head;

            for (int i = 0; node != nullptr && i < first; i++) {
                node = node->next;
            }

            if (first < 0 || node == nullptr) {
                ok = false;
            } else {
                std::cout << node->value << '\n';
            }
            break;
        }

        case Command::LPRINT:
            printDoubleList(doubleLists[name]);
            break;

        case Command::LREVERSE:
            printDoubleList(doubleLists[name], true);
            break;

        // Стек
        case Command::SPUSH: {
            if (!readText(words, 2, text)) {
                usage();
                ok = false;
                break;
            }

            pushStack(stacks[name], text);
            changed = true;
            break;
        }

        case Command::SPOP:
            ok = popStack(stacks[name], result);

            if (ok) {
                std::cout << result << '\n';
            }

            changed = ok;
            break;

        case Command::SGET:
            ok = getStackTop(stacks[name], result);

            if (ok) {
                std::cout << result << '\n';
            }
            break;

        case Command::SPRINT:
            printStack(stacks[name]);
            break;

        // Очередь
        case Command::QPUSH: {
            if (!readText(words, 2, text)) {
                usage();
                ok = false;
                break;
            }

            addQueueEnd(queues[name], text);
            changed = true;
            break;
        }

        case Command::QPOP:
            ok = removeQueueFront(queues[name], result);

            if (ok) {
                std::cout << result << '\n';
            }

            changed = ok;
            break;

        case Command::QGET:
            ok = getQueueFront(queues[name], result);

            if (ok) {
                std::cout << result << '\n';
            }
            break;

        case Command::QPRINT:
            printQueue(queues[name]);
            break;

        // Дерево
        case Command::TINSERT: {
            if (!readNumber(words, 2, first)) {
                usage();
                ok = false;
                break;
            }

            insertInTree(trees[name], first);
            changed = true;
            break;
        }

        case Command::TGET:
        case Command::ISMEMBER: {
            if (!readNumber(words, 2, first)) {
                usage();
                ok = false;
                break;
            }

            bool found = findInTree(trees[name], first);
            std::cout << (found ? "TRUE" : "FALSE") << '\n';
            break;
        }

        case Command::TCHECK:
            std::cout << (isCompleteTree(trees[name])
                          ? "TRUE" : "FALSE") << '\n';
            break;

        case Command::TPRINT:
            printTree(trees[name]);
            break;

        default:
            if (ok) {
                usage();
            }

            ok = false;
            break;
    }

    if (!ok) {
        std::cout
            << "ERROR: invalid command, missing value, or element not found\n";
    }

    if (changed) {
        saveDataToFile(file);
    }

    freeMemory();
    return ok ? 0 : 2;
}