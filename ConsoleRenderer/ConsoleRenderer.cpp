//
// Created by rd on 20.05.2019.
//

#include "ConsoleRenderer.hpp"

ConsoleRenderer::ConsoleRenderer(COORD size_) {
	resize(size_);
}

void ConsoleRenderer::resize(COORD size_) {
	this->size = size_;
	Console::prepareBuffer(currentFrame, size);
	Console::prepareBuffer(nextFrame, size);
}

void ConsoleRenderer::addRenderable(Renderable *r) {
	renderables.push_back(r);
}

void ConsoleRenderer::prepareNextFrame() {
	//Cleanup next frame buffer
	Console::prepareBuffer(nextFrame, size);

	//Copy contents to screenBuffer
	for (Renderable *r : renderables) {
		Console::copyBufferContentsToBuffer(nextFrame, *r->getBuffer(), r->getPosition());
	}
}
