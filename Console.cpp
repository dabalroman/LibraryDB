//
// Created by rd on 20.05.2019.
//

#include <windows.h>
#include <wincon.h>
#include "Console.hpp"

Console::Console() {
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	updateConsoleInfo();
}

void Console::setConsoleColor(Console::Color fg, Console::Color bg) {
	setConsoleColor(getColor(fg, bg));
}

void Console::setConsoleColor(Console::COLOR c) {
	cout.flush();
	SetConsoleTextAttribute(hOut, c);
}

void Console::cls() {
	setConsoleColor();
	updateConsoleInfo();

	DWORD length = csbi.dwSize.X * csbi.dwSize.Y;
	DWORD written;

	FillConsoleOutputCharacter(hOut, ' ', length, topLeft, &written);
	FillConsoleOutputAttribute(hOut, csbi.wAttributes, length, topLeft, &written);
	setCursorPosition();
}

void Console::setCursorPosition(int x, int y) {
	COORD c = {(short) x, (short) y};
	setCursorPosition(c);
}

void Console::setCursorPosition(COORD c) {
	cout.flush();
	SetConsoleCursorPosition(hOut, c);

	//Hide cursor
	cci.bVisible = false;
	SetConsoleCursorInfo(hOut, &cci);
}

COORD Console::getSize() {
	updateConsoleInfo();
	return COORD{csbi.srWindow.Right, csbi.srWindow.Bottom};
}

void Console::updateConsoleInfo() {
	GetConsoleScreenBufferInfo(hOut, &csbi);
	GetConsoleCursorInfo(hOut, &cci);
}

Console::COLOR Console::getColor(Console::Color fg, Console::Color bg) {
	return (COLOR) bg << 0x4 | (COLOR) fg;
}
