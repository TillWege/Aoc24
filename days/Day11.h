//
// Created by tillw on 24/12/2024.
//

#ifndef DAY11_H
#define DAY11_H

#include "DayBase.h"
#include <map>
#include <vector>

class Day11 : public DayBase {
public:
    void load() override;
    void part1() override;
    void part2() override;

private:
    struct Stone {
        long long value;
    };
    
    typedef std::vector<Stone> Line;
    
    void printLine(const Line& line);
    void blink(Line& line);
    unsigned long long getSplitCount(unsigned long long num, int depth);
    
    std::map<std::tuple<unsigned long long, unsigned long long>, unsigned long long> cache;
    Line line;
};

#endif //DAY11_H
