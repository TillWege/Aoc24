#ifndef DAY01_H
#define DAY01_H

#include "DayBase.h"
#include <vector>

class Day01 : public DayBase {
public:
    void load() override;
    void part1() override;
    void part2() override;

private:
    std::vector<int> col1, col2;
};

#endif // DAY01_H
