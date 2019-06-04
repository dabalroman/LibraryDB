#ifndef LIBRARYDB_RENDERABLE_HPP
#define LIBRARYDB_RENDERABLE_HPP

#include <utility>
#include "Console.hpp"

class Renderable {
protected:
	COORD size{}, position{};

	Console::RICHTEXT buffer;

	Console::FULLCOLOR
			textColor = Console::COLOR_DEFAULT,
			borderColor = Console::COLOR_DEFAULT;

	bool needUpdate = true;

	/**
	 * Render object
	 */
	virtual void render() = 0;

	/**
	 * Flush buffer content
	 */
	void emptyBuffer();

public:
	enum class TextAlign {
		LEFT, CENTER, RIGHT
	};

	/**
	 * Create Renderable object
	 * @param size_ Size
	 * @param position_ Position
	 */
	explicit Renderable(COORD size_, COORD position_ = {0, 0});

	/**
	 * Set size
	 * @param size_ New size
	 */
	void resize(COORD size_);

	/**
	 * Set position on screen
	 * @param position_ New position
	 */
	void move(COORD position_);

	/**
	 * Returns size
	 * @return COORD Size
	 */
	COORD getSize() const;

	/**
	 * Returns position
	 * @return COORD Position
	 */
	COORD getPosition() const;

	/**
	 * Returns rendered buffer
	 * @return RICHTEXT Rendered buffer
	 */
	Console::RICHTEXT *getBuffer();

	/**
	 * Set text color
	 * @param textColor_ FULLCOLOR
	 */
	void setTextColor(Console::FULLCOLOR textColor_);

	/**
	 * Set border color
	 * @param borderColor_ FULLCOLOR
	 */
	void setBorderColor(Console::FULLCOLOR borderColor_);
};


#endif //LIBRARYDB_RENDERABLE_HPP
