#include "commands.h"

#include <iostream>
#include <string>

enum class Argument {
    File,
    Query,
    Unknown
};

Argument findArgument(const std::string& text) {
    if (text == "--file") {
        return Argument::File;
    }
    if (text == "--query") {
        return Argument::Query;
    }
    return Argument::Unknown;
}

int main(int argc, char** argv) {
    std::string file;
    std::string query;

    for (int i = 1; i < argc; i++) {
        Argument argument = findArgument(argv[i]);
        if (i + 1 >= argc) {
            usage();
            return 1;
        }

        switch (argument) {
            case Argument::File:
                file = argv[++i];
                break;
            case Argument::Query:
                query = argv[++i];
                break;
            case Argument::Unknown:
                usage();
                return 1;
        }
    }

    if (file.empty() || query.empty()) {
        usage();
        return 1;
    }

    return runQuery(file, query);
}
