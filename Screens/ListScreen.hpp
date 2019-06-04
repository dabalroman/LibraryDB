#ifndef LIBRARYDB_LISTSCREEN_HPP
#define LIBRARYDB_LISTSCREEN_HPP


#include "../DataKeeper.hpp"
#include "../ConsoleRenderer/Screen.hpp"
#include "../ConsoleRenderer/Renderables/InputField.hpp"
#include "../ConsoleRenderer/Renderables/DataListRenderable.hpp"

class ListScreen : public Screen {
public:
	InputField *input;
	DataListRenderable *booksList;
	TextField *instructions, *sortInstructions;

	/**
	 * Create List Screen
	 * @param consoleHandle_ Console Handle
	 * @param dataHandle_ Data Handle
	 */
	ListScreen(Console &consoleHandle_, DataKeeper &dataHandle_);

	/**
	 * Handle user input
	 * @param c user input
	 * @return RETURNCODE (change screen or stay)
	 */
	int handleInput(KEY_EVENT_RECORD c) override;
};


#endif //LIBRARYDB_LISTSCREEN_HPP
