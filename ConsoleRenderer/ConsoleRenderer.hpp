//
// Created by rd on 20.05.2019.
//

#ifndef LIBRARYDB_CONSOLERENDERER_HPP
#define LIBRARYDB_CONSOLERENDERER_HPP


#include <vector>
#include "Console.hpp"
#include "Screen.hpp"

class ConsoleRenderer {
private:
	COORD size{};
	Console *console;
	Console::RICHTEXT currentFrame, nextFrame;

	vector<Screen *> screens;
	int activeScreen = 0;

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
	void addScreen(Screen *s);

	/**
	 * Render buffer to console screen
	 */
	void render();

	/**
	 * Set active screen
	 * @param s Screen ID
	 */
	void setActiveScreen(int s);

	/**
	 * Get active screen
	 * @return Screen ID
	 */
	int getActiveScreen() const;

private:
	/**
	 * Create next frame to render
	 */
	void prepareNextFrame();
};


#endif //LIBRARYDB_CONSOLERENDERER_HPP
