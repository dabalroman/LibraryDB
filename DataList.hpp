//
// Created by rd on 02.06.2019.
//

#ifndef LIBRARYDB_DATALIST_HPP
#define LIBRARYDB_DATALIST_HPP


#include <vector>
#include <algorithm>
#include "Record.hpp"

class DataList {
private:
	int activeElement;
	vector<Record *> records;

public:
	enum class SortBy : int {
		Name = 0,
		Author = 1,
		Signature = 2,
		State = 3,
	};

	DataList();

	void addRecord(Record *r);

	void removeRecord(int i);

	Record *getRecord(int i) const;

	Record *getActiveRecord() const;

	int getActiveElement() const;

	void setActiveElement(int i);

	int getSize() const;

	int next();

	int prev();

	void sort(SortBy sortBy = SortBy::Name);
};


#endif //LIBRARYDB_DATALIST_HPP
