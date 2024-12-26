#include <string>
#include <fstream>
#include <sstream>
#include <regex>
#include <iostream>
#include "Day03.h"
#include "../common.h"
#include "../colors.h"

class Day03Impl {
public:
    std::vector<std::string> extractMulMatches(const std::string& text) {
        std::regex pattern(R"(mul\(\d+,\d+\))");
        std::vector<std::string> matches;
        std::string::const_iterator searchStart(text.cbegin());
        std::smatch match;

        while (std::regex_search(searchStart, text.cend(), match, pattern)) {
            matches.push_back(match.str());
            searchStart = match.suffix().first;
        }

        return matches;
    }

    int calcMulOp(const std::string& instruction) {
        auto content = instruction.substr(4, instruction.length() - 5);
        auto parts = split(content, ',');
        int lhs = stoi(parts[0]);
        int rhs = stoi(parts[1]);
        return lhs * rhs;
    }

    std::vector<std::string> extractMulDoDontMatches(const std::string& text) {
        std::regex pattern(R"((mul\(\d+,\d+\)|do\(\)|don't\(\)))");
        std::vector<std::string> matches;
        std::string::const_iterator searchStart(text.cbegin());
        std::smatch match;

        while (std::regex_search(searchStart, text.cend(), match, pattern)) {
            matches.push_back(match.str());
            searchStart = match.suffix().first;
        }

        return matches;
    }

    std::string loadInput() {
        std::ifstream file("./Inputs/Day03.txt");
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }
};

void Day03::load() {
    Day03Impl impl;
    impl.loadInput();
}

void Day03::part1() {
    Day03Impl impl;
    auto input = impl.loadInput();
    auto calcs = impl.extractMulMatches(input);

    int sum = 0;
    for (const auto& item : calcs)
        sum += impl.calcMulOp(item);

    std::cout << "Calculation Result: " << BOLDGREEN << sum << RESET << std::endl;
}

void Day03::part2() {
    Day03Impl impl;
    auto input = impl.loadInput();
    auto instructions = impl.extractMulDoDontMatches(input);

    int sum = 0;
    bool isActive = true;

    for (const auto& item : instructions) {
        if(item == "do()") {
            isActive = true;
        } else if (item == "don't()") {
            isActive = false;
        } else {
            if(isActive)
                sum += impl.calcMulOp(item);
        }
    }

    std::cout << "Calculation Result with activations: " << BOLDGREEN << sum << RESET << std::endl;
}
