#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include "Day01.h"
#include <algorithm>
#include <cmath>
#include "../common.h"
#include "../colors.h"

void Day01::load() {
    std::ifstream file("./Inputs/Day01.txt");
    std::string str;
	col1.clear();
	col2.clear();
    while (std::getline(file, str)) {
        auto parts = split(str, ' ');
        col1.push_back(std::stoi(parts[0]));
        col2.push_back(std::stoi(parts[3]));
    }
}

void Day01::part1() {
    load();
    std::sort(col1.begin(), col1.end());
    std::sort(col2.begin(), col2.end());

    int sum = 0;
    for (int i = 0; i < col1.size(); i++) {
        sum += abs(col1[i] - col2[i]);
    }
    std::cout << BOLDGREEN << "DAY 1 PART 1: " << RESET << sum << std::endl;
}

void Day01::part2() {
    load();
    int similarity = 0;
    for (int val : col1) {
        similarity += val * (int)std::count(col2.begin(), col2.end(), val);
    }
    std::cout << BOLDGREEN << "DAY 1 PART 2: " << RESET << similarity << std::endl;
}
