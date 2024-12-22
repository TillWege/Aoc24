#include <fstream>
#include <iostream>
#include <vector>
#include "../common.h"
#include "../colors.h"

enum Tile { EMPTY, WALL, GUARD, VISITED, ERROR };

Tile getTile(char c) {
  if (c == '.') {
    return EMPTY;
  } else if (c == '#') {
    return WALL;
  } else if (c == '^') {
    return GUARD;
  } else {
    return ERROR;
  }
}

std::vector<std::vector<Tile>> mapData;

enum dir {
    TOP,
    RIGHT,
    BOTTOM,
    LEFT,
};

Vec2 getMovement(dir dir)
{
    switch (dir) {
    case TOP:
        return {0 ,1};
    case RIGHT:
        return {1,0};
    case BOTTOM:
        return {0,-1};
    case LEFT:
        return {-1,0};
    }
}

dir currentDir = TOP;

void nextDir() {
    switch(currentDir) {
    case TOP:
        currentDir = RIGHT;
        break;
    case RIGHT:
        currentDir = BOTTOM;
        break;
    case BOTTOM:
        currentDir = LEFT;
        break;
    case LEFT:
        currentDir = TOP;
        break;
    }
}

void d6p1() {
  std::ifstream file("./Inputs/Day06e.txt");
  std::string str;

  int idy = 0;
  Vec2 pos = {0,0};
  while (std::getline(file, str)) {
      std::vector<Tile> line;
      for(int i = 0; i<str.length(); i++){
          Tile nt = getTile(str[i]);
          line.push_back(nt);

          if(nt == GUARD) {
              pos.x = i;
              pos.y = idy;
          }
      }
      mapData.push_back(line);
      idy++;


  }

  std::cout << "Found " << BOLDRED << "PLAYER " << RESET << "at " << pos << std::endl;
  std::cout << "Map is " << BOLDGREEN << mapData.size() << ":" << mapData[0].size() << RESET << std::endl;
}

void d6p2()
{

}
