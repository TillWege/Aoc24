//
// Created by tillw on 26/12/2024.
//

#ifndef DAY13_H
#define DAY13_H

#include "DayBase.h"
#include "../common.h"
#include <vector>
#include <optional>

class Day13 : public DayBase {
public:
    void load() override;
    void part1() override;
    void part2() override;
private:
	struct Clawmachine {
		Vec2 ButtonA;
		Vec2 ButtonB;
		Vec2 Prize;

		std::optional<int> getLowestTickets();
	};

	std::vector<Clawmachine> clawmachines;
};


#endif //DAY13_H
