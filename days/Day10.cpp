//
// Created by tillw on 23/12/2024.
//

#include "Day10.h"
#include "../common.h"
#include "../colors.h"

#include <string>
#include <fstream>

enum Direction
{
	UP,
	RIGHT,
	DOWN,
	LEFT,
};

const Direction DIRECTIONS[] = {
		UP,
		RIGHT,
		DOWN,
		LEFT,
};

Vec2 getMovement(Direction dir)
{
	switch (dir)
	{
	case UP:
		return { 0, -1 };
	case DOWN:
		return { 0, 1 };
	case LEFT:
		return { -1, 0 };
	case RIGHT:
		return { 1, 0 };

	}
}

typedef std::vector<std::vector<int>> Map;

bool isMoveAllowed(const Map& map, Vec2 pos, Direction dir)
{
	int diff = 0;
	Vec2 newPos = pos + getMovement(dir);

	if (newPos.x < 0 || newPos.y < 0 || newPos.x >= map.size() || newPos.y >= map[0].size())
	{
		return false;
	}
	diff = map[newPos.y][newPos.x] - map[pos.y][pos.x];

	return diff == 1;
}

int getTrailHeadSum(const Map& map, Vec2 startPos, bool filterDupes = true)
{
	std::vector<Vec2> TilesToVisit;
	std::vector<Vec2> PeaksFound;

	TilesToVisit.push_back(startPos);

	int sum = 0;

	while (!TilesToVisit.empty())
	{
		Vec2 pos = TilesToVisit.back();
		TilesToVisit.pop_back();

		for (int i = 0; i < 4; ++i)
		{
			Direction dir = DIRECTIONS[i];
			if (isMoveAllowed(map, pos, dir))
			{
				Vec2 newPos = pos + getMovement(dir);
				if(map[newPos.y][newPos.x] == 9)
				{
					if(filterDupes)
					{
						bool newPeak = true;

						for(const auto& peak : PeaksFound)
						{
							if(peak == newPos)
							{
								newPeak = false;
								break;
							}
						}

						if(newPeak)
						{
							sum++;
							PeaksFound.push_back(newPos);
						}
					} else {
						sum++;
						PeaksFound.push_back(newPos);
					}
				}else{
					TilesToVisit.push_back(newPos);
				}
			}
		}
	}
	return sum;
}

void d10p1()
{
	std::ifstream file("./Inputs/Day10.txt");
	std::string input((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	auto lines = split(input, '\n');

	Map mapData;
	std::vector<Vec2> possibleStarts;

	for (int y = 0; y < lines.size(); ++y)
	{
		std::vector<int> line;
		for (int x = 0; x < lines[y].size(); ++x)
		{
			int num = lines[y][x] - '0';
			if (num == 0)
				possibleStarts.emplace_back(x, y);

			line.push_back(num);
		}
		mapData.push_back(line);
	}

	printf("Found %zu possible starts\n", possibleStarts.size());

	int trailHeadSum = 0;

	for(const auto& start : possibleStarts)
	{
		trailHeadSum += getTrailHeadSum(mapData, start);
	}

	printf("Sum of Trailheads: %d\n", trailHeadSum);

}

void d10p2()
{
	std::ifstream file("./Inputs/Day10.txt");
	std::string input((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	auto lines = split(input, '\n');

	Map mapData;
	std::vector<Vec2> possibleStarts;

	for (int y = 0; y < lines.size(); ++y)
	{
		std::vector<int> line;
		for (int x = 0; x < lines[y].size(); ++x)
		{
			int num = lines[y][x] - '0';
			if (num == 0)
				possibleStarts.emplace_back(x, y);

			line.push_back(num);
		}
		mapData.push_back(line);
	}

	printf("Found %zu possible starts\n", possibleStarts.size());

	int trailHeadSum = 0;

	for(const auto& start : possibleStarts)
	{
		trailHeadSum += getTrailHeadSum(mapData, start, false);
	}

	printf("Sum of unique Trailheads: %d\n", trailHeadSum);
}