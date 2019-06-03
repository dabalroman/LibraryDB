//
// Created by rd on 02.06.2019.
//

#include "DataList.hpp"

DataList::DataList() {
	activeElement = 0;
}

void DataList::addRecord(Record *r) {
	records.push_back(r);
}

void DataList::removeRecord(const int i) {
	records.erase(records.begin() + i);

	if (activeElement == i) {
		activeElement--;
	}
}

Record *DataList::getRecord(const int i) const {
	return records[i];
}

Record *DataList::getActiveRecord() const {
	return getRecord(activeElement);
}

int DataList::getActiveElement() const {
	return activeElement;
}

void DataList::setActiveElement(const int i) {
	if (i < 0) {
		activeElement = 0;
		return;
	}

	if (i >= records.size() - 1) {
		activeElement = records.size() - 1;
		return;
	}

	activeElement = i;
}

int DataList::getSize() const {
	return records.size();
}

int DataList::next() {
	if (activeElement >= records.size() - 1) {
		return 1;
	}

	activeElement++;
	return 0;
}

int DataList::prev() {
	if (activeElement <= 0) {
		return 1;
	}

	activeElement--;
	return 0;
}

void DataList::sort(DataList::SortBy sortBy) {
	switch (sortBy) {
		case SortBy::Name:
			std::sort(records.begin(), records.end(), Record::compareByName);
			break;
		case SortBy::State:
			std::sort(records.begin(), records.end(), Record::compareByState);
			break;
		case SortBy::Signature:
			std::sort(records.begin(), records.end(), Record::compareBySignature);
			break;
		case SortBy::Author:
			std::sort(records.begin(), records.end(), Record::compareByAuthor);
			break;
	}
}










