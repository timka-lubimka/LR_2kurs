#include "baseball.h"
#include "hash_task.h"
#include "lru_task.h"
#include "right_view.h"
#include "set_commands.h"
#include "set_partition.h"
#include "subsets.h"
#include <iostream>
#include <stdexcept>
#include <string>
int main(int argc, char **argv) {
    try {
        if (argc < 2) {
            std::cerr << "Usage: lr2 baseball..lru_task [--file data --query 'SETADD x']\n";
            return 1;
        }
        std::string task = argv[1];
        if (task == "baseball") {
            baseball(std::cin, std::cout);
        } else if (task == "set_commands") {
            std::string file, query;
            for (int i = 2; i < argc; i++) {
                std::string argument = argv[i];
                if (argument == "--file" && i + 1 < argc) {
                    file = argv[++i];
                } else if (argument == "--query" && i + 1 < argc) {
                    query = argv[++i];
                }
            }
            if (file.empty() || query.empty()) {
                throw std::runtime_error("set_commands needs --file and --query");
            }
            set_commands(file, query, std::cout);
        } else if (task == "set_partition") {
            set_partition(std::cin, std::cout);
        } else if (task == "subsets") {
            subsets(std::cin, std::cout);
        } else if (task == "right_view") {
            right_view(std::cin, std::cout);
        } else if (task == "hash_task") {
            hash_task(std::cin, std::cout);
        } else if (task == "lru_task") {
            lru_task(std::cin, std::cout);
        } else {
            throw std::runtime_error("Unknown task");
        }
    } catch (const std::exception &error) {
        std::cerr << "ERROR: " << error.what() << '\n';
        return 1;
    }
}
