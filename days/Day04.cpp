//
// Created by tillw on 05/12/2024.
//

#include <fstream>
#include <iosfwd>
#include <sstream>
#include <vector>
#include "Day04.h"

std::vector<std::string> data;

struct vec
{
	int x, y;
};

enum dir
{
	TOP,
	TOPRIGHT,
	RIGHT,
	BOTTOMRIGHT,
	BOTTOM,
	BOTTOMLEFT,
	LEFT,
	TOPLEFT
};

vec fromDir(dir dir)
{
	switch (dir)
	{
	case TOP:
		return { 0, -1 };
	case TOPRIGHT:
		return { 1, -1 };
	case RIGHT:
		return { 1, 0 };
	case BOTTOMRIGHT:
		return {1,1};
	case BOTTOM:
		return {0,1};
	case BOTTOMLEFT:
		return {-1,1};
	case LEFT:
		return {-1,0};
	case TOPLEFT:
		return {-1,-1};
	}
}

bool checkLetter(int posX, int posY)
{

}

void d4p1()
{
	std::ifstream file("./Inputs/Day04.txt");
	std::string str;

	while (std::getline(file, str))
		data.push_back(str);

	for (int i = 0; i < data.size(); i++)
	{
		for (int j = 0; i < data.size(); j++)
		{
			if (data[i][j] == 'X')
				checkLetter(i, j);
		}
	}

}

void d4p2();