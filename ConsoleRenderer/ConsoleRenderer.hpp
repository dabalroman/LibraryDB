//
// Created by rd on 20.05.2019.
//

#ifndef LIBRARYDB_CONSOLERENDERER_HPP
#define LIBRARYDB_CONSOLERENDERER_HPP


#include <vector>
#include "../Console.hpp"

class ConsoleRenderer {
public:
	struct RICHCHAR {
		char c;
		Console::COLOR color;
	};
	typedef vector<RICHCHAR> RICHLINE;
	typedef vector<RICHLINE> RICHTEXT;

private:
	COORD size;
	RICHTEXT current, next;

public:
	static void
	insertStringIntoBuffer(RICHTEXT &buffer, string s, COORD coord, Console::COLOR color = Console::COLOR_DEFAULT);
//	ConsoleRenderer(COORD size);
};


#endif //LIBRARYDB_CONSOLERENDERER_HPP
