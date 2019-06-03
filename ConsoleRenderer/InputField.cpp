#include <utility>

//
// Created by rd on 03.06.2019.
//

#include "InputField.hpp"
#include "Buffer.hpp"
#include "../Utils.hpp"

InputField::InputField(COORD size_, string text_, TextAlign textAlign_) : TextField(size_, std::move(text_),
                                                                                    textAlign_) {}

void InputField::render() {
	if (!needUpdate) {
		return;
	}

	emptyBuffer();
	Buffer::fill(buffer, ' ', textColor);
	Buffer::insertString(buffer, ">> " + text, {0, 0}, textColor);
}

void InputField::insert(char c) {
	if (c < 32 || c > 126) {
		return;
	}

	text += c;
}

void InputField::backspace() {
	text = cropString(text, text.length() - 1);
}