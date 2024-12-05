//
// Created by tillw on 05/12/2024.
//

#include "Day04.h"
#include "../common.h"
#include "../colors.h"
#include <cstdio>
#include <fstream>
#include <iosfwd>
#include <iostream>
#include <vector>

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
        case TOP:
            return Vec2(0, -1);
        case TOPRIGHT:
            return Vec2(1, -1);
        case RIGHT:
            return Vec2(1, 0);
        case BOTTOMRIGHT:
            return Vec2(0, 1);
        case BOTTOM:
            return Vec2(0, 1);
        case BOTTOMLEFT:
            return Vec2(1, 1);
        case LEFT:
            return Vec2(1, 0);
        case TOPLEFT:
            return Vec2(1, -1);
    }
}

int checkLetter(Vec2 pos) {
    auto maxDim = data.size();

    int foundCount = 0;
    for(int i = 0; i<8;i++) {
        std::string testStr;
        auto dir = static_cast<enum dir>(i);
        auto vec = fromDir(dir);
        auto maxDir = vec * 3;
        auto maxPos = pos + maxDir;


        if(maxPos.x < 0 || maxPos.y < 0 || maxPos.x > maxDim-1 || maxPos.y > maxDim )
        {
            continue;
        }

        for(int j = 0; j<4;j++) {
            testStr += data[pos.x + (vec.x * j)][pos.y + (vec.y * j)];
        }

        if(testStr == "XMAS")
            foundCount++;
    }
    return foundCount;
}

// zwischen 2088 und 4392

void d4p1() {
    std::ifstream file("./Inputs/Day04.txt");
    std::string str;

    while (std::getline(file, str))
        data.push_back(str.substr(0, str.size() - 1));


    int sum = 0;
    for (int i = 0; i < data.size(); i++) {
        for (int j = 0; j < data.size(); j++) {
            if (data[i][j] == 'X'){}
                sum += checkLetter(Vec2(i, j));
        }
    }

    std::cout << "Found XMAS " << BOLDGREEN << sum << " times" << RESET << std::endl;
}

void d4p2() {

};
