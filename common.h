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

#endif // COMMON_H
