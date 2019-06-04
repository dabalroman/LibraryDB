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
	Buffer::fill(buffer, ' ', isActive() ? activeColor : textColor);
	Buffer::insertString(buffer,
	                     (isActive() ? activePreText : preText) +
	                     ((text.length() == 0 && !isActive()) ? emptyText : text) +
	                     (isActive() ? activePostText : postText),
	                     {0, 0},
	                     isActive() ? activeColor : textColor);
}

void InputField::insert(const char c) {
	if (c < 32 || c > 126) {
		return;
	}

	text += c;
}

void InputField::backspace() {
	text = cropString(text, text.length() - 1);
}

bool InputField::isActive() const {
	return active;
}

void InputField::setActive(bool active_) {
	InputField::active = active_;
}

void InputField::setActiveColor(Console::FULLCOLOR activeColor_) {
	activeColor = activeColor_;
	needUpdate = true;
}