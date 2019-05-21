//
// Created by rd on 20.05.2019.
//

#ifndef LIBRARYDB_RENDERABLE_HPP
#define LIBRARYDB_RENDERABLE_HPP


#include "Console.hpp"

//TODO: Render on demand (change) SUPPORT
class Renderable {
protected:
	COORD size{};
	COORD position{};

	Console::RICHTEXT buffer;

	virtual void render() = 0;

public:
	enum class TextAlign {
		LEFT, CENTER, RIGHT
	};

	Renderable(COORD size_, COORD position_ = {0, 0});

	void resize(COORD size_);

	void move(COORD position_);

	COORD getSize();

	COORD getPosition();

	Console::RICHTEXT *getBuffer();
};


#endif //LIBRARYDB_RENDERABLE_HPP
