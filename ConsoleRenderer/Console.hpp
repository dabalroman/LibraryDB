//
// Created by rd on 20.05.2019.
//

#ifndef LIBRARYDB_CONSOLE_HPP
#define LIBRARYDB_CONSOLE_HPP

#include <windows.h>
#include <iostream>
#include <vector>

using namespace std;

class Console {
	HANDLE hOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi{};
	CONSOLE_CURSOR_INFO cci{};
	const COORD topLeft = {0, 0};

public:
	typedef unsigned short FULLCOLOR;
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
	static const FULLCOLOR COLOR_DEFAULT = (unsigned short) Color::BRIGHT_WHITE;

	struct RICHCHAR {
		char c;
		Console::FULLCOLOR color;

		bool operator!=(const RICHCHAR &a) const {
			return (c != a.c || color != a.color);
		}
	};
	typedef vector<RICHCHAR> RICHLINE;
	typedef vector<RICHLINE> RICHTEXT;
private:
	FULLCOLOR currentColor = {};

public:
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
	void setColor(Color fg, Color bg = Color::BLACK);

	/**
	 * Sets console color
	 * @param c COLOR
	 */
	void setColor(FULLCOLOR c = COLOR_DEFAULT);

	/**
	 * Returns console color
	 * @return FULLCOLOR Console color
	 */
	FULLCOLOR getCurrentColor();

	/**
	 * Returns size of console
	 * @return COORD Size of console in characters
	 */
	COORD getSize();

	/**
	 * Returns FULLCOLOR
	 * @param fg Console::Color Foreground color. Default BRIGHT_WHITE
	 * @param bg Console::Color Background color. Default BLACK
	 * @return FULLCOLOR Combined fg & bg values
	 */
	static FULLCOLOR getFullColor(Color fg = Color::BRIGHT_WHITE, Color bg = Color::BLACK);
private:
	/**
	 * Fetch console info from OS
	 */
	void updateConsoleInfo();
};


#endif //LIBRARYDB_CONSOLE_HPP
