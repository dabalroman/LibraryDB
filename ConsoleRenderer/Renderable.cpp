#include "Renderable.hpp"
#include "Buffer.hpp"


Renderable::Renderable(COORD size_, COORD position_) {
	position = position_;
	resize(size_);
}

void Renderable::move(COORD position_) {
	position_.X = max(position_.X, (short) 0);
	position_.Y = max(position_.Y, (short) 0);

	position = position_;
	needUpdate = true;
}

void Renderable::resize(COORD size_) {
	size = size_;
	emptyBuffer();
	needUpdate = true;
}

COORD Renderable::getSize() const {
	return size;
}

COORD Renderable::getPosition() const {
	return position;
}

Console::RICHTEXT *Renderable::getBuffer() {
	render();
	return &buffer;
}

void Renderable::setTextColor(Console::FULLCOLOR textColor_) {
	textColor = textColor_;
	needUpdate = true;
}

void Renderable::setBorderColor(Console::FULLCOLOR borderColor_) {
	borderColor = borderColor_;
	needUpdate = true;
}

void Renderable::emptyBuffer() {
	Buffer::prepare(buffer, size);
}


