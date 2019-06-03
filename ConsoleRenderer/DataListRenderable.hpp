//
// Created by rd on 02.06.2019.
//

#ifndef LIBRARYDB_DATALISTRENDERABLE_HPP
#define LIBRARYDB_DATALISTRENDERABLE_HPP


#include "Renderable.hpp"
#include "../DataList.hpp"

class DataListRenderable : public Renderable {
protected:
	void render() override;

	DataList *dataListPointer;

	struct {
		int lp = 4;
		int signature = 20;
		int name = 40;
		int author = 30;
		int state = 20;
	} dataFieldLength;

	Console::FULLCOLOR activeRecordColor, defaultRecordColor, legendColor;

public:
	/**
	 * Create DataListRenderable
	 * @param size_
	 * @param dl
	 */
	DataListRenderable(COORD size_, DataList *dl);
};


#endif //LIBRARYDB_DATALISTRENDERABLE_HPP
