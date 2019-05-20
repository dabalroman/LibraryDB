//
// Created by rd on 20.05.2019.
//

#include "Renderable.hpp"

void Renderable::prepareBuffer() {
	buffer.clear();
	buffer.resize(size.Y);

	ConsoleRenderer::RICHCHAR rc = {' ', Console::COLOR_DEFAULT};

	for (ConsoleRenderer::RICHLINE &sr : buffer) {
		sr.resize(size.X, rc);
	}

	cout << "Buffer prepared: " << buffer.size() << " x " << buffer[0].size() << endl;
}

Renderable::Renderable(COORD size) {
	cout << "Renderable constructor" << endl;
	this->size = size;

	prepareBuffer();
}

void Renderable::resize(COORD size_) {
	this->size = size_;
	prepareBuffer();
}

const ConsoleRenderer::RICHTEXT *Renderable::getBuffer() {
	render();
	return &buffer;
}


