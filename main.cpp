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
#include "ConsoleRenderer/InputField.hpp"
#include "ConsoleRenderer/ConsoleRenderer.hpp"
#include "ConsoleRenderer/DataListRenderable.hpp"

using namespace std;

int main() {
	//Data storage
	DataKeeper dk;
	dk.loadFromFile();

	//Communication with console & renderer
	Console console;
	ConsoleRenderer consoleRenderer(console);

	//Text field
	TextField *tf = new TextField({20, 1}, " ??? ");
	tf->move({100, (short) (console.getSize().Y - 1)});

	//Data list renderable
	auto *booksList = new DataListRenderable({console.getSize().X, 14}, &dk.data);

	auto *input = new InputField({console.getSize().X, 1});
	input->setTextColor(Console::getFullColor(Console::Color::BRIGHT_WHITE, Console::Color::GRAY));
	input->move({0, (short) (console.getSize().Y - 3)});

	//General info
	auto *instructions = new TextField({console.getSize().X, 1});
	instructions->text = "Ogolne:     [Strzalka w gore / dol] - Zaznacz rekord    [I] - Szukaj    [ESC] - Zakoncz";
	instructions->setTextColor(Console::getFullColor(Console::Color::BRIGHT_WHITE, Console::Color::BLUE));
	instructions->move({0, (short) (console.getSize().Y - 2)});

	//Sort info
	auto *sortInstructions = new TextField({console.getSize().X, 1});
	sortInstructions->text = "Sortowanie: [T] - Tytul    [A] - Autor    [S] - Status    [Z] - Sygnatura";
	sortInstructions->setTextColor(Console::getFullColor(Console::Color::BRIGHT_WHITE, Console::Color::PURPLE));
	sortInstructions->move({0, (short) (console.getSize().Y - 1)});


	consoleRenderer.addRenderable(booksList);
	consoleRenderer.addRenderable(input);
	consoleRenderer.addRenderable(instructions);
	consoleRenderer.addRenderable(sortInstructions);
	consoleRenderer.addRenderable(tf);
	consoleRenderer.render();

	//App heartbeat
	bool close = false;
	bool textInputMode = false;

	while (!close) {
		auto c = console.getKey();

		stringstream ss;
		ss << c.uChar.AsciiChar << " (" << (int) c.uChar.AsciiChar << " / " << c.wVirtualKeyCode << ")";
		tf->text = ss.str();

		if (textInputMode) {
			input->insert(c.uChar.AsciiChar);

			//BACKSPACE
			if (c.wVirtualKeyCode == KEY::BACKSPACE) {
				input->backspace();
			}

			//ESC
			if (c.wVirtualKeyCode == KEY::ESC) {
				input->setTextColor(Console::getFullColor(Console::Color::BRIGHT_WHITE, Console::Color::GRAY));
				textInputMode = false;
			}
		} else {
			switch (c.wVirtualKeyCode) {
				case KEY::ARROW_UP:
					//Previous record
					dk.data.prev();
					break;
				case KEY::ARROW_DOWN:
					//Next record
					dk.data.next();
					break;
				case KEY::A:
					//Sort by Author
					dk.data.sort(DataList::SortBy::Author);
					break;
				case KEY::T:
					//Sort by Title
					dk.data.sort(DataList::SortBy::Name);
					break;
				case KEY::S:
					//Sort by State
					dk.data.sort(DataList::SortBy::State);
					break;
				case KEY::Z:
					//Sort by Signature
					dk.data.sort(DataList::SortBy::Signature);
					break;
				case KEY::ESC:
					//End program
					close = true;
					break;
				case KEY::I:
					//Enable input
					input->setTextColor(Console::getFullColor(Console::Color::BLUE, Console::Color::WHITE));
					textInputMode = true;
					break;
			}
		}

		consoleRenderer.render();
	}

	//Save data
	dk.saveToFile();
	return 0;
}