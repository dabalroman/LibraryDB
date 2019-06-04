//
// Created by rd on 04.06.2019.
//

#include <sstream>
#include "ListScreen.hpp"

ListScreen::ListScreen(Console &consoleHandle_, DataKeeper &dataHandle_) : Screen(consoleHandle_, dataHandle_) {
	//DEBUG
	debug = new TextField({20, 1}, " ??? ");
	debug->move({100, (short) (consoleHandle->getSize().Y - 1)});

	//Books list
	booksList = new DataListRenderable({consoleHandle->getSize().X, 29}, &dataHandle->data);

	//Input field
	input = new InputField({consoleHandle->getSize().X, 1});
	input->setTextColor(Console::getFullColor(Console::Color::BRIGHT_WHITE, Console::Color::GRAY));
	input->setActiveColor(Console::getFullColor(Console::Color::BLACK, Console::Color::WHITE));
	input->move({0, (short) (consoleHandle->getSize().Y - 4)});
	input->preText = "Filtr: ";

	//General info
	instructions = new TextField({consoleHandle->getSize().X, 1});
	instructions->text = "Ogolne:     [Strzalka w gore / dol] - Zaznacz rekord               [Strzalka w prawo] - Szczegoly rekordu";
	instructions->setTextColor(Console::getFullColor(Console::Color::BRIGHT_WHITE, Console::Color::BLUE));
	instructions->move({0, (short) (consoleHandle->getSize().Y - 3)});

	instructions2 = new TextField({consoleHandle->getSize().X, 1});
	instructions2->text = "            [N] - Nowy rekord    [I] - Szukaj    [ESC] - Zakoncz";
	instructions2->setTextColor(Console::getFullColor(Console::Color::BRIGHT_WHITE, Console::Color::BLUE));
	instructions2->move({0, (short) (consoleHandle->getSize().Y - 2)});

	//Sort info
	sortInstructions = new TextField({consoleHandle->getSize().X, 1});
	sortInstructions->text = "Sortowanie: [T] - Tytul          [A] - Autor     [S] - Status      [Z] - Sygnatura";
	sortInstructions->setTextColor(
			Console::getFullColor(Console::Color::BRIGHT_WHITE, Console::Color::PURPLE));
	sortInstructions->move({0, (short) (consoleHandle->getSize().Y - 1)});

	//Add to render query
	addRenderable(booksList);
	addRenderable(input);
	addRenderable(instructions);
	addRenderable(instructions2);
	addRenderable(sortInstructions);
	addRenderable(debug);
}

int ListScreen::handleInput(KEY_EVENT_RECORD c) {
	stringstream ss;
	ss << c.uChar.AsciiChar << " (" << (int) c.uChar.AsciiChar << " / " << c.wVirtualKeyCode << ")";
	debug->text = ss.str();

	//Handle input mode
	if (textInputMode) {
		input->insert(c.uChar.AsciiChar);

		//BACKSPACE
		if (c.wVirtualKeyCode == KEY::BACKSPACE) {
			input->backspace();
		}

		//ESC
		if (c.wVirtualKeyCode == KEY::ESC) {
			input->setActive(false);
			textInputMode = false;
		}

		//Filter data
		dataHandle->data.filter(input->text);

		return RETURNCODES::DEFAULT;
	}

	//Handle function keys
	switch (c.wVirtualKeyCode) {
		case KEY::ARROW_UP:
			//Previous record
			dataHandle->data.prev();
			break;

		case KEY::ARROW_DOWN:
			//Next record
			dataHandle->data.next();
			break;

		case KEY::A:
			//Sort by Author
			dataHandle->data.sort(DataList::SortBy::Author);
			break;

		case KEY::T:
			//Sort by Title
			dataHandle->data.sort(DataList::SortBy::Name);
			break;

		case KEY::S:
			//Sort by State
			dataHandle->data.sort(DataList::SortBy::State);
			break;

		case KEY::Z:
			//Sort by Signature
			dataHandle->data.sort(DataList::SortBy::Signature);
			break;

		case KEY::I:
			//Enable input
			input->setActive(true);
			textInputMode = true;
			break;

		case KEY::ARROW_RIGHT:
			//Go to details screen
			return RETURNCODES::DETAILS_SCREEN;

		case KEY::ESC:
			//End program
			return RETURNCODES::EXIT;
	}

	return RETURNCODES::DEFAULT;
}
