#include <iostream>
#include <conio.h>
#include <csignal>
#include <windows.h>
#include "colors.h"
#include "days/Day01.h"
#include "days/Day02.h"
#include "days/Day03.h"

const int DAYS_IMPLEMENTED = 3;
int cursor = DAYS_IMPLEMENTED;
bool exitFlag = false;

void signalHandler(int signum) {
	exitFlag = true;
}

// Function to set cursor position instead of clearing screen
void setCursorPosition(int x, int y) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hConsole, pos);
}

// Hide console cursor
void hideCursor() {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void displayMenu() {
	// Initial clear screen only once
	static bool firstRun = true;
	if (firstRun) {
		system("cls");
		firstRun = false;
	}

	// Buffer the output
	std::string output;
	for (int i = 1; i <= 25; i++) {
		setCursorPosition(0, i-1);

		if (i == cursor)
			std::cout << BOLDBLUE << "> " << RESET;
		else
			std::cout << "  "; // Two spaces to clear the arrow

		if (i <= DAYS_IMPLEMENTED) {
			std::cout << BOLDGREEN << "Day " << i << RESET;
		} else {
			std::cout << BOLDRED << "Day " << i << RESET;
		}

		// Clear the rest of the line
		std::cout << "    \r";
	}
}

void solveDay()
{
	std::cout << "Running " << BOLDGREEN << "day " << cursor << RESET << std::endl;
	if (cursor == 1) {
		d1p1();
		d1p2();
	} else if(cursor == 2){
		d2p1();
		d2p2();
	} else if(cursor == 3){
		d3p1();
		d3p2();
	} else {
		std::cout << BOLDRED << "Day " << cursor  << RESET << " not implemented yet" << std::endl;
	}
}

int main(int argc, char *argv[]) {
	bool isInteractive = true;

	if(argc > 1)
	{
		std::string interactiveFlag = "-auto";
		std::string flag = argv[1];
		isInteractive = flag != interactiveFlag;
	}

	if(isInteractive)
	{
		signal(SIGINT, signalHandler);
		hideCursor();
		displayMenu();

		while (!exitFlag)
		{
			if (_kbhit())
			{
				char key = _getch();
				if (key == 27) break; // ESC to exit

				int oldCursor = cursor;
				if (key == 72 && cursor > 1) cursor--; // Up arrow
				if (key == 80 && cursor < 25) cursor++; // Down arrow
				if (key == 13)
				{
					solveDay();
					break;
				}
				else if (oldCursor != cursor)
				{
					displayMenu();
				}
			}
		}
	} else {
		solveDay();
	}


	return 0;
}