//
// Created by rd on 20.05.2019.
//

#ifndef LIBRARYDB_RENDERABLE_HPP
#define LIBRARYDB_RENDERABLE_HPP

#include <utility>
#include "Console.hpp"

//TODO: Render on demand (change) SUPPORT
class Renderable {
protected:
	COORD size{}, position{};

	Console::RICHTEXT buffer;

	Console::FULLCOLOR
			textColor = Console::COLOR_DEFAULT,
			borderColor = Console::COLOR_DEFAULT;

	bool needUpdate = true;

	virtual void render() = 0;

	void emptyBuffer();

public:
	enum class TextAlign {
		LEFT, CENTER, RIGHT
	};

	explicit Renderable(COORD size_, COORD position_ = {0, 0});

	void resize(COORD size_);

	void move(COORD position_);

	COORD getSize() const;

	COORD getPosition() const;

	Console::RICHTEXT *getBuffer();

	void setTextColor(Console::FULLCOLOR textColor_);

	void setBorderColor(Console::FULLCOLOR borderColor_);
};


#endif //LIBRARYDB_RENDERABLE_HPP
