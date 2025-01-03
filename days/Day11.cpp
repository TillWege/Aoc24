//
// Created by tillw on 24/12/2024.
//

#include "Day11.h"
#include "../common.h"

#include <string>
#include <fstream>
#include <map>

void Day11::printLine(const Line& line)
{
    for(const auto& stone : line)
    {
        printf("%llu ", stone.value);
    }
    printf("\n");
}

void Day11::blink(Line& line)
{
    Line newLine;
    for (auto& item : line)
    {
        if (item.value == 0)
        {
            Stone stone {
                1
            };
            newLine.push_back(stone);
        } else {
            std::string strVal = std::to_string(item.value);
            auto digits = int(std::log10(item.value) + 1);

            if(digits % 2 == 0)
            {
                long long idk = std::pow(10, digits / 2);
                long long l = (item.value - item.value % idk) / idk;
                long long r = item.value % idk;

                Stone stonelh {
                    l
                };

                newLine.push_back(stonelh);

                Stone stonerh {
                    r
                };

                newLine.push_back(stonerh);
            } else {
                Stone stone {
                    item.value * 2024
                };
                newLine.push_back(stone);
            }
        }
    }
    line = newLine;
}

void Day11::load()
{
    std::ifstream file("./Inputs/Day11.txt");
    std::string input((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    auto parts = split(input, ' ');
    for(const auto& part : parts)
    {
        if(part.empty())
            continue;

        Stone stone {
            std::stoi(part)
        };
        line.push_back(stone);
    }
}

void Day11::part1()
{
	load();
    printf("Day 11 Part 1:\n");
    printf("Line after parsing:\n");
    printLine(line);

    for(int i = 0; i < 25; i++)
    {
        blink(line);
    }

    printf("Stone count %zu\n", line.size());
}

unsigned long long Day11::getSplitCount(unsigned long long num, int depth)
{
    if(depth == 0)
    {
        return 1;
    } else {
        auto p = std::make_pair(num, depth);

        if(cache.contains(p))
        {
            return cache[p];
        } else {
            unsigned long long res;
            if (num == 0)
            {
                res = getSplitCount(1, depth - 1);
            } else {
                auto digits = int(std::log10(num) + 1);

                if(digits % 2 == 0)
                {
                    unsigned long long idk = std::pow(10, digits / 2);
                    unsigned long long l = (num - num % idk) / idk;
                    unsigned long long r = num % idk;

                    res = getSplitCount(l, depth - 1) + getSplitCount(r, depth - 1);
                } else {
                    res = getSplitCount(num * 2024, depth - 1);
                }
            }
            cache[p] = res;
            return res;
        }
    }
}

void Day11::part2()
{
	line.clear();
	load();
    printf("Day 11 Part 2:\n");
    unsigned long long StoneCount = 0;
    for(const auto& stone : line)
    {
        StoneCount += getSplitCount(stone.value, 75);
    }

    printf("Stone count: %zu\n", StoneCount);
    printf("Total cache size: %zu\n", cache.size());
}
