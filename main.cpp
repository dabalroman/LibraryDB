#include <iostream>
#include <iomanip>
#include <windows.h>
#include <cctype>
#include <cstdio>
#include <wincon.h>
#include <conio.h>
#include <sstream>
#include "DataKeeper.hpp"
#include "Utils.hpp"
#include "ConsoleRenderer/Console.hpp"
#include "ConsoleRenderer/TextField.hpp"
#include "ConsoleRenderer/ConsoleRenderer.hpp"

using namespace std;
HANDLE hIn, hOut;

KEY_EVENT_RECORD getKey() {
	DWORD mode, count;
	INPUT_RECORD inputRecord;

	GetConsoleMode(hIn, &mode);
	SetConsoleMode(hIn, 0);
	FlushConsoleInputBuffer(hIn);

	do {
		ReadConsoleInput(hIn, &inputRecord, 1, &count);
	} while (inputRecord.EventType != KEY_EVENT || !inputRecord.Event.KeyEvent.bKeyDown);

	SetConsoleMode(hIn, mode);

	return inputRecord.Event.KeyEvent;
}

int main() {
	//Data storage
	DataKeeper dk;
	//Communication with console
	Console console;
	//Console screen render
	ConsoleRenderer consoleRenderer(console);

	//Text field
	TextField *tf = new TextField({20, 3}, " ??? ");
	TextField *tfW = new TextField({11, 3}, "0 x 0");

	consoleRenderer.addRenderable(tf);
	consoleRenderer.addRenderable(tfW);
	consoleRenderer.render();


//	if (!dk.loadFromFile()) {
//		cout << "File access error!";
//		_getch();
//		return 1;
//	}
//
//	for (auto r : dk.records) {
//		cout << r->name << endl;
//	}
//
//	dk.saveToFile();

	hIn = GetStdHandle(STD_INPUT_HANDLE);
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	//App heartbeat
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
	while (true) {
		auto c = getKey();

		stringstream ss;
		ss << c.uChar.AsciiChar << " (" << (int) c.uChar.AsciiChar << " / " << c.wVirtualKeyCode << ")";
		tf->text = ss.str();

		ss.str("");
		ss << setw(2) << tfW->getPosition().X << " x " << setw(2) << tfW->getPosition().Y;
		tfW->text = ss.str();

		if (c.uChar.AsciiChar == 90) {
			tf->setBorderColor(Console::getFullColor(Console::Color::RED));
		} else {
			tf->setBorderColor(Console::getFullColor(Console::Color::LIGHT_BLUE));
		}

		switch (c.wVirtualKeyCode) {
			case 37:
				tf->move({(short) (tf->getPosition().X - 1), (short) (tf->getPosition().Y)});
				break;
			case 38:
				tf->move({(short) (tf->getPosition().X), (short) (tf->getPosition().Y - 1)});
				break;
			case 39:
				tf->move({(short) (tf->getPosition().X + 1), (short) (tf->getPosition().Y)});
				break;
			case 40:
				tf->move({(short) (tf->getPosition().X), (short) (tf->getPosition().Y + 1)});
				break;
			case 65:
				tfW->move({(short) (tfW->getPosition().X - 1), (short) (tfW->getPosition().Y)});
				break;
			case 87:
				tfW->move({(short) (tfW->getPosition().X), (short) (tfW->getPosition().Y - 1)});
				break;
			case 68:
				tfW->move({(short) (tfW->getPosition().X + 1), (short) (tfW->getPosition().Y)});
				break;
			case 83:
				tfW->move({(short) (tfW->getPosition().X), (short) (tfW->getPosition().Y + 1)});
				break;
			default:
				break;
		}
		consoleRenderer.render();
	}
#pragma clang diagnostic pop

	_getch();
	return 0;
}