#include "colors.h"
#include "days/DayBase.h"
#include "days/Day01.h"
#include "days/Day02.h"
#include "days/Day03.h"
#include "days/Day04.h"
#include "days/Day05.h"
#include "days/Day06.h"
#include "days/Day07.h"
#include "days/Day08.h"
#include "days/Day09.h"
#include "days/Day10.h"
#include "days/Day11.h"
#include "days/Day12.h"
#include "days/Day13.h"
#include <iostream>
#include <signal.h>
#include <memory>
#include <array>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#endif


const int DAYS_IMPLEMENTED = 13;
int cursor = DAYS_IMPLEMENTED;
bool exitFlag = false;

std::array<std::unique_ptr<DayBase>, 13> days = {
    std::make_unique<Day01>(),
	std::make_unique<Day02>(),
	std::make_unique<Day03>(),
	std::make_unique<Day04>(),
	std::make_unique<Day05>(),
	std::make_unique<Day06>(),
	std::make_unique<Day07>(),
	std::make_unique<Day08>(),
	std::make_unique<Day09>(),
	std::make_unique<Day10>(),
	std::make_unique<Day11>(),
	std::make_unique<Day12>(),
	std::make_unique<Day13>()
};

void signalHandler(int signum) { exitFlag = true; }

#ifdef _WIN32
void setCursorPosition(int x, int y) {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD pos = {(SHORT)x, (SHORT)y};
  SetConsoleCursorPosition(hConsole, pos);
}

void hideCursor() {
  HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO info;
  info.dwSize = 100;
  info.bVisible = FALSE;
  SetConsoleCursorInfo(consoleHandle, &info);
}

void showCursor() {
  HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO info;
  info.dwSize = 100;
  info.bVisible = TRUE;
  SetConsoleCursorInfo(consoleHandle, &info);
}

#else
void setCursorPosition(int x, int y) {
    std::cout << "\033[" << (y + 1) << ";" << (x + 1) << "H";
    std::cout.flush();
}

void hideCursor() {
    std::cout << "\033[?25l";
    std::cout.flush();
}

void showCursor() {
    std::cout << "\033[?25h";
    std::cout.flush();
}

char getch() {
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return buf;
}

bool kbhit() {
    struct termios term;
    tcgetattr(0, &term);
    struct termios term2 = term;
    term2.c_lflag &= ~ICANON;
    tcsetattr(0, TCSANOW, &term2);
    int byteswaiting;
    ioctl(0, FIONREAD, &byteswaiting);
    tcsetattr(0, TCSANOW, &term);
    return byteswaiting > 0;
}
#endif

void clearScreen() {
#ifdef _WIN32
  system("cls");
#else
    std::cout << "\033[2J\033[H";
    std::cout.flush();
#endif
}

void displayMenu() {
    static bool firstRun = true;
    if (firstRun) {
        clearScreen();
        firstRun = false;
    }

    for (int i = 0; i < 25; i++) {
        setCursorPosition(0, i);
        std::cout << "\033[K";
    }

    for (int i = 1; i <= 25; i++) {
        setCursorPosition(0, i - 1);
        if (i == cursor)
            std::cout << BOLDBLUE << "> " << RESET;
        else
            std::cout << "  ";

        if (i <= DAYS_IMPLEMENTED) {
            std::cout << BOLDGREEN << "Day " << i << RESET;
        } else {
            std::cout << BOLDRED << "Day " << i << RESET;
        }
    }

    setCursorPosition(0, 25);
    std::cout.flush();
}

void solveDay() {
    std::cout << "Running " << BOLDGREEN << "day " << cursor << RESET
            << std::endl;
    
    if (cursor > 0 && cursor <= DAYS_IMPLEMENTED && days[cursor - 1]) {
        days[cursor - 1]->part1();
        days[cursor - 1]->part2();
    } else {
        std::cout << BOLDRED << "Day " << cursor << RESET << " not implemented yet"
                << std::endl;
    }
}

int main(int argc, char *argv[]) {
    bool isInteractive = true;
    if (argc > 1) {
        std::string interactiveFlag = "-auto";
        std::string flag = argv[1];
        isInteractive = flag != interactiveFlag;
    }

    if (isInteractive) {
        signal(SIGINT, signalHandler);
        hideCursor();
        displayMenu();

        while (!exitFlag) {
#ifdef _WIN32
      if (_kbhit()) {
        char key = _getch();
#else
            if (kbhit()) {
                char key = getch();
#endif
                if (key == 27) {
                    char nextChar = getch();
                    if (nextChar == '[') {
                        char arrowKey = getch();
                        if (arrowKey == 'A' && cursor > 1)
                            cursor--;
                        else if (arrowKey == 'B' && cursor < 25)
                            cursor++;
                        displayMenu();
                    }
                    continue;
                }

                if (key == 'q' || key == 'Q')
                    break;
                if (key == '\r' || key == '\n') {
                    showCursor();
                    clearScreen();
                    setCursorPosition(0, 0);
                    solveDay();
                    break;
                }
            }
        }
        showCursor();
        setCursorPosition(0, 25);
        std::cout << "\033[K";
        std::cout.flush();
    } else {
        solveDay();
    }

    return 0;
}
