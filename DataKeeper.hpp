#ifndef LIBRARYDB_DATAKEEPER_HPP
#define LIBRARYDB_DATAKEEPER_HPP

#include <vector>
#include "Record.hpp"
#include "DataList.hpp"

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
	DataList data;

	DataKeeper();

	int loadFromFile();

	int saveToFile();
};


#endif //LIBRARYDB_DATAKEEPER_HPP
