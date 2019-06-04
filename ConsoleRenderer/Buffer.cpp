#include <conio.h>
#include "Console.hpp"
#include "Buffer.hpp"
#include "../Utils.hpp"

void Buffer::copyContent(Console::RICHTEXT &target, Console::RICHTEXT &source, COORD offset) {
	//Are source and target not overlapping?
	if (target.empty() || source.empty()
	    || offset.X >= target[0].size() || offset.Y >= target.size()) {
		return;
	}

	//Find buffer boundaries
	int xBoundary = min(target[0].size() - offset.X, source[0].size());
	int yBoundary = min(target.size() - offset.Y, source.size());

	//Copy data
	for (int y = 0; y < yBoundary; y++) {
		for (int x = 0; x < xBoundary; x++) {
			target[y + offset.Y][x + offset.X] = source[y][x];
		}
	}
}

void Buffer::insertString(Console::RICHTEXT &buffer, string s, COORD offset, Console::FULLCOLOR color) {
	//Is there anything to insert
	if (buffer.empty() || s.length() <= 0) {
		return;
	}

	//Find buffer boundaries
	int xBoundary = buffer[0].size();
	int yBoundary = buffer.size();

	//Isn't string to long to fit in one line? (Or does not have any /n?)
	if (s.length() <= xBoundary && s.find('\n') == string::npos) {

		//Ok, copy
		for (int x = offset.X; x < xBoundary && (x - offset.X) <= s.length(); x++) {
			buffer[offset.Y][x] = {s[x - offset.X], color};
		}
	} else {
		//Nope, need to split
		vector<string> v = splitStringToRows(s, xBoundary);

		//Copy each row
		for (int y = offset.Y; y < yBoundary && (y - offset.Y) < v.size(); y++) {
			//Copy line
			for (int x = offset.X; x < xBoundary && (x - offset.X) <= v[y - offset.Y].length(); x++) {
				buffer[y][x] = {v[y - offset.Y][x - offset.X], color};
			}
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
