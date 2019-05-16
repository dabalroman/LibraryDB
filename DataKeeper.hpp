//
// Created by rd on 16/05/2019.
//

#ifndef LIBRARYDB_DATAKEEPER_HPP
#define LIBRARYDB_DATAKEEPER_HPP

#include <vector>
#include "Record.hpp"

class DataKeeper {
	vector<Record> rawData;
	vector<Record *> records;

public:
	enum class SortBy : short {
		Name = 0,
		Author = 1,
		Signature = 2,
		State = 3,
	};

	void loadFromFile();

	void saveToFile();

	vector<Record *> getRecords();

	void sort(SortBy sortby);
};


#endif //LIBRARYDB_DATAKEEPER_HPP
