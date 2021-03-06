#ifndef LIBRARYDB_TEXTFIELD_HPP
#define LIBRARYDB_TEXTFIELD_HPP

#include "../Renderable.hpp"

using namespace std;

class TextField : public Renderable {
protected:
	void render() override;

public:
	string text;

	/**
	 * Create TextField
	 * @param size_
	 * @param text_
	 * @param textAlign_
	 */
	explicit TextField(COORD size_, string text_ = "");
};


#endif //LIBRARYDB_TEXTFIELD_HPP
