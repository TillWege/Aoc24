#include <fstream>
#include <iostream>
#include <vector>
#include "../common.h"
#include "../colors.h"
#include "Day06.h"

enum Tile
{
	EMPTY,
	WALL,
	GUARD,
	VISITED,
	ERROR,
};

Tile getTile(char c)
{
	if (c == '.')
		return EMPTY;
	else if (c == '#')
		return WALL;
	else if (c == '^')
		return GUARD;
	else
		return ERROR;
}

typedef std::vector<std::vector<Tile>> Map;

enum dir
{
	TOP,
	RIGHT,
	BOTTOM,
	LEFT,
};

Vec2 getMovement(dir dir)
{
	switch (dir)
	{
	case TOP:
		return { 0, -1 };
	case RIGHT:
		return { 1, 0 };
	case BOTTOM:
		return { 0, 1 };
	case LEFT:
		return { -1, 0 };
	}
}

dir nextDir(dir direction)
{
	switch (direction)
	{
	case TOP:
		return RIGHT;
	case RIGHT:
		return BOTTOM;
	case BOTTOM:
		return LEFT;
	case LEFT:
		return TOP;
	}
}

void printMap(const Map& map)
{
	for (const auto& line : map)
	{
		for (const auto& tile : line)
		{
			if (tile == WALL)
			{
				std::cout << BOLDRED << "#" << RESET;
			}
			else if (tile == GUARD)
			{
				std::cout << BOLDRED << "^" << RESET;
			}
			else if (tile == VISITED)
			{
				std::cout << BOLDGREEN << "." << RESET;
			}
			else
			{
				std::cout << BOLDBLUE << "." << RESET;
			}
		}
		std::cout << std::endl;
	}
}

void Day06::load() {
    // Load any necessary data here
}

void Day06::part1()
{
	std::ifstream file("./Inputs/Day06e.txt");
	std::string str;

	Map mapData;
	dir currentDir = TOP;

	int idy = 0;
	Vec2 pos = { 0, 0 };
	while (std::getline(file, str))
	{
		std::vector<Tile> line;
		for (int i = 0; i < str.length(); i++)
		{
			Tile nt = getTile(str[i]);
			line.push_back(nt);

			if (nt == GUARD)
			{
				pos.x = i;
				pos.y = idy;
			}
		}
		mapData.push_back(line);
		idy++;
	}

	auto maxWidth = mapData[0].size();
	auto maxHeight = mapData.size();

	std::cout << "Found " << BOLDRED << "PLAYER " << RESET << "at " << pos << std::endl;
	std::cout << "Map is " << BOLDGREEN << maxWidth << ":" << maxWidth << RESET << std::endl;
	printMap(mapData);

	while (true)
	{
		Vec2 nextPos = pos + getMovement(currentDir);

		if (nextPos.x < 0 || nextPos.y < 0 || nextPos.x >= maxWidth || nextPos.y >= maxHeight)
		{
			mapData[pos.y][pos.x] = VISITED;
			break;
		}

		if (mapData[nextPos.y][nextPos.x] == WALL)
		{
			currentDir = nextDir(currentDir);
		}
		else if (mapData[nextPos.y][nextPos.x] == EMPTY || mapData[nextPos.y][nextPos.x] == VISITED)
		{
			mapData[pos.y][pos.x] = VISITED;
			pos = nextPos;
		}
	}

	int visited = 0;
	for (const auto& line : mapData)
	{
		for (const auto& tile : line)
		{
			if (tile == VISITED)
			{
				visited++;
			}
		}
	}
	printMap(mapData);
	std::cout << "Visited " << visited << " tiles" << std::endl;
}

bool isLooping(Map map, Vec2 startPos, dir dir)
{
	const int MAX_STEPS = 10000;
	Vec2 pos = startPos;
	int steps = 0;
	auto maxWidth = map[0].size();
	auto maxHeight = map.size();

	while (steps < MAX_STEPS)
	{
		Vec2 nextPos = pos + getMovement(dir);

		if (nextPos.x < 0 || nextPos.y < 0 || nextPos.x >= maxWidth || nextPos.y >= maxHeight)
		{
			map[pos.y][pos.x] = VISITED;
			return false;
		}

		if (map[nextPos.y][nextPos.x] == WALL)
		{
			dir = nextDir(dir);
		}
		else
		{
			map[pos.y][pos.x] = VISITED;

			pos = nextPos;
		}

		steps++;
	}
	return true;
}

void Day06::part2()
{
	std::ifstream file("./Inputs/Day06.txt");
	std::string str;

	Map mapData;

	int idy = 0;
	Vec2 pos = { 0, 0 };
	while (std::getline(file, str))
	{
		std::vector<Tile> line;
		for (int i = 0; i < str.length(); i++)
		{
			Tile nt = getTile(str[i]);
			line.push_back(nt);

			if (nt == GUARD)
			{
				pos.x = i;
				pos.y = idy;
			}
		}
		mapData.push_back(line);
		idy++;
	}

	int loopCount = 0;
	for (int i = 0; i < mapData.size(); i++)
	{
		for (int j = 0; j < mapData[i].size(); j++)
		{
			auto newMap = mapData;
			auto playerPos = pos;
			if(newMap[i][j] == EMPTY)
			{
				newMap[i][j] = WALL;
				bool didLoop = isLooping(newMap, playerPos, TOP);
				if (didLoop)
				{
					loopCount++;
				}
			}
		}
	}

	printf("Found %s %d loops %s\n", BOLDGREEN, loopCount, RESET);
}
