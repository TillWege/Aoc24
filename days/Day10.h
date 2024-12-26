//
// Created by tillw on 23/12/2024.
//

#ifndef DAY10_H
#define DAY10_H

#include "DayBase.h"
#include <vector>
#include "../common.h"

class Day10 : public DayBase {
public:
    void load() override;
    void part1() override;
    void part2() override;

private:
    std::vector<std::vector<int>> mapData;
    std::vector<Vec2> possibleStarts;
    
    bool isMoveAllowed(const Vec2& pos, Direction dir);
    int getTrailHeadSum(const Vec2& startPos, bool filterDupes = true);
};

#endif //DAY10_H
