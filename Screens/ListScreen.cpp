#include <sstream>
#include "ListScreen.hpp"

ListScreen::ListScreen(Console &consoleHandle_, DataKeeper &dataHandle_) : Screen(consoleHandle_, dataHandle_) {
	dataHandle->data.sort(DataList::SortBy::Title);

	//Books list
	booksList = new DataListRenderable({consoleHandle->getSize().X, 30}, &dataHandle->data);

	//Input field
	input = new InputField({consoleHandle->getSize().X, 1});
	input->setTextColor(Console::getFullColor(Console::Color::BRIGHT_WHITE, Console::Color::GRAY));
	input->setActiveColor(Console::getFullColor(Console::Color::BLACK, Console::Color::WHITE));
	input->move({0, (short) (consoleHandle->getSize().Y - 4)});
	input->preText = "Filtr: ";

	//General info
	instructions = new TextField({consoleHandle->getSize().X, 2});
	instructions->text = "Ogolne:     [Strzalka w gore / dol] - Zaznacz rekord               "
	                     "[Strzalka w prawo] - Szczegoly rekordu\n            "
	                     "[N] - Nowy rekord    [I] - Szukaj    [ESC] - Zakoncz";
	instructions->setTextColor(Console::getFullColor(Console::Color::BRIGHT_WHITE, Console::Color::BLUE));
	instructions->move({0, (short) (consoleHandle->getSize().Y - 3)});

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
	addRenderable(sortInstructions);
}

int ListScreen::handleInput(KEY_EVENT_RECORD c) {
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
			dataHandle->data.sort(DataList::SortBy::Title);
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

		case KEY::N:
			//New record
			//Create new record and go to details screen
			dataHandle->data.addRecord(new Record("?", "?", "?", "?"));
			dataHandle->data.setActiveElementByID(dataHandle->data.getSize() - 1);
			return RETURNCODES::DETAILS_SCREEN;

		case KEY::ARROW_RIGHT:
			//Go to details screen
			return RETURNCODES::DETAILS_SCREEN;

		case KEY::ESC:
			//End program
			return RETURNCODES::EXIT;
	}

	return RETURNCODES::DEFAULT;
}
