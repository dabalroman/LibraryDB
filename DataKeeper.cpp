#include <fstream>
#include <iostream>
#include <conio.h>
#include "DataKeeper.hpp"
#include "Utils.hpp"

using namespace std;

DataKeeper::DataKeeper() {
	data = DataList();
}

int DataKeeper::loadFromFile() {
	//Open file
	fstream file;
	file.open(DATA_FILE, ios::in);

	if (file.good()) {
		string rawInput;

		//Read data
		while (!file.eof()) {
			getline(file, rawInput);

			//Last line?
			if (rawInput == "\n") {
				continue;
			}

			//Split data
			auto input = splitString(rawInput, DATA_DELIMITER);

			//Wrong input size?
			if (input.size() != DATA_INPUT_STRINGS_AMOUNT) {
				continue;
			}

			//Push data to record
			data.addRecord(new Record(
					input[(int) FileDataOrder::Title],
					input[(int) FileDataOrder::Author],
					input[(int) FileDataOrder::Description],
					input[(int) FileDataOrder::Signature],
					static_cast<Record::State>(
							stoi(input[(int) FileDataOrder::State])
					)));
		}

	} else {
		return 0;
	}

	file.close();
	return 1;
}

int DataKeeper::saveToFile() {
	fstream file;
	file.open(DATA_FILE, ios::out | ios::trunc);

	if (file.good()) {
		data.setActiveElementByID(0);

		//Save data to file
		do {
			Record *r = data.getActiveRecord();
			file << r->title << ';'
			     << r->author << ';'
			     << r->description << ';'
			     << r->signature << ';'
			     << r->getIntState() << '\n';
		} while (!data.next());

	} else {
		return 0;
	}

	file.close();
	return 1;
}