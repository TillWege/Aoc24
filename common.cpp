//
// Created by tillw on 28/12/2024.
//
#include "common.h"

template <typename Out>
void split(const std::string &s, char delim, Out result)
{
	std::istringstream iss(s);
	std::string item;
	while (std::getline(iss, item, delim))
	{
		*result++ = item;
	}
}

std::vector<std::string> split(const std::string &s, char delim)
{
	std::vector<std::string> elems;
	split(s, delim, std::back_inserter(elems));
	return elems;
}

Vec2<> getMovement(Direction dir)
{
	switch (dir)
	{
	case Direction::UP:
		return { 0, -1 };
	case Direction::DOWN:
		return { 0, 1 };
	case Direction::LEFT:
		return { -1, 0 };
	case Direction::RIGHT:
		return { 1, 0 };

	}
}