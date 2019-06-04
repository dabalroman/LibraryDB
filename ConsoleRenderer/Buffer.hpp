#ifndef LIBRARYDB_BUFFER_HPP
#define LIBRARYDB_BUFFER_HPP

#include "Console.hpp"

namespace Buffer {
	/**
	 * Create given size buffer filled with default values
	 * @param buffer Reference to buffer
	 * @param size Buffer target size
	 */
	void prepare(Console::RICHTEXT &buffer, COORD size);

	/**
	 * Copy buffer content to another buffer with position offset
	 * @param target Buffer to copy to
	 * @param source Buffer to copy from
	 * @param offset Source buffer offset
	 */
	void copyContent(Console::RICHTEXT &target, Console::RICHTEXT &source, COORD offset = {0, 0});

	/**
	 * Inserts string into buffer at given position
	 * @param buffer Reference to buffer
	 * @param s String
	 * @param offset String target position
	 * @param color String target color
	 */
	void insertString(Console::RICHTEXT &buffer, string s, COORD offset = {0, 0},
	                  Console::FULLCOLOR color = Console::COLOR_DEFAULT);

	/**
	 * Create border around renderable
	 * @param buffer Reference to buffer
	 * @param color Color
	 */
	void createBorder(Console::RICHTEXT &buffer, Console::FULLCOLOR color = Console::COLOR_DEFAULT);

	/**
	 * Fill buffer with char
	 * @param buffer Reference to buffer
	 * @param c Char
	 * @param color Color
	 */
	void fill(Console::RICHTEXT &buffer, char c, Console::FULLCOLOR color = Console::COLOR_DEFAULT);
}

#endif //LIBRARYDB_BUFFER_HPP
