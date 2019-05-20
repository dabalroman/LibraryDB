//
// Created by rd on 20.05.2019.
//

#ifndef LIBRARYDB_RENDERABLE_HPP
#define LIBRARYDB_RENDERABLE_HPP


#include "ConsoleRenderer.hpp"

class Renderable {
protected:
	COORD size{};

	ConsoleRenderer::RICHTEXT buffer;

	void prepareBuffer();

	virtual void render() = 0;

public:
	Renderable(COORD size);

	void resize(COORD size_);

	const ConsoleRenderer::RICHTEXT *getBuffer();
};


#endif //LIBRARYDB_RENDERABLE_HPP
