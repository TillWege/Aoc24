#include "Day04.h"
#include "../common.h"
#include "../colors.h"
#include <fstream>
#include <iostream>
#include <vector>

class Day04Impl {
public:
    std::vector<std::string> data;

    enum dir {
        TOP,
        TOPRIGHT,
        RIGHT,
        BOTTOMRIGHT,
        BOTTOM,
        BOTTOMLEFT,
        LEFT,
        TOPLEFT
    };

    Vec2 fromDir(dir dir) {
        switch (dir) {
            case TOP: return { 0, -1 };
            case TOPRIGHT: return { 1, -1 };
            case RIGHT: return { 1, 0 };
            case BOTTOMRIGHT: return { 1, 1 };
            case BOTTOM: return { 0, 1 };
            case BOTTOMLEFT: return { -1, 1 };
            case LEFT: return { -1, 0 };
            case TOPLEFT: return { -1, -1 };
        }
    }

    int findXMAS(Vec2 pos) {
        auto maxDim = data.size();
        auto lineLength = data[0].length();

        int foundCount = 0;
        for(int i = 0; i<8;i++) {
            std::string testStr;
            auto dir = static_cast<enum dir>(i);
            auto vec = fromDir(dir);
            auto maxPos = pos + (vec * 3);

            if(maxPos.x < 0 || maxPos.y < 0 || maxPos.x >= lineLength || maxPos.y >= maxDim)
                continue;

            for(int j = 0; j<4;j++) {
                testStr += data[pos.y + (vec.y * j)][pos.x + (vec.x * j)];
            }

            if(testStr == "XMAS")
                foundCount++;
        }
        return foundCount;
    }

    bool findCrossMass(Vec2 pos) {
        auto maxDim = data.size();
        auto lineLength = data[0].length();

        if(pos.x <= 0 || pos.y <= 0 || pos.x >= lineLength || pos.y >= maxDim - 1)
            return false;

        // check topleft / bottomright
        Vec2 tlVec = { pos.x - 1, pos.y - 1 };
        Vec2 brVec = { pos.x + 1, pos.y + 1 };

        std::string str1;
        str1 += data[tlVec.y][tlVec.x];
        str1 += data[pos.y][pos.x];
        str1 += data[brVec.y][brVec.x];

        bool tlbr = str1 == "MAS" || str1 == "SAM";

        // check topright / bottomleft
        Vec2 trVec = { pos.x + 1, pos.y - 1 };
        Vec2 blVec = { pos.x - 1, pos.y + 1 };

        std::string str2;
        str2 += data[trVec.y][trVec.x];
        str2 += data[pos.y][pos.x];
        str2 += data[blVec.y][blVec.x];

        bool trbl = str2 == "MAS" || str2 == "SAM";

        return (trbl && tlbr);
    }

    void loadData() {
        std::ifstream file("./Inputs/Day04.txt");
        std::string str;
        while (std::getline(file, str))
            data.push_back(str.substr(0, str.size()));
    }
};

void Day04::load() {
    Day04Impl impl;
    impl.loadData();
}

void Day04::part1() {
    Day04Impl impl;
    impl.loadData();

    int sum = 0;
    for (int line = 0; line < impl.data.size(); line++) {
        auto strLength = impl.data[line].length();
        for (int idx = 0; idx < strLength; idx++) {
            if (impl.data[line][idx] == 'X'){
                sum += impl.findXMAS(Vec2(idx, line));
            }
        }
    }

    std::cout << "Found XMAS " << BOLDGREEN << sum << " times" << RESET << std::endl;
}

void Day04::part2() {
    Day04Impl impl;
    impl.loadData();

    int sum = 0;
    for (int line = 0; line < impl.data.size(); line++) {
        auto strLength = impl.data[line].length();
        for (int idx = 0; idx < strLength; idx++) {
            if (impl.data[line][idx] == 'A'){
                sum += impl.findCrossMass(Vec2(idx, line));
            }
        }
    }

    std::cout << "Found X-MAS " << BOLDGREEN << sum << " times" << RESET << std::endl;
}
