//
// Created by rd on 20.05.2019.
//

#include "Console.hpp"

Console::Console() {
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	updateConsoleInfo();
	setColor();
}

void Console::setColor(Console::Color fg, Console::Color bg) {
	setColor(getFullColor(fg, bg));
}

void Console::setColor(Console::FULLCOLOR c) {
	cout.flush();
	currentColor = c;
	SetConsoleTextAttribute(hOut, c);
}

void Console::cls() {
	setColor();
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

	//Hide blinking cursor
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

Console::FULLCOLOR Console::getFullColor(Console::Color fg, Console::Color bg) {
	return (FULLCOLOR) bg << 0x4 | (FULLCOLOR) fg;
}

Console::FULLCOLOR Console::getCurrentColor() {
	return currentColor;
}
