#ifndef LIBRARYDB_DATAKEEPER_HPP
#define LIBRARYDB_DATAKEEPER_HPP

#include <vector>
#include "Record.hpp"

class DataKeeper {
	const string DATA_FILE = "data.txt";
	const char DATA_DELIMITER = ';';
	const int DATA_INPUT_STRINGS_AMOUNT = 5;

	enum class FileDataOrder : int {
		Name = 0,
		Author = 1,
		Description = 2,
		Signature = 3,
		State = 4
	};

public:
	vector<Record *> records;

	enum class SortBy : int {
		Name = 0,
		Author = 1,
		Signature = 2,
		State = 3,
	};

	DataKeeper() = default;

	int loadFromFile();

	int saveToFile();

	vector<Record *> *getRecords();

	void sort(SortBy sortby);
};


#endif //LIBRARYDB_DATAKEEPER_HPP
