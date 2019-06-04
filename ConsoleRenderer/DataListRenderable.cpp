//
// Created by rd on 02.06.2019.
//

#include <sstream>
#include <iomanip>
#include "DataListRenderable.hpp"
#include "Buffer.hpp"
#include "../Utils.hpp"

DataListRenderable::DataListRenderable(COORD size_, DataList *dl) : Renderable(size_) {
	dataListPointer = dl;

	if (size.X < 10) {
		size.X = 10;
	}

	if (size.Y < 3) {
		size.Y = 3;
	}

	activeRecordColor = Console::getFullColor(Console::Color::BLACK, Console::Color::BRIGHT_WHITE);
	defaultRecordColor = Console::COLOR_DEFAULT;
	legendColor = Console::getFullColor(Console::Color::YELLOW);
}

void DataListRenderable::render() {
	if (!needUpdate) {
		return;
	}

	emptyBuffer();

	//Legend
	stringstream ss;
	ss << " ### "
	   << left << setw(dataFieldLength.name + 1) << "Tytul pozycji"
	   << setw(dataFieldLength.author + 1) << "Autor"
	   << setw(dataFieldLength.state + 1) << "Status"
	   << setw(dataFieldLength.signature + 1) << "Sygnatura";

	Buffer::insertString(buffer, ss.str(), {0, 0}, legendColor);

	//Create rows
	string textState;
	int rowsAmount = 0;
	for (int i = 0; i < dataListPointer->getSize(); ++i) {
		//Do not display if hidden
		if (dataListPointer->getRecord(i)->hidden) {
			continue;
		}

		//State
		switch (dataListPointer->getRecord(i)->getState()) {
			case Record::State::Available:
				textState = "Dostepna";
				break;
			case Record::State::Lend:
				textState = "Wypozyczona";
				break;
			case Record::State::Unavailable:
				textState = "Niedostepna";
				break;
		}

		//Crate list row
		ss.str(" ");
		ss << right << setw(dataFieldLength.lp) << i + 1 << " "
		   << left << setw(dataFieldLength.name + 1)
		   << cropString(dataListPointer->getRecord(i)->name, dataFieldLength.name)
		   << setw(dataFieldLength.author + 1)
		   << cropString(dataListPointer->getRecord(i)->author, dataFieldLength.author)
		   << setw(dataFieldLength.state + 1)
		   << textState
		   << setw(dataFieldLength.signature + 1)
		   << cropString(dataListPointer->getRecord(i)->signature, dataFieldLength.signature);

		Buffer::insertString(buffer, ss.str(), {0, (short) ((rowsAmount++) + 1)},
		                     (dataListPointer->getActiveElement() == i) ? activeRecordColor : defaultRecordColor);
	}
}
