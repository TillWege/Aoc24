//
// Created by tillw on 26/12/2024.
//

#ifndef DAY13_H
#define DAY13_H

#include "DayBase.h"
#include "../common.h"
#include <vector>
#include <optional>
#include <cinttypes>

typedef Vec2<int64_t > Vec2Long;

class Day13 : public DayBase {
public:
    void load() override;
    void part1() override;
    void part2() override;
private:
	struct Clawmachine {
		Vec2Long ButtonA;
		Vec2Long ButtonB;
		Vec2Long Prize;

		std::optional<int> getLowestTicketsSimple();
		std::optional<int> getLowestTickets();
	};

	std::vector<Clawmachine> clawmachines;
};


#endif //DAY13_H
