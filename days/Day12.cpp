//
// Created by tillw on 26/12/2024.
//

#include <fstream>
#include "Day12.h"
#include "string"
#include "vector"
#include "../common.h"
#include <set>

std::string Example = "RRRRIICCFF\n"
					  "RRRRIICCCF\n"
					  "VVRRRCCFFF\n"
					  "VVRCCCJFFF\n"
					  "VVVVCJJCFE\n"
					  "VVIVCCJJEE\n"
					  "VVIIICJJEE\n"
					  "MIIIIIJJEE\n"
					  "MIIISIJEEE\n"
					  "MMMISSJEEE";

struct Region
{
	std::vector<Vec2> tiles;
	char letter;

	bool contains(Vec2 pos)
	{
		for(const auto& tile : tiles)
		{
			if(tile == pos)
				return true;
		}
		return false;
	}

	bool addTile(Vec2 pos)
	{
		if(contains(pos))
			return false;

		tiles.push_back(pos);
		return true;
	}
};

typedef std::vector<std::vector<char>> Map;
typedef std::vector<Region> Regions;

bool isTileClaimed(const Regions& regions, Vec2 pos)
{
	for(Region region : regions)
	{
		if(region.contains(pos))
			return true;
	}
	return false;
}

void floodFill(const Map& map, Vec2 startPos, Regions& regions)
{
	if (isTileClaimed(regions, startPos))
		return;

	Region region;
	region.letter = map[startPos.y][startPos.x];
	std::vector<Vec2> TilesToVisit;
	std::set<Vec2> TilesChecked;

	TilesToVisit.push_back(startPos);

	while(!TilesToVisit.empty())
	{
		Vec2 pos = TilesToVisit.back();
		TilesToVisit.pop_back();

		if(TilesChecked.contains(pos))
			continue;
		TilesChecked.insert(pos);

		if (!region.addTile(pos))
			continue;

		for(int i = 0; i < 4; i++)
		{
			Direction dir = DIRECTIONS[i];
			Vec2 newPos = pos + getMovement(dir);

			if(newPos.x < 0 || newPos.y < 0 || newPos.x >= map[0].size() || newPos.y >= map.size())
				continue;

			if(map[newPos.y][newPos.x] == map[pos.y][pos.x])
			{
				if(!isTileClaimed(regions, newPos))
				{
					TilesToVisit.push_back(newPos);
				}
			}
		}
	}
	if(!region.tiles.empty())
	{
		regions.push_back(region);
	}
}

int getPerimeterLength(Region region)
{
	int length = 0;

	for (const auto& item : region.tiles)
	{
		for(int i = 0; i < 4; i++)
		{
			Direction dir = DIRECTIONS[i];
			Vec2 pos = item;
			Vec2 newPos = pos + getMovement(dir);
			if(!region.contains(newPos))
			{
				length++;
			}
		}
	}

	return length;
}

