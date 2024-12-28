//
// Created by tillw on 28/12/2024.
//
#include "common.h"


#ifdef _MSC_VER
	#include <intrin.h>
	#define DEBUG_BREAK() __debugbreak()
#else
	#ifdef __APPLE__
		#include <signal.h>
		#define DEBUG_BREAK() raise(SIGTRAP)
	#else
		#define DEBUG_BREAK() __builtin_trap()
	#endif
#endif

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

void triggerBreakpoint() {
#ifdef _DEBUG
	DEBUG_BREAK();
#endif
}
