#ifndef LIBRARYDB_DETAILSSCREEN_HPP
#define LIBRARYDB_DETAILSSCREEN_HPP


#include "../DataKeeper.hpp"
#include "../ConsoleRenderer/Screen.hpp"
#include "../ConsoleRenderer/Renderables/InputField.hpp"
#include "../ConsoleRenderer/Renderables/TextField.hpp"

class DetailsScreen : public Screen {
private:
	int currentInputFiled = 0, prevInputField = 0;
public:
	InputField *input;
	TextField *descTitle, *title,
			*descAuthor, *author,
			*descDescription, *description,
			*descState, *state,
			*descSignature, *signature,
			*instructions, *instructions2;

	/**
	 * Create Details Screen
	 * @param consoleHandle_ Console Handle
	 * @param dataHandle_ Data Handle
	 */
	DetailsScreen(Console &consoleHandle_, DataKeeper &dataHandle_);

	/**
	 * Handle user input
	 * @param c user input
	 * @return RETURNCODE (change screen or stay)
	 */
	int handleInput(KEY_EVENT_RECORD c) override;
};


#endif //LIBRARYDB_DETAILSSCREEN_HPP
