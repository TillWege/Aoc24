#include <fstream>
#include <string>
#include "Day02.h"
#include "algorithm"
#include "../common.h"
#include <iostream>
#include "../colors.h"

class Day02Impl {
public:
    std::vector<std::vector<int>> data;

    void loadData() {
        std::ifstream file("./Inputs/Day02.txt");
        std::string str;

        while (std::getline(file, str)) {
            auto parts = split(str, ' ');
            std::vector<int> row;
            for (const auto& item : parts)
                if(!item.empty()) {
                    row.push_back(std::stoi(item));
                }
            data.push_back(row);
        }
    }

    bool isSafeWithRemoving(const std::vector<int>& line) {
        bool foundSafe = false;

        for(int i = 0; i < line.size(); i++) {
            std::vector<int> test = line;
            test.erase(test.begin() + i);
            foundSafe |= isSafe(test);
        }

        return foundSafe;
    }

    bool isSafe(std::vector<int> line) {
        bool didIncrease = false;
        bool didDecrease = false;

        for (int i = 0; i < line.size() - 1; i++) {
            int diff = line[i] - line[i + 1];

            if (diff < 0){
                didDecrease = true;
            } else if(diff > 0){
                didIncrease = true;
            } else {
                return false;
            }

            if(abs(diff) > 3)
                return false;
        }

        return !(didIncrease && didDecrease);
    }

    int calculatePart1() {
        std::vector<bool> res(data.size());
        std::transform(data.begin(), data.end(), res.begin(), [this](auto& line) { return isSafe(line); });
        return std::count(res.begin(), res.end(), true);
    }

    int calculatePart2() {
        std::vector<bool> res(data.size());
        std::transform(data.begin(), data.end(), res.begin(), [this](auto& line) { return isSafeWithRemoving(line); });
        return std::count(res.begin(), res.end(), true);
    }
};

void Day02::load() {
    Day02Impl impl;
    impl.loadData();
}

void Day02::part1() {
    Day02Impl impl;
    impl.loadData();
    int result = impl.calculatePart1();
    std::cout << BOLDGREEN << "DAY 2 PART 1: " << RESET << result << " safe lines" << std::endl;
}

void Day02::part2() {
    Day02Impl impl;
    impl.loadData();
    int result = impl.calculatePart2();
    std::cout << BOLDGREEN << "DAY 2 PART 2: " << RESET << result << " safe lines by potentially removing something" << std::endl;
}
