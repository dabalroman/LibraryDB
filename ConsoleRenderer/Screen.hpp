//
// Created by rd on 03.06.2019.
//

#ifndef LIBRARYDB_SCREEN_HPP
#define LIBRARYDB_SCREEN_HPP


#include "Renderable.hpp"

class Screen {
private:
	vector<Renderable *> renderables;

public:
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
};


#endif //LIBRARYDB_SCREEN_HPP
