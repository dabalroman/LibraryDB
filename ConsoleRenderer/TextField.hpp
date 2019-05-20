#include <utility>

//
// Created by rd on 20.05.2019.
//

#ifndef LIBRARYDB_TEXTFIELD_HPP
#define LIBRARYDB_TEXTFIELD_HPP

#include <string>
#include "Renderable.hpp"
#include "ConsoleRenderer.hpp"

using namespace std;

class TextField : public Renderable {
protected:
	void render() override;

public:
	string text;

	explicit TextField(COORD size, string text = "");
};


#endif //LIBRARYDB_TEXTFIELD_HPP
