//
// Created by tillw on 05/12/2024.
//

#include <fstream>
#include <string>
#include "Day02.h"
#include "algorithm"
#include "../common.h"

bool isSafeWithRemoving(const std::vector<int>& line)
{
	bool foundSafe = false;

	for(int i = 0; i < line.size(); i++)
	{
		std::vector<int> test = line;
		test.erase(test.begin() + i);
		foundSafe |= isSafe(test);
	}

	return foundSafe;
}

bool isSafe(std::vector<int> line){
	bool didIncrease = false;
	bool didDecrease = false;

	for (int i = 0; i < line.size() - 1; i++)
	{
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

void d2p1()
{
	std::ifstream file("./Inputs/Day02.txt");
	std::string str;

	std::vector<std::vector<int>> data;

	while (std::getline(file, str))
	{
		auto parts = split(str, ' ');
		std::vector<int> row;
		for (const auto& item : parts)
			if(!item.empty()) {
				row.push_back(std::stoi(item));
			}
		data.push_back(row);
	}

	std::vector<bool> res(data.size());
	std::transform(data.begin(), data.end(), res.begin(), isSafe);

	auto trueCount = std::count(res.begin(), res.end(), true);

	printf("Found %zu safe lines \n", trueCount);
}

void d2p2()
{
	std::ifstream file("./Inputs/Day02.txt");
	std::string str;

	std::vector<std::vector<int>> data;

	while (std::getline(file, str))
	{
		auto parts = split(str, ' ');
		std::vector<int> row;
		for (const auto& item : parts)
			if(!item.empty()) {
				row.push_back(std::stoi(item));
			}
		data.push_back(row);
	}

	std::vector<bool> res(data.size());
	std::transform(data.begin(), data.end(), res.begin(), isSafeWithRemoving);

	auto trueCount = std::count(res.begin(), res.end(), true);

	printf("Found %zu safe lines by potentially removing something\n", trueCount);
}