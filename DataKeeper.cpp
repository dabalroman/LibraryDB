//
// Created by rd on 16/05/2019.
//

#include <fstream>
#include <iostream>
#include <conio.h>
#include "DataKeeper.hpp"
#include "Utils.hpp"

using namespace std;

int DataKeeper::loadFromFile() {
	fstream file;
	file.open(DATA_FILE, ios::in);

	if (file.good()) {

		string rawInput;

		while (!file.eof()) {
			getline(file, rawInput);

			if (rawInput == "\n") {
				continue;
			}

			auto input = splitString(rawInput, DATA_DELIMITER);

			if (input.size() != DATA_INPUT_STRINGS_AMOUNT) {
				continue;
			}

			records.push_back(new Record(
					input[(int) FileDataOrder::Name],
					input[(int) FileDataOrder::Author],
					input[(int) FileDataOrder::Description],
					input[(int) FileDataOrder::Signature],
					static_cast<Record::State>(
							stoi(input[(int) FileDataOrder::State])
					)
			));
		}

	} else {
		return 0;
	}

	file.close();
	return 1;
}

vector<Record *> *DataKeeper::getRecords() {
	return &records;
}

int DataKeeper::saveToFile() {
	fstream file;
	file.open(DATA_FILE, ios::out | ios::trunc);

	if (file.good()) {

		for (auto r : records) {
			file << r->getName() << ';'
			     << r->getAuthor() << ';'
			     << r->getDescription() << ';'
			     << r->getSignature() << ';'
			     << static_cast<int>(r->getState()) << '\n';
		}

	} else {
		return 0;
	}

	file.close();
	return 1;
}