//
// Created by tillw on 05/12/2024.
//

#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include "../common.h"
#include "Day01.h"
#include <algorithm>
#include <cmath>
#include "../colors.h"

void d1p1() {
	std::string input;

	std::vector<int> col1, col2;

	std::ifstream file("./Inputs/Day01.txt");
	std::string str;
	while (std::getline(file, str))
	{
		auto parts = split(str, ' ');
		col1.push_back(std::stoi(parts[0]));
		col2.push_back(std::stoi(parts[3]));
	}

	std::sort(col1.begin(), col1.end());
	std::sort(col2.begin(), col2.end());

	int sum = 0;

	for(int i = 0; i<col1.size(); i++)
	{
		sum += abs(col1[i] - col2[i]);
	}
	std::cout << BOLDGREEN << "DAY 1 PART 1: " << RESET  << sum << std::endl;
}

void d1p2() {
	std::string input;

	std::vector<int> col1, col2;

	std::ifstream file("./Inputs/Day01.txt");
	std::string str;
	while (std::getline(file, str))
	{
		auto parts = split(str, ' ');
		col1.push_back(std::stoi(parts[0]));
		col2.push_back(std::stoi(parts[3]));
	}

	int similarity = 0;

	for(int val : col1)
	{
			similarity += val * (int)std::count(col2.begin(), col2.end(), val);
	}


	std::cout << BOLDGREEN << "DAY 1 PART 2: " << RESET  << similarity << std::endl;
}