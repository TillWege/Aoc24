#ifndef DAYBASE_H
#define DAYBASE_H

#include <string>

class DayBase {
public:
    virtual ~DayBase() = default;
    virtual void load() = 0;
    virtual void part1() = 0;
    virtual void part2() = 0;
};

#endif // DAYBASE_H