void d12p1()
{
	return;
	std::ifstream file("./Inputs/Day12.txt");
	std::string input((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	//input = Example;

	Map map;
	Regions regions;
	auto lines = split(input, '\n');

	for(const auto& line : lines)
	{
		std::vector<char> lineChars;
		for(const auto& c : line)
		{
			lineChars.push_back(c);
		}
		map.push_back(lineChars);
	}

	printf("Map dimensions: %zu x %zu\n", map.size(), map[0].size());

	for(int y = 0; y < map.size(); y++)
	{
		for(int x = 0; x < map[0].size(); x++)
		{
			floodFill(map, {x,y}, regions);
		}
	}

	printf("Found %zu regions\n", regions.size());
	int totalPrice = 0;
	for(const auto& region : regions)
	{
		printf("Region: %c Perimeter length: %d area: %llu\n", region.letter, getPerimeterLength(region), region.tiles.size());
		totalPrice += getPerimeterLength(region) * region.tiles.size();
	}

	printf("Total price: %d\n", totalPrice);
}

int getSides(Region region, const Map& map)
{
	int width = map[0].size();
	int height = map.size();


	bool debug = region.letter == 'C';

	Vec2 MostTopLeft = Vec2{height - 1,width - 1};
	Vec2 MostBottomRight = Vec2{0,0};

	for(const auto& tile : region.tiles)
	{
		if(tile.x < MostTopLeft.x)
			MostTopLeft.x = tile.x;

		if(tile.y < MostTopLeft.y)
			MostTopLeft.y = tile.y;

		if(tile.x > MostBottomRight.x)
			MostBottomRight.x = tile.x;

		if(tile.y > MostBottomRight.y)
			MostBottomRight.y = tile.y;
	}

	int lCount = 0;
	int rCount = 0;
	int tCount = 0;
	int bCount = 0;


	// Scan top to bottom
	for(int y = MostTopLeft.y; y <= MostBottomRight.y; y++)
	{
		int lineWidth = MostBottomRight.x - MostTopLeft.x + 1;
		std::vector<bool> topBorder = std::vector<bool>(lineWidth);
		std::vector<bool> bottomBorder = std::vector<bool>(lineWidth);
		for(int x = MostTopLeft.x; x <= MostBottomRight.x; x++)
		{

			if(region.contains({x,y}))
			{
				Vec2 pos = {x,y};

				Vec2 topPos = pos + getMovement(Direction::UP);
				Vec2 bottomPos = pos + getMovement(Direction::DOWN);

				topBorder[x - MostTopLeft.x] = (pos.y == 0) || (topPos.y >= 0 && (map[topPos.y][topPos.x] != region.letter));
				bottomBorder[x - MostTopLeft.x] = (pos.y == height - 1) || (bottomPos.y < height && (map[bottomPos.y][bottomPos.x] != region.letter));
			}
		}

		int topBorderCount = 0;
		bool lastTopBorder = false;
		for(int i = 0; i < lineWidth; i++)
		{
			if(topBorder[i])
			{
				if(!lastTopBorder)
				{
					topBorderCount++;
				}
				lastTopBorder = true;
			} else {
				lastTopBorder = false;
			}
		}

		int bottomBorderCount = 0;
		bool lastBottomBorder = false;
		for(int i = lineWidth - 1; i >= 0; i--)
		{
			if(bottomBorder[i])
			{
				if(!lastBottomBorder)
				{
					bottomBorderCount++;
				}
				lastBottomBorder = true;
			} else {
				lastBottomBorder = false;
			}
		}

		tCount += topBorderCount;
		bCount += bottomBorderCount;
	}

	for(int x = MostTopLeft.x; x <= MostBottomRight.x; x++)
	{
		int lineHeight = MostBottomRight.y - MostTopLeft.y + 1;
		std::vector<bool> leftBorder = std::vector<bool>(lineHeight);
		std::vector<bool> rightBorder = std::vector<bool>(lineHeight);
		for(int y = MostTopLeft.y; y <= MostBottomRight.y; y++)
		{
			if(region.contains({x,y}))
			{
				Vec2 pos = {x,y};

				Vec2 leftPos = pos + getMovement(Direction::LEFT);
				Vec2 rightPos = pos + getMovement(Direction::RIGHT);

				leftBorder[y - MostTopLeft.y] = (pos.x == 0) || (leftPos.x >= 0 && (map[leftPos.y][leftPos.x] != region.letter));
				rightBorder[y - MostTopLeft.y] = (pos.x == width - 1)
					|| (rightPos.x < width && (map[rightPos.y][rightPos.x] != region.letter));
			}
		}

		int leftBorderCount = 0;
		bool lastLeftBorder = false;
		for(int i = 0; i < lineHeight; i++)
		{
			if(leftBorder[i])
			{
				if(!lastLeftBorder)
				{
					leftBorderCount++;
				}
				lastLeftBorder = true;
			} else {
				lastLeftBorder = false;
			}
		}

		int rightBorderCount = 0;
		bool lastRightBorder = false;
		for(int i = lineHeight - 1; i >= 0; i--)
		{
			if(rightBorder[i])
			{
				if(!lastRightBorder)
				{
					rightBorderCount++;
				}
				lastRightBorder = true;
			} else {
				lastRightBorder = false;
			}
		}

		lCount += leftBorderCount;
		rCount += rightBorderCount;
	}

	return tCount + bCount + lCount + rCount;

}

void d12p2()
{
	std::ifstream file("./Inputs/Day12.txt");
	std::string input((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	//input = Example;

	Map map;
	Regions regions;
	auto lines = split(input, '\n');

	for(const auto& line : lines)
	{
		std::vector<char> lineChars;
		for(const auto& c : line)
		{
			lineChars.push_back(c);
		}
		map.push_back(lineChars);
	}

	printf("Map dimensions: %zu x %zu\n", map.size(), map[0].size());

	for(int y = 0; y < map.size(); y++)
	{
		for(int x = 0; x < map[0].size(); x++)
		{
			floodFill(map, {x,y}, regions);
		}
	}

	printf("Found %zu regions\n", regions.size());
	int totalPrice = 0;
	for(const auto& region : regions)
	{
		printf("Region: %c area: %llu sides: %d\n", region.letter, region.tiles.size(), getSides(region, map));
		totalPrice += getSides(region, map) * region.tiles.size();
	}

	// To high: 908978
	printf("Total price: %d\n", totalPrice);
}