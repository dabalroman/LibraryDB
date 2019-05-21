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
	COORD size;
	Console::RICHTEXT currentFrame, nextFrame;

	vector<Renderable *> renderables;

public:
	ConsoleRenderer(COORD size_);

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
	 * Create next frame to render
	 */
	void prepareNextFrame();
};


#endif //LIBRARYDB_CONSOLERENDERER_HPP
