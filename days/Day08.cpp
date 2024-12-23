//
// Created by tillw on 22/12/2024.
//

#include <vector>
#include <fstream>
#include <string>
#include "Day08.h"
#include "../common.h"
#include <variant>
#include <set>
#include <iostream>

typedef std::variant<char, std::monostate> Tile;

struct Antenna
{
	Vec2 pos;
	char frequency;
};

typedef std::vector<std::vector<Tile>> Map;
typedef std::vector<Antenna> AntennaList;

Vec2 getDistance(Vec2 a, Vec2 b)
{
	return {
		a.x - b.x,
		a.y - b.y
	};
}

bool isAntinodeP1(const AntennaList& list, Vec2 pos, char frequency)
{
	for(int y = 0; y < list.size(); y++)
	{
		for(int x = 0; x < list.size(); x++)
		{
			if(x == y)
				continue;

			if(list[x].frequency != frequency)
				continue;

			if(list[y].frequency != frequency)
				continue;

			Antenna a1 = list[x];
			Antenna a2 = list[y];

			Vec2 distance1 = getDistance(pos, a1.pos);
			Vec2 distance2 = getDistance(pos, a2.pos);

			if(((distance1 * 2) == distance2) || (distance1 == (distance2 * 2)))
			{
				return true;
			}
		}
	}


	return false;
}

bool isAntinodeP2(const AntennaList& list, Vec2 pos, char frequency)
{
	for(int y = 0; y < list.size(); y++)
	{
		for(int x = 0; x < list.size(); x++)
		{
			if(x == y)
				continue;

			if(list[x].frequency != frequency)
				continue;

			if(list[y].frequency != frequency)
				continue;

			Antenna a1 = list[x];
			Antenna a2 = list[y];

			Vec2 distance1 = getDistance(pos, a1.pos);
			Vec2 distance2 = getDistance(pos, a2.pos);

			if(distance1 == Vec2{0,0})
				return true;

			if(distance2 == Vec2{0,0})
				return true;

			if(distance1.x == 0 xor distance2.x == 0)
				continue;
			if(distance1.y == 0 xor distance2.y == 0)
				continue;


			float xCoff = (float)distance1.x / (float)distance2.x;
			float yCoff = (float)distance1.y / (float)distance2.y;

		if(xCoff == yCoff)
				return true;
		}
	}


	return false;
}

void d8p1()
{
	std::ifstream file("./Inputs/Day08.txt");
	std::string str;

	Map mapData;


	std::set<char> frequencies;
	AntennaList antennas;

	int idy = 0;
	while (std::getline(file, str))
	{
		std::vector<Tile> line;
		for (int x = 0; x < str.length(); ++x)
		{
			if (str[x] == '.')
			{
				line.emplace_back(std::monostate());
			} else
			{
				line.emplace_back(str[x]);
				frequencies.insert(str[x]);
				antennas.emplace_back(Antenna{{
												  x,
												  idy
				}, str[x]});
			}
		}
		mapData.push_back(line);
		idy++;
	}

	auto maxWidth = mapData[0].size();
	auto maxHeight = mapData.size();

	printf("Found x: %zu y:%zu f: %zu\n", maxWidth, maxHeight, frequencies.size());


	int antiNodes = 0;
	for (int y = 0; y < maxHeight; ++y)
	{
		for (int x = 0; x < maxWidth; ++x)
		{
			for(int k = 0; k < frequencies.size(); k++)
			{
				Vec2 pos = {x,y};
				if(isAntinodeP1(antennas, pos, *std::next(frequencies.begin(), k)))
				{
					antiNodes++;
					mapData[x][y] = '#';
					break;
				}
			}
		}
	}

	printf("Found %d antinodes\n", antiNodes);
}

void d8p2()
{
	std::ifstream file("./Inputs/Day08.txt");
	std::string str;

	Map mapData;


	std::set<char> frequencies;
	AntennaList antennas;

	int idy = 0;
	while (std::getline(file, str))
	{
		std::vector<Tile> line;
		for (int x = 0; x < str.length(); ++x)
		{
			if (str[x] == '.')
			{
				line.emplace_back(std::monostate());
			} else
			{
				line.emplace_back(str[x]);
				frequencies.insert(str[x]);
				antennas.emplace_back(Antenna{{
												  x,
												  idy
											  }, str[x]});
			}
		}
		mapData.push_back(line);
		idy++;
	}

	auto maxWidth = mapData[0].size();
	auto maxHeight = mapData.size();

	printf("Found x: %zu y:%zu f: %zu\n", maxWidth, maxHeight, frequencies.size());


	int antiNodes = 0;
	for (int y = 0; y < maxHeight; ++y)
	{
		for (int x = 0; x < maxWidth; ++x)
		{
			for(int k = 0; k < frequencies.size(); k++)
			{
//				if(x == 10 && y == 2)
//					__debugbreak();
				Vec2 pos = {x,y};
				if(isAntinodeP2(antennas, pos, *std::next(frequencies.begin(), k)))
				{
					antiNodes++;
					mapData[y][x] = '#';
					break;
				}
			}
		}
	}

	for(int y = 0; y < maxHeight; y++)
	{
		for(int x = 0; x < maxWidth; x++)
		{
			if(const auto& get = std::get_if<char>(&mapData[y][x]))
			{
				std::cout << *get;
			} else
			{
				std::cout << ".";
			}
		}
		printf("\n");
	}

	printf("Found %d antinodes\n", antiNodes);
}