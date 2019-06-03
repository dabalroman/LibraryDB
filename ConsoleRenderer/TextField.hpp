//
// Created by rd on 20.05.2019.
//

#ifndef LIBRARYDB_TEXTFIELD_HPP
#define LIBRARYDB_TEXTFIELD_HPP

#include "Renderable.hpp"

using namespace std;

class TextField : public Renderable {
protected:
	void render() override;

	TextAlign textAlign;

public:
	string text;

	/**
	 * Create TextField
	 * @param size_
	 * @param text_
	 * @param textAlign_
	 */
	explicit TextField(COORD size_, string text_ = "", TextAlign textAlign_ = TextAlign::LEFT);
};


#endif //LIBRARYDB_TEXTFIELD_HPP
