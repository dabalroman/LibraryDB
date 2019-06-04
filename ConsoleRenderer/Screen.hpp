#ifndef LIBRARYDB_SCREEN_HPP
#define LIBRARYDB_SCREEN_HPP


#include "Renderable.hpp"
#include "../DataKeeper.hpp"

class Screen {
protected:
	Console *consoleHandle;
	DataKeeper *dataHandle;
	vector<Renderable *> renderables;
	bool textInputMode = false;

public:
	enum RETURNCODES : int {
		DETAILS_SCREEN = 1,
		LIST_SCREEN = 0,
		DEFAULT = -1,
		EXIT = -2
	};

	/**
	 * Create screen
	 * @param consoleHandle_ Console handle
	 * @param dataHandle_ Data Handle
	 */
	Screen(Console &consoleHandle_, DataKeeper &dataHandle_);

	/**
	 * Add renderable to screen
	 * @param r Renderable
	 */
	void addRenderable(Renderable *r);

	/**
	 * Get renderables
	 * @return renderables
	 */
	vector<Renderable *> *getRenderables();

	/**
	 * Handle user input
	 * @param c Input
	 */
	virtual int handleInput(KEY_EVENT_RECORD c) = 0;
};


#endif //LIBRARYDB_SCREEN_HPP
