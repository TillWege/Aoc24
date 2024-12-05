//
// Created by tillw on 05/12/2024.
//

#include <string>
#include <fstream>
#include <sstream>
#include <regex>
#include <iostream>
#include "Day03.h"
#include "../common.h"
#include "../colors.h"

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

int calcMulOp(const std::string& instruction)
{
	auto content = instruction.substr(4, instruction.length() - 5);
	auto parts = split(content, ',');
	int lhs = stoi(parts[0]);
	int rhs = stoi(parts[1]);

	return lhs * rhs;
}

void d3p1()
{
	std::ifstream file("./Inputs/Day03.txt");
	std::stringstream buffer;
	buffer << file.rdbuf();
	std::string input = buffer.str();

	auto calcs = extractMulMatches(input);

	int sum = 0;
	for (const auto& item : calcs)
		sum += calcMulOp(item);

	std::cout << "Calculation Result: " << BOLDGREEN << sum << RESET << std::endl;
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

void d3p2()
{
	std::ifstream file("./Inputs/Day03.txt");
	std::stringstream buffer;
	buffer << file.rdbuf();
	std::string input = buffer.str();

	auto instructions = extractMulDoDontMatches(input);

	int sum = 0;
	bool isActive = true;

	for (const auto& item : instructions)
	{
		if(item == "do()")
		{
			isActive = true;
		} else if (item == "don't()")
		{
			isActive = false;
		} else {
			if(isActive)
				sum += calcMulOp(item);
		}
	}

	std::cout << "Calculation Result with activations: " << BOLDGREEN << sum << RESET << std::endl;
}