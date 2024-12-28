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

template <typename T = int>
struct Vec2 {
	T x, y;

	Vec2() : x(0), y(0) {}
	Vec2(T x, T y) : x(x), y(y) {}

	Vec2(const Vec2& other) : x(other.x), y(other.y) {}

	Vec2& operator=(const Vec2& other) {
		if (this != &other) {
			x = other.x;
			y = other.y;
		}
		return *this;
	}

	Vec2 operator+(const Vec2& other) const {
		return Vec2(x + other.x, y + other.y);
	}

	Vec2& operator+=(const Vec2& other) {
		x += other.x;
		y += other.y;
		return *this;
	}

	Vec2 operator-(const Vec2& other) const {
		return Vec2(x - other.x, y - other.y);
	}

	Vec2& operator-=(const Vec2& other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}

	Vec2 operator*(T scalar) const {
		return Vec2(x * scalar, y * scalar);
	}

	Vec2& operator*=(T scalar) {
		x *= scalar;
		y *= scalar;
		return *this;
	}

	Vec2 operator/(T scalar) const {
		return Vec2(x / scalar, y / scalar);
	}

	Vec2& operator/=(T scalar) {
		x /= scalar;
		y /= scalar;
		return *this;
	}

	T dot(const Vec2& other) const {
		return x * other.x + y * other.y;
	}

	T magnitude() const {
		return std::sqrt(x * x + y * y);
	}

	Vec2 normalized() const {
		T mag = magnitude();
		return Vec2(x / mag, y / mag);
	}

	bool operator==(const Vec2& other) const {
		return x == other.x && y == other.y;
	}

	bool operator!=(const Vec2& other) const {
		return !(*this == other);
	}

	// Output stream operator
	friend std::ostream& operator<<(std::ostream& os, const Vec2& vec) {
		os << "(" << vec.x << ", " << vec.y << ")";
		return os;
	}
};

//  ┌─────────────────────┐
//  │  String Functions   │
//  └─────────────────────┘

template <typename Out>
inline void split(const std::string &s, char delim, Out result);
std::vector<std::string> split(const std::string &s, char delim);

//  ┌──────────────────────────┐
//  │  Directions & Functions  │
//  └──────────────────────────┘

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

Vec2<> getMovement(Direction dir);

//  ┌──────────────────────────┐
//  │  Common Functions        |
//  └──────────────────────────┘

void triggerBreakpoint();

#endif // COMMON_H
