//
// Created by rd on 20.05.2019.
//

#include "ConsoleRenderer.hpp"
#include "Buffer.hpp"

ConsoleRenderer::ConsoleRenderer(Console &console_) {
	console = &console_;
	resize(console->getSize());
	console->cls();
}

void ConsoleRenderer::resize(COORD size_) {
	this->size = size_;
	Buffer::prepare(currentFrame, size);
	Buffer::prepare(nextFrame, size);
}

void ConsoleRenderer::addRenderable(Renderable *r) {
	renderables.push_back(r);
}

void ConsoleRenderer::prepareNextFrame() {
	//Cleanup next frame buffer
	Buffer::prepare(nextFrame, size);

	//Copy contents to nextFrame
	for (Renderable *r : renderables) {
		Buffer::copyContent(nextFrame, *r->getBuffer(), r->getPosition());
	}
}

void ConsoleRenderer::render() {
	prepareNextFrame();

	//Update only changed fields in screen buffer and display to console
	int updatedChars = 0;
	COORD lastCursorPosition = {0, 0};
	for (short y = 0; y < currentFrame.size(); y++) {
		for (short x = 0; x < currentFrame[0].size(); x++) {
			//If different
			if (currentFrame[y][x] != nextFrame[y][x]) {
				//Set cursor position if not at near left char
				if (lastCursorPosition.X != x - 1 || lastCursorPosition.Y != y) {
					console->setCursorPosition(x, y);
				}

				//Update color
				if (console->getCurrentColor() != nextFrame[y][x].color) {
					console->setColor(nextFrame[y][x].color);
				}

				//Print char
				cout << nextFrame[y][x].c;

				//Apply changes
				currentFrame[y][x] = nextFrame[y][x];
				lastCursorPosition = {x, y};
				updatedChars++;
			}
		}
	}

	//Debug info
	COORD consoleSize = console->getSize();
	console->setColor(Console::Color::AQUA);
	console->setCursorPosition(0, consoleSize.Y);
	cout << "                     ";
	console->setCursorPosition(0, consoleSize.Y);
	cout << "Updated chars: " << updatedChars;
}
