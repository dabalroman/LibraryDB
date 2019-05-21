//
// Created by rd on 20.05.2019.
//

#include <utility>
#include "TextField.hpp"

using namespace std;

void TextField::render() {
	cout << "TextField Render()" << endl;

	//TODO: ALIGN SUPPORT

	Console::createBufferBorder(buffer, Console::getColor(Console::Color::LIGHT_BLUE));
	Console::insertStringIntoBuffer(buffer, text, {2, 1}, Console::getColor(Console::Color::LIGHT_RED));
}

TextField::TextField(COORD size_, string text_, TextAlign textAlign_) : Renderable(size_) {
	cout << "Text field constructor" << endl;
	textAlign = textAlign_;
	text = std::move(text_);

	if (size.X < 10) {
		size.X = 10;
	}

	if (size.Y < 3) {
		size.Y = 3;
	}
}


