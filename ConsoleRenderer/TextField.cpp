//
// Created by rd on 20.05.2019.
//

#include <utility>
#include "TextField.hpp"

using namespace std;

void TextField::render() {
	ConsoleRenderer::RICHCHAR rc = {'-', Console::COLOR_DEFAULT};

	ConsoleRenderer::insertStringIntoBuffer(buffer, text, {0, 1}, Console::getColor(Console::Color::LIGHT_RED));
	fill(buffer.at(0).begin(), buffer.at(0).end(), rc);
	fill(buffer.at(2).begin(), buffer.at(2).end(), rc);
}

TextField::TextField(COORD size, string text) : Renderable(size) {
	cout << "Text field constructor" << endl;
	this->text = std::move(text);
}


