//
// Created by rd on 20.05.2019.
//

#include "TextField.hpp"
#include "Buffer.hpp"

using namespace std;

void TextField::render() {
	if (!needUpdate) {
		return;
	}

	//TODO: ALIGN SUPPORT
	emptyBuffer();
	Buffer::createBorder(buffer, borderColor);
	Buffer::insertString(buffer, text, {2, 1}, textColor);
}

TextField::TextField(COORD size_, string text_, TextAlign textAlign_) : Renderable(size_) {
	textAlign = textAlign_;
	text = std::move(text_);

	if (size.X < 10) {
		size.X = 10;
	}

	if (size.Y < 3) {
		size.Y = 3;
	}
}


