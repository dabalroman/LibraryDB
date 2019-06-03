//
// Created by rd on 21.05.2019.
//

#include <conio.h>
#include "Console.hpp"
#include "Buffer.hpp"

void Buffer::copyContent(Console::RICHTEXT &target, Console::RICHTEXT &source, COORD offset) {
	if (target.empty() || source.empty()
	    || offset.X >= target[0].size() || offset.Y >= target.size()) {
		return;
	}

	int xBoundary = min(target[0].size() - offset.X, source[0].size());
	int yBoundary = min(target.size() - offset.Y, source.size());

	for (int y = 0; y < yBoundary; y++) {
		for (int x = 0; x < xBoundary; x++) {
			target[y + offset.Y][x + offset.X] = source[y][x];
		}
	}
}

void Buffer::insertString(Console::RICHTEXT &buffer, string s, COORD offset, Console::FULLCOLOR color) {
	if (buffer.empty() || s.length() <= 0) {
		return;
	}

	int xBoundary = min(buffer[0].size(), s.length() + offset.X + 1);
	int yBoundary = min(buffer.size(), (unsigned) offset.Y + 1);

	for (int y = offset.Y; y < yBoundary; y++) {
		for (int x = offset.X; x < xBoundary; x++) {
			buffer[y][x] = {s[x - offset.X], color};
		}
	}
}

void Buffer::prepare(Console::RICHTEXT &buffer, COORD size) {
	buffer.clear();
	buffer.resize(size.Y);

	for (Console::RICHLINE &sr : buffer) {
		sr.resize(size.X, {' ', Console::COLOR_DEFAULT});
	}
}

void Buffer::createBorder(Console::RICHTEXT &buffer, Console::FULLCOLOR color) {
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

void Buffer::fill(Console::RICHTEXT &buffer, char c, Console::FULLCOLOR color) {
	for (Console::RICHLINE &sr : buffer) {
		sr.assign(sr.size(), {c, color});
	}
}
