//
// Created by rd on 20.05.2019.
//

#include "Renderable.hpp"


Renderable::Renderable(COORD size_, COORD position_) {
	cout << "Renderable constructor" << endl;
	position = position_;
	resize(size_);
}

void Renderable::move(COORD position_) {
	position = position_;
}

void Renderable::resize(COORD size_) {
	size = size_;
	Console::prepareBuffer(buffer, size);
}

COORD Renderable::getSize() {
	return size;
}

COORD Renderable::getPosition() {
	return position;
}

Console::RICHTEXT *Renderable::getBuffer() {
	render();
	return &buffer;
}


