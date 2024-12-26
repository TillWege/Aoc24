//
// Created by tillw on 23/12/2024.
//

#include "Day10.h"

#include <string>
#include <fstream>

bool Day10::isMoveAllowed(const Vec2& pos, Direction dir)
{
    int diff = 0;
	Vec2 myPos = pos;
    Vec2 newPos = myPos + getMovement(dir);

    if (newPos.x < 0 || newPos.y < 0 || newPos.x >= mapData.size() || newPos.y >= mapData[0].size())
    {
        return false;
    }
    diff = mapData[newPos.y][newPos.x] - mapData[pos.y][pos.x];

    return diff == 1;
}

int Day10::getTrailHeadSum(const Vec2& startPos, bool filterDupes) {
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
            if (isMoveAllowed(pos, dir))
            {
                Vec2 newPos = pos + getMovement(dir);
                if(mapData[newPos.y][newPos.x] == 9)
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

void Day10::load()
{
    std::ifstream file("./Inputs/Day10.txt");
    std::string input((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    auto lines = split(input, '\n');

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
}

void Day10::part1()
{
	load();
    int trailHeadSum = 0;

    for(const auto& start : possibleStarts)
    {
        trailHeadSum += getTrailHeadSum(start);
    }

    printf("Sum of Trailheads: %d\n", trailHeadSum);
}

void Day10::part2()
{
    int trailHeadSum = 0;

    for(const auto& start : possibleStarts)
    {
        trailHeadSum += getTrailHeadSum(start, false);
    }

    printf("Sum of unique Trailheads: %d\n", trailHeadSum);
}
