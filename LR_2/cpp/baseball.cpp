#include "baseball.h"
#include "../LR-1/cpp/stack.h"
#include <stdexcept>
#include <string>
void baseball(std::istream &input, std::ostream &output) {
    int count;
    if (!(input >> count) || count < 0) {
        throw std::runtime_error("Expected nonnegative operation count");
    }
    Stack scores;
    long long total = 0;
    for (int i = 0; i < count; ++i) {
        std::string operation;
        if (!(input >> operation)) {
            throw std::runtime_error("Missing operation");
        }
        std::string lastScore, previousScore;
        if (operation == "C") {
            if (!popStack(scores, lastScore)) {
                throw std::runtime_error("C requires score");
            }
            total -= std::stoll(lastScore);
        } else if (operation == "D") {
            if (!getStackTop(scores, lastScore)) {
                throw std::runtime_error("D requires score");
            }
            long long score = 2 * std::stoll(lastScore);
            pushStack(scores, std::to_string(score));
            total += score;
        } else if (operation == "+") {
            if (!popStack(scores, lastScore)) {
                throw std::runtime_error("+ requires two scores");
            }
            if (!getStackTop(scores, previousScore)) {
                pushStack(scores, lastScore);
                throw std::runtime_error("+ requires two scores");
            }
            pushStack(scores, lastScore);
            long long score = std::stoll(lastScore) + std::stoll(previousScore);
            pushStack(scores, std::to_string(score));
            total += score;
        } else {
            size_t parsedLength = 0;
            long long score = std::stoll(operation, &parsedLength);
            if (parsedLength != operation.size() || score <= 0) {
                throw std::runtime_error("Score must be positive integer");
            }
            pushStack(scores, operation);
            total += score;
        }
    }
    output << total << '\n';
    while (scores.size) {
        std::string s;
        popStack(scores, s);
    }
}
