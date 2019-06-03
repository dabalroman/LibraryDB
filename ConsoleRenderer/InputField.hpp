//
// Created by rd on 03.06.2019.
//

#ifndef LIBRARYDB_INPUTFIELD_HPP
#define LIBRARYDB_INPUTFIELD_HPP


#include "InputField.hpp"
#include "TextField.hpp"

class InputField : public TextField {
protected:
	void render() override;

public:
	/**
	 * Create InputField
	 * @param size_
	 * @param text_
	 * @param textAlign_
	 */
	explicit InputField(COORD size_, string text_ = "", TextAlign textAlign_ = TextAlign::LEFT);

	/**
	 * Insert char
	 * @param c Char
	 */
	void insert(const char c);

	/**
	 * Remove char
	 */
	void backspace();
};

#endif //LIBRARYDB_INPUTFIELD_HPP
