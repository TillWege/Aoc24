//
// Created by tillw on 05/12/2024.
//

#ifndef COMMON_H
#define COMMON_H

#include <ostream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>

struct Vec2
{
    Vec2(int x, int y) : x(x), y(y) {}

    Vec2 operator+(Vec2 other);
    Vec2 operator-(Vec2 &other);
    Vec2 operator*(int other);
	Vec2 operator/(int other);
	bool operator==(Vec2 other);
	bool operator<(const Vec2& other) const;
    std::ostream operator<<(std::ostream &os);

    int x, y;
};

inline Vec2 Vec2::operator+(Vec2 other)
{
    return {
        this->x + other.x,
        this->y + other.y};
}

inline Vec2 Vec2::operator-(Vec2 &other)
{
    return {
        this->x - other.x,
        this->y - other.y};
}

inline Vec2 Vec2::operator*(int other)
{
    return {
        this->x * other,
        this->y * other};
}

inline bool Vec2::operator==(Vec2 other)
{
	return (this->x == other.x && this->y == other.y);
}

inline Vec2 Vec2::operator/(int other)
{
	return {
		this->x / other,
		this->y / other
	};
}
inline bool Vec2::operator<(const Vec2& other) const
{
	if(this->x < other.x)
		return true;
	else if(this->x > other.x)
		return false;
	else
		return this->y < other.y;
}
inline std::ostream &operator<<(std::ostream &os, const Vec2 &v)
{
    os << "{" << v.x << ":" << v.y << "}";
    return os;
}

template <typename Out>
inline void split(const std::string &s, char delim, Out result)
{
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, delim))
    {
        *result++ = item;
    }
}

inline std::vector<std::string> split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

enum class Direction
{
	UP,
	RIGHT,
	DOWN,
	LEFT,
};

const Direction DIRECTIONS[] = {
		Direction::UP,
		Direction::RIGHT,
		Direction::DOWN,
		Direction::LEFT,
};

inline Vec2 getMovement(Direction dir)
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

#endif // COMMON_H
