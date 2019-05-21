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

void Console::copyBufferContentsToBuffer(Console::RICHTEXT &target, Console::RICHTEXT &source,
                                         COORD offset) {
	if (target.empty() || source.empty()) {
		return;
	}

	int xBoundary = min(target[0].size(), source[0].size() + offset.X);
	int yBoundary = min(target.size(), source.size() + offset.Y);

	for (int y = offset.Y; y < yBoundary; y++) {
		for (int x = offset.X; x < xBoundary; x++) {
			target[y][x] = source[y][x];
		}
	}
}

void Console::insertStringIntoBuffer(Console::RICHTEXT &buffer, string s, COORD offset,
                                     Console::COLOR color) {
	if (buffer.empty() || s.length() <= 0) {
		return;
	}

	int xBoundary = min(buffer[0].size(), s.length() + offset.X + 1);
	int yBoundary = min(buffer.size(), (unsigned) offset.Y + 1);

	cout
			<< " xb" << offset.X
			<< "-" << xBoundary - 1
			<< " yb" << offset.Y
			<< "-" << yBoundary - 1
			<< " sl" << s.length()
			<< " bx" << buffer[0].size()
			<< " by" << buffer.size()
			<< endl;

	for (int y = offset.Y; y < yBoundary; y++) {
		for (int x = offset.X; x < xBoundary; x++) {
			buffer[y][x] = {s[x - offset.X], color};
		}
	}
}

void Console::prepareBuffer(Console::RICHTEXT &buffer, COORD size) {
	buffer.clear();
	buffer.resize(size.Y);

	for (Console::RICHLINE &sr : buffer) {
		sr.resize(size.X, {' ', Console::COLOR_DEFAULT});
	}

	cout << "Buffer prepared: " << buffer.size() << " x " << buffer[0].size() << endl;
}

void Console::createBufferBorder(Console::RICHTEXT &buffer, Console::COLOR color) {
	Console::RICHCHAR horizontal = {'-', color};
	Console::RICHCHAR vertical = {'|', color};

	int bufferXSize = buffer[0].size();
	int bufferYSize = buffer.size();

	//Create top & bottom lines
	fill(buffer[0].begin(), buffer[0].end(), horizontal);
	fill(buffer[bufferYSize - 1].begin(), buffer[bufferYSize - 1].end(), horizontal);

	//Create left & right lines
	for (int y = 1; y < bufferYSize - 1; y++) {
		buffer[y][0] = vertical;
		buffer[y][bufferXSize - 1] = vertical;
	}
}
