//
// Created by rd on 04.06.2019.
//

#include <sstream>
#include "DetailsScreen.hpp"

int DetailsScreen::handleInput(KEY_EVENT_RECORD c) {
	//Current record
	Record *r = dataHandle->data.getActiveRecord();

	//Debug
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

		return RETURNCODES::DEFAULT;
	}

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
			textInputMode = true;
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

	//Update fields
	title->text = r->name;
	author->text = r->author;
	description->text = r->description;
	signature->text = r->signature;

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
	COORD descSize = {18, 1};
	COORD fieldSize = {100, 1};
	COORD descriptionDescSize = {18, 10};
	COORD descriptionFieldSize = {100, 10};
	Console::FULLCOLOR descColor = Console::getFullColor(Console::Color::BRIGHT_WHITE, Console::Color::BLUE);

	//DEBUG
	debug = new TextField(descSize, " ??? ");
	debug->move({100, (short) (consoleHandle->getSize().Y - 1)});

	//Record Fields
	descTitle = new TextField(descSize, "Tytul");
	descTitle->move({0, 0});
	descTitle->setTextColor(descColor);

	title = new TextField(fieldSize);
	title->move({20, 0});

	descAuthor = new TextField(descSize, "Autor");
	descAuthor->move({0, 1});
	descAuthor->setTextColor(descColor);

	author = new TextField(fieldSize);
	author->move({20, 1});

	descDescription = new TextField(descriptionDescSize, "Opis");
	descDescription->move({0, 2});
	descDescription->setTextColor(descColor);

	description = new TextField(descriptionFieldSize);
	description->move({20, 2});

	descState = new TextField(descSize, "Status");
	descState->move({0, 12});
	descState->setTextColor(descColor);

	state = new TextField(fieldSize);
	state->move({20, 12});

	descSignature = new TextField(descSize, "Sygnatura");
	descSignature->move({0, 13});
	descSignature->setTextColor(descColor);

	signature = new TextField(fieldSize);
	signature->move({20, 13});

	//Input field
	input = new InputField({consoleHandle->getSize().X, 1});
	input->setTextColor(Console::getFullColor(Console::Color::BRIGHT_WHITE, Console::Color::GRAY));
	input->setActiveColor(Console::getFullColor(Console::Color::BLACK, Console::Color::WHITE));
	input->move({0, (short) (consoleHandle->getSize().Y - 4)});
	input->preText = "TODO";

	//Instructions
	instructions = new TextField({consoleHandle->getSize().X, 1});
	instructions->text = "Ogolne:     [Strzalka w lewo] - Powrot do listy";
	instructions->setTextColor(Console::getFullColor(Console::Color::BRIGHT_WHITE, Console::Color::BLUE));
	instructions->move({0, (short) (consoleHandle->getSize().Y - 3)});

	instructions2 = new TextField({consoleHandle->getSize().X, 1});
	instructions2->text = "Rekord:     [S] - Zmien status    [C] - Kopiuj    [E] - Edytuj    [DEL] - Usun";
	instructions2->setTextColor(Console::getFullColor(Console::Color::BRIGHT_WHITE, Console::Color::PURPLE));
	instructions2->move({0, (short) (consoleHandle->getSize().Y - 2)});

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
	addRenderable(debug);
}
