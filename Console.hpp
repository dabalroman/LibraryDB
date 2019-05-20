//
// Created by rd on 20.05.2019.
//

#ifndef LIBRARYDB_CONSOLE_HPP
#define LIBRARYDB_CONSOLE_HPP

#include <windows.h>
#include <iostream>

using namespace std;

class Console {
	HANDLE hOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi{};
	CONSOLE_CURSOR_INFO cci{};
	const COORD topLeft = {0, 0};

public:
	typedef unsigned short COLOR;
	enum class Color : unsigned short {
		BLACK = 0x0,
		BLUE = 0x1,
		GREEN = 0x2,
		AQUA = 0x3,
		RED = 0x4,
		PURPLE = 0x5,
		YELLOW = 0x6,
		WHITE = 0x7,
		GRAY = 0x8,
		LIGHT_BLUE = 0x9,
		LIGHT_GREEN = 0xA,
		LIGHT_AQUA = 0xB,
		LIGHT_RED = 0xC,
		LIGHT_PURPLE = 0xD,
		LIGHT_YELLOW = 0xE,
		BRIGHT_WHITE = 0xF
	};
	static const COLOR COLOR_DEFAULT = (unsigned short) Color::BRIGHT_WHITE;

	Console();

	/**
	 * Wipe out console contents and attributes
	 */
	void cls();

	/**
	 * Sets cursor position
	 * @param x int
	 * @param y int
	 */
	void setCursorPosition(int x, int y);

	/**
	 * Sets cursor position
	 * @param c COORD
	 */
	void setCursorPosition(COORD c = {0, 0});

	/**
	 * Sets console color
	 * @param fg Console::Color Foreground color. Default BRIGHT_WHITE
	 * @param bg Console::Color Background color. Default BLACK
	 */
	void setConsoleColor(Color fg, Color bg = Color::BLACK);

	/**
	 * Sets console color
	 * @param c COLOR
	 */
	void setConsoleColor(COLOR c = COLOR_DEFAULT);

	/**
	 * Returns size of console
	 * @return COORD Size of console in characters
	 */
	COORD getSize();

	/**
	 * Returns COLOR
	 * @param fg Console::Color Foreground color. Default BRIGHT_WHITE
	 * @param bg Console::Color Background color. Default BLACK
	 * @return COLOR Combined fg & bg values
	 */
	static COLOR getColor(Color fg = Color::BRIGHT_WHITE, Color bg = Color::BLACK);

private:
	/**
	 * Fetch console info from OS
	 */
	void updateConsoleInfo();
};


#endif //LIBRARYDB_CONSOLE_HPP
