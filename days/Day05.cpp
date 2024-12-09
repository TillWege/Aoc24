//
// Created by tillw on 09/12/2024.
//

#include <fstream>
#include <string>
#include <iostream>
#include "Day05.h"
#include "../common.h"
#include "../colors.h"

struct UpdateRule {
	int r1, r2;
};

typedef std::vector<int> Update;

std::vector<UpdateRule> rules;
std::vector<Update> updates;

bool isUpdateOrderedCorrectly(Update update){

	bool isCorrect = true;
	for(int i = 0; i<update.size(); i++)
	{
		for(int j = i + 1; j<update.size(); j++)
		{
			int n1 = update[i];
			int n2 = update[j];

			for (const auto& rule : rules)
			{
				if((rule.r1 == n2 && rule.r2 == n1)) {
					isCorrect = false;
				}
			}

		}
	}

	return isCorrect;
}

enum state {
	ruleState,
	updateState,
};

void d5p1()
{
	std::ifstream file("./Inputs/Day05.txt");
	std::string str;

	state state = ruleState;

	while (std::getline(file, str))
	{
		if(state == ruleState)
		{
			if(str.empty())
			{
				state = updateState;
				continue;
			}

			auto parts = split(str, '|');
			int r1, r2;

			r1 = std::stoi(parts[0]);
			r2 = std::stoi(parts[1]);

			UpdateRule r = {
				r1,r2
			};

			rules.push_back(r);
		} else {
			Update u;
			auto parts = split(str, ',');

			for (const auto& item : parts)
			{
				u.push_back(std::stoi(item));
			}

			updates.push_back(u);

		}

	}
	printf("Got %zu rules\n", rules.size());
	printf("Got %zu updates\n", updates.size());

	int sum = 0;
	for (const auto& item : updates){

		if(isUpdateOrderedCorrectly(item))
		{
			auto len = item.size();
			auto mid = item[len / 2];
			sum += mid;
		}
	}

	std::cout << "Sum of correctly ordered Updates: " << BOLDGREEN << sum << RESET << std::endl;
}

Update getFixedUpdate(Update update)
{
	for(int i = 0; i<update.size(); i++)
	{
		for(int j = i + 1; j<update.size(); j++)
		{
			int n1 = update[i];
			int n2 = update[j];

			for (const auto& rule : rules)
			{
				if((rule.r1 == n2 && rule.r2 == n1)) {
					std::swap(update[i], update[j]);
					return update;
				}
			}

		}
	}
	return update;
}

void d5p2()
{
	std::ifstream file("./Inputs/Day05.txt");
	std::string str;

	state state = ruleState;

	rules.clear();
	updates.clear();

	while (std::getline(file, str))
	{
		if(state == ruleState)
		{
			if(str.empty())
			{
				state = updateState;
				continue;
			}

			auto parts = split(str, '|');
			int r1, r2;

			r1 = std::stoi(parts[0]);
			r2 = std::stoi(parts[1]);

			UpdateRule r = {
				r1,r2
			};

			rules.push_back(r);
		} else {
			Update u;
			auto parts = split(str, ',');

			for (const auto& item : parts)
			{
				u.push_back(std::stoi(item));
			}

			updates.push_back(u);

		}

	}

	int sum = 0;
	for (const auto& item : updates){

		if(!isUpdateOrderedCorrectly(item))
		{
			Update fixedUpdate = item;
			while(!isUpdateOrderedCorrectly(fixedUpdate))
			{
				fixedUpdate = getFixedUpdate(fixedUpdate);
			}

			auto len = fixedUpdate.size();
			auto mid = fixedUpdate[len / 2];
			sum += mid;
		}
	}

	std::cout << "Sum of fixed incorrectly ordered Updates: " << BOLDGREEN << sum << RESET << std::endl;
}