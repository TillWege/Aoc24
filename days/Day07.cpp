//
// Created by tillw on 22/12/2024.
//

#include <fstream>
#include <string>
#include <vector>
#include "Day07.h"
#include "../common.h"
#include "../colors.h"

enum Operation
{
	ADD,
	MUL,
	CONCAT
};

std::vector<std::vector<Operation>> generateOperatorCombinationsAddMul(int length) {
	std::vector<std::vector<Operation>> combinations;
	int numCombinations = std::pow(2, length);

	for (int i = 0; i < numCombinations; ++i) {
		std::vector<Operation> currentCombination;
		for (int j = length - 1; j >= 0; --j) {
			if ((i >> j) & 1) {
				currentCombination.push_back(MUL);
			} else {
				currentCombination.push_back(ADD);
			}
		}
		combinations.push_back(currentCombination);
	}
	return combinations;
}

std::vector<std::vector<Operation>> generateOperatorCombinationsAll(int length) {
	std::vector<std::vector<Operation>> combinations;
	int numCombinations = std::pow(3, length);

	for (int i = 0; i < numCombinations; ++i) {
		std::vector<Operation> currentCombination;
		int temp = i;
		for (int j = 0; j < length; ++j) {
			int remainder = temp % 3;
			temp /= 3;
			if (remainder == 0) {
				currentCombination.push_back(ADD);
			} else if (remainder == 1) {
				currentCombination.push_back(MUL);
			} else if (remainder == 2) {
				currentCombination.push_back(CONCAT);
			}
		}
		std::reverse(currentCombination.begin(), currentCombination.end());
		combinations.push_back(currentCombination);
	}
	return combinations;
}

struct Equation
{
	int64_t Result;
	std::vector<int> Inputs;
};

int64_t doOperation(int64_t a, int64_t b, Operation op)
{
	if (op == ADD)
	{
		return a + b;
	}
	else if (op == MUL)
	{
		return a * b;
	} else if (op == CONCAT)
	{
		std::string strConCat = std::to_string(a) + std::to_string(b);
		return std::stoull(strConCat);
	}
	return 0;
}


bool isCorrectP1(const Equation& eq)
{
	int ops = eq.Inputs.size() - 1;

	auto operationLists = generateOperatorCombinationsAddMul(ops);

	for (const auto& opList : operationLists)
	{
		int64_t sum = 0;
		for(int i = 0; i<opList.size(); i++)
		{
			if(i==0) {
				sum = doOperation(eq.Inputs[0], eq.Inputs[1], opList[i]);
			} else {
				sum =doOperation(sum, eq.Inputs[i+1], opList[i]);
			}
		}

		if(sum == eq.Result)
		{
			return true;

		}
	}


	return false;
}

bool isCorrectP2(const Equation& eq)
{
	int ops = eq.Inputs.size() - 1;

	auto operationLists = generateOperatorCombinationsAll(ops);

	for (const auto& opList : operationLists)
	{
		int64_t sum = 0;
		for(int i = 0; i<opList.size(); i++)
		{
			if(i==0) {
				sum = doOperation(eq.Inputs[0], eq.Inputs[1], opList[i]);
			} else {
				sum = doOperation(sum, eq.Inputs[i+1], opList[i]);
			}
		}

		if(sum == eq.Result)
		{
			return true;

		}
	}


	return false;
}

void d7p1()
{
	std::ifstream file("./Inputs/Day07.txt");
	std::string str;

	std::vector<Equation> equations;
	while (std::getline(file, str))
	{
		auto parts = split(str, ':');
		int64_t result = std::stoull(parts[0]);
		std::vector<int> inputs;
		auto inputParts = split(parts[1], ' ');
		for (const auto& item : inputParts)
		{
			if (item.empty())
			{
				continue;
			}
			inputs.push_back(std::stoi(item));
		}
		Equation eq = {
			result,
			inputs
		};
		equations.push_back(eq);
	}

	printf("Found %zu equations\n", equations.size());
	int64_t sumOfCorrect = 0;
	int correctCount = 0;

	for (const auto& eq : equations)
	{
		if (isCorrectP1(eq))
		{
			sumOfCorrect += eq.Result;
			correctCount++;
		}
	}

	printf("Part 1: Found %s %d correct %s equations totalling %s %lld %s\n", BOLDGREEN, correctCount, RESET, BOLDGREEN, sumOfCorrect, RESET);
}

void d7p2(){
	std::ifstream file("./Inputs/Day07.txt");
	std::string str;

	std::vector<Equation> equations;
	while (std::getline(file, str))
	{
		auto parts = split(str, ':');
		int64_t result = std::stoull(parts[0]);
		std::vector<int> inputs;
		auto inputParts = split(parts[1], ' ');
		for (const auto& item : inputParts)
		{
			if (item.empty())
			{
				continue;
			}
			inputs.push_back(std::stoi(item));
		}
		Equation eq = {
			result,
			inputs
		};
		equations.push_back(eq);
	}

	printf("Found %zu equations\n", equations.size());
	int64_t sumOfCorrect = 0;
	int correctCount = 0;

	for (const auto& eq : equations)
	{
		if (isCorrectP2(eq))
		{
			sumOfCorrect += eq.Result;
			correctCount++;
		}
	}

	printf("Part 2: Found %s %d correct %s equations totalling %s %lld %s\n", BOLDGREEN, correctCount, RESET, BOLDGREEN, sumOfCorrect, RESET);
}