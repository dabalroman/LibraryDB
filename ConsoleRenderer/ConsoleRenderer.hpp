//
// Created by rd on 20.05.2019.
//

#ifndef LIBRARYDB_CONSOLERENDERER_HPP
#define LIBRARYDB_CONSOLERENDERER_HPP


#include <vector>
#include "Console.hpp"
#include "Renderable.hpp"

//TODO: RENDER WHOLE SCREEN TO CONSOLE
class ConsoleRenderer {
private:
	COORD size{};
	Console *console;
	Console::RICHTEXT currentFrame, nextFrame;

	vector<Renderable *> renderables;

public:
	explicit ConsoleRenderer(Console &console_);

	/**
	 * Resize console render
	 * @param size_ New console render size
	 */
	void resize(COORD size_);

	/**
	 * Add renderable to render query
	 * @param r Renderable
	 */
	void addRenderable(Renderable *r);

	/**
	 * Render buffer to console screen
	 */
	void render();

private:
	/**
	 * Create next frame to render
	 */
	void prepareNextFrame();
};


#endif //LIBRARYDB_CONSOLERENDERER_HPP
