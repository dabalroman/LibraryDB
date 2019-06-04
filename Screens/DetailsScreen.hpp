//
// Created by rd on 04.06.2019.
//

#ifndef LIBRARYDB_DETAILSSCREEN_HPP
#define LIBRARYDB_DETAILSSCREEN_HPP


#include "../DataKeeper.hpp"
#include "../ConsoleRenderer/Screen.hpp"
#include "../ConsoleRenderer/Renderables/InputField.hpp"
#include "../ConsoleRenderer/Renderables/TextField.hpp"

class DetailsScreen : public Screen {
public:
	DetailsScreen(Console &consoleHandle_, DataKeeper &dataHandle_);

	InputField *input;
	TextField *descTitle, *title,
			*descAuthor, *author,
			*descDescription, *description,
			*descState, *state,
			*descSignature, *signature,
			*debug, *instructions, *instructions2;

	int handleInput(KEY_EVENT_RECORD c) override;
};


#endif //LIBRARYDB_DETAILSSCREEN_HPP
