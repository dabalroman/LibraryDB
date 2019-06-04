#include <sstream>
#include "DetailsScreen.hpp"

int DetailsScreen::handleInput(KEY_EVENT_RECORD c) {
	//Current record
	Record *r = dataHandle->data.getActiveRecord();
	bool rowChanged = false;

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

		//Next row
		if (c.wVirtualKeyCode == KEY::ARROW_UP || c.wVirtualKeyCode == KEY::ENTER) {
			currentInputFiled++;
			if (currentInputFiled > 3) {
				currentInputFiled = 0;
			}
			rowChanged = true;
		}

		//Previous row
		if (c.wVirtualKeyCode == KEY::ARROW_DOWN) {
			currentInputFiled--;
			if (currentInputFiled < 0) {
				currentInputFiled = 3;
			}
			rowChanged = true;
		}
	} else {

		//Handle function keys
		switch (c.wVirtualKeyCode) {
			case KEY::S:
				//Set Status
				if (r->getState() == Record::State::Available) {
					r->setState(Record::State::Lend);
				} else if (r->getState() == Record::State::Lend) {
					r->setState(Record::State::Unavailable);
				} else {
					r->setState(Record::State::Available);
				}
				break;

			case KEY::E:
				//Edit
				input->setActive(true);
				textInputMode = true;
				//Fake change row to update input text
				rowChanged = true;
				break;

			case KEY::C:
				//Copy and set new record as active
				dataHandle->data.addRecord(new Record(*r));
				dataHandle->data.setActiveElementByID(dataHandle->data.getSize() - 1);
				return RETURNCODES::LIST_SCREEN;

			case KEY::DEL:
				//Delete record
				dataHandle->data.removeRecordByID(dataHandle->data.getActiveElementID());
				return RETURNCODES::LIST_SCREEN;

			case KEY::ARROW_LEFT:
				//List Screen
				return RETURNCODES::LIST_SCREEN;
		}
	}

	//Handle row change
	if (rowChanged) {
		switch (currentInputFiled) {
			case 0:
				input->text = r->title;
				break;
			case 1:
				input->text = r->author;
				break;
			case 2:
				input->text = r->description;
				break;
			case 3:
				input->text = r->signature;
				break;
		}
	}

	//Update preText in input field accordingly to edited field
	if (textInputMode) {
		switch (currentInputFiled) {
			case 0:
				r->title = input->text;
				input->activePreText = "Tytul: ";
				break;
			case 1:
				r->author = input->text;
				input->activePreText = "Autor: ";
				break;
			case 2:
				r->description = input->text;
				input->activePreText = "Opis: ";
				break;
			case 3:
				r->signature = input->text;
				input->activePreText = "Sygnatura: ";
				break;
		}
	} else {
		//Clear input if not in textInputMode
		input->text = "";
	}

	//Update fields
	title->text = r->title;
	author->text = r->author;
	description->text = r->description;
	signature->text = r->signature;

	//Update state
	switch (r->getState()) {
		case Record::State::Available:
			state->text = "Dostepna";
			break;
		case Record::State::Lend:
			state->text = "Wypozyczona";
			break;
		case Record::State::Unavailable:
			state->text = "Niedostepna";
			break;
	}

	return RETURNCODES::DEFAULT;
}

DetailsScreen::DetailsScreen(Console &consoleHandle_, DataKeeper &dataHandle_) : Screen(consoleHandle_, dataHandle_) {
	COORD descSize = {18, 2};
	COORD fieldSize = {100, 2};
	COORD descriptionDescSize = {18, 14};
	COORD descriptionFieldSize = {100, 14};
	Console::FULLCOLOR descColor = Console::getFullColor(Console::Color::BRIGHT_WHITE, Console::Color::BLUE);

	//Record Fields
	descTitle = new TextField(descSize, "Tytul");
	descTitle->move({0, 0});
	descTitle->setTextColor(descColor);

	title = new TextField(fieldSize);
	title->move({20, 0});

	descAuthor = new TextField(descSize, "Autor");
	descAuthor->move({0, 2});
	descAuthor->setTextColor(descColor);

	author = new TextField(fieldSize);
	author->move({20, 2});

	descDescription = new TextField(descriptionDescSize, "Opis");
	descDescription->move({0, 4});
	descDescription->setTextColor(descColor);

	description = new TextField(descriptionFieldSize);
	description->move({20, 4});

	descState = new TextField(descSize, "Status");
	descState->move({0, 18});
	descState->setTextColor(descColor);

	state = new TextField(fieldSize);
	state->move({20, 18});

	descSignature = new TextField(descSize, "Sygnatura");
	descSignature->move({0, 20});
	descSignature->setTextColor(descColor);

	signature = new TextField(fieldSize);
	signature->move({20, 20});

	//Input field
	input = new InputField({consoleHandle->getSize().X, 1});
	input->setTextColor(Console::getFullColor(Console::Color::BRIGHT_WHITE, Console::Color::GRAY));
	input->setActiveColor(Console::getFullColor(Console::Color::BLACK, Console::Color::WHITE));
	input->move({0, (short) (consoleHandle->getSize().Y - 4)});
	input->preText = "[E] - Edytuj";
	input->emptyText = "";

	//Instructions
	instructions = new TextField({consoleHandle->getSize().X, 2});
	instructions->text = "Ogolne:     [Strzalka w lewo] - Powrot do listy\n            [Strzalka w gore / dol / ENTER] - zmiana pola podczas wprowadzania";
	instructions->setTextColor(Console::getFullColor(Console::Color::BRIGHT_WHITE, Console::Color::BLUE));
	instructions->move({0, (short) (consoleHandle->getSize().Y - 3)});

	instructions2 = new TextField({consoleHandle->getSize().X, 1});
	instructions2->text = "Rekord:     [S] - Zmien status    [C] - Kopiuj     [E] - Edytuj    [DEL] - Usun";
	instructions2->setTextColor(Console::getFullColor(Console::Color::BRIGHT_WHITE, Console::Color::PURPLE));
	instructions2->move({0, (short) (consoleHandle->getSize().Y - 1)});

	addRenderable(input);
	addRenderable(descTitle);
	addRenderable(title);
	addRenderable(descAuthor);
	addRenderable(author);
	addRenderable(descDescription);
	addRenderable(description);
	addRenderable(descState);
	addRenderable(state);
	addRenderable(descSignature);
	addRenderable(signature);
	addRenderable(instructions);
	addRenderable(instructions2);
}
