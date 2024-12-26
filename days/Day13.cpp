//
// Created by tillw on 26/12/2024.
//

#include "Day13.h"
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include "../common.h"
#include "../colors.h"

const std::string EXAMPLE = "Button A: X+94, Y+34\n"
							"Button B: X+22, Y+67\n"
							"Prize: X=8400, Y=5400\n"
							"\n"
							"Button A: X+26, Y+66\n"
							"Button B: X+67, Y+21\n"
							"Prize: X=12748, Y=12176\n"
							"\n"
							"Button A: X+17, Y+86\n"
							"Button B: X+84, Y+37\n"
							"Prize: X=7870, Y=6450\n"
							"\n"
							"Button A: X+69, Y+23\n"
							"Button B: X+27, Y+71\n"
							"Prize: X=18641, Y=10279";

void Day13::load()
{
	std::cout << "Loading Input" << std::endl;
	std::ifstream file("./Inputs/Day13.txt");
	std::string input((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	auto lines = split(input, '\n');
	for(int i = 0; i < lines.size(); i += 4)
	{
		std::string buttonALine = lines[i].substr(10);
		std::string buttonBLine = lines[i + 1].substr(10);
		std::string prizeLine = lines[i + 2].substr(7);

		Vec2 buttonA = Vec2{0,0};
		Vec2 buttonB = Vec2{0,0};
		Vec2 prize = Vec2{0,0};

		auto parts = split(buttonALine, ',');
		buttonA.x = std::stoi(parts[0].substr(2));
		buttonA.y = std::stoi(parts[1].substr(2));

		parts = split(buttonBLine, ',');
		buttonB.x = std::stoi(parts[0].substr(2));
		buttonB.y = std::stoi(parts[1].substr(2));

		parts = split(prizeLine, ', ');
		prize.x = std::stoi(parts[0].substr(2));
		prize.y = std::stoi(parts[1].substr(2));

		clawmachines.push_back(Clawmachine{
			buttonA,
			buttonB,
			prize
		});
	}

	std::cout << "Loaded " << BOLDGREEN << clawmachines.size() << " clawmachines" << RESET<< std::endl;
}

std::optional<int> Day13::Clawmachine::getLowestTickets()
{
	const int MAX_TRIES = 500;

	std::vector<Vec2> hits;

	for(int i = 0; i < MAX_TRIES; i++)
	{
		for(int j = MAX_TRIES - 1; j >= 0; j--)
		{
			Vec2 pair = Vec2{i,j};

			Vec2 pos = (this->ButtonA * i) + (this->ButtonB * j);
			if(pos == this->Prize)
			{
				hits.push_back(pair);
				break;
			}
		}
	}

	if(hits.empty())
		return std::nullopt;

	int lowestTickets = MAX_TRIES * 2;

	for(const auto& hit : hits)
	{
		int tickets = (hit.x * 3) + hit.y;
		if(tickets < lowestTickets)
			lowestTickets = tickets;
	}

	return lowestTickets;
}

void Day13::part1()
{
	load();

	unsigned long long ticketSum = 0;
	unsigned long long prizeCount = 0;

	for(Clawmachine clawmachine : clawmachines)
	{
		auto lowestTickets = clawmachine.getLowestTickets();
		if(lowestTickets)
		{
			ticketSum += *lowestTickets;
			prizeCount++;
		}
	}

	printf("Prize sum: %s%llu%s\n", BOLDGREEN, prizeCount, RESET);
	printf("Number of tickets spend: %s%llu%s\n", BOLDGREEN, ticketSum, RESET);
}

void Day13::part2()
{
	return;

	// TODO:
	// Implement Vec2 as a generic type
	// Fix this for very large numbers

	unsigned long long ticketSum = 0;
	unsigned long long prizeCount = 0;

	for(Clawmachine clawmachine : clawmachines)
	{
		clawmachine.Prize.x += 10000000000000;
		clawmachine.Prize.y += 10000000000000;
		auto lowestTickets = clawmachine.getLowestTickets();
		if(lowestTickets)
		{
			ticketSum += *lowestTickets;
			prizeCount++;
		}
	}

	printf("Prize sum: %s%llu%s\n", BOLDGREEN, prizeCount, RESET);
	printf("Number of tickets spend: %s%llu%s\n", BOLDGREEN, ticketSum, RESET);
}