//
// Created by rd on 04.06.2019.
//

#ifndef LIBRARYDB_LISTSCREEN_HPP
#define LIBRARYDB_LISTSCREEN_HPP


#include "ConsoleRenderer/Screen.hpp"
#include "ConsoleRenderer/InputField.hpp"
#include "ConsoleRenderer/DataListRenderable.hpp"
#include "DataKeeper.hpp"

class ListScreen : public Screen {
public:
	ListScreen(Console &consoleHandle_, DataKeeper &dataHandle_);

	InputField *input;
	DataListRenderable *booksList;
	TextField *instructions, *instructions2, *sortInstructions, *debug;

	int handleInput(KEY_EVENT_RECORD c) override;
};


#endif //LIBRARYDB_LISTSCREEN_HPP
