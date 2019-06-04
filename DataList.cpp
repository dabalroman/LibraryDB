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

void DataList::removeRecordByID(const int i) {
	if (activeElement == i) {
		setActiveElementByID(0);
	}

	records.erase(records.begin() + i);
}

Record *DataList::getRecordByID(const int i) const {
	return records[i];
}

Record *DataList::getActiveRecord() const {
	return getRecordByID(activeElement);
}

int DataList::getActiveElementID() const {
	return activeElement;
}

int DataList::setActiveElementByID(const int i) {
	if (i < 0) {
		activeElement = 0;
		return 1;
	}

	if (i >= records.size() - 1) {
		activeElement = records.size() - 1;
		return 1;
	}

	if (getRecordByID(i)->hidden) {
		return 1;
	}

	activeElement = i;
	return 0;
}

int DataList::getSize() const {
	return records.size();
}

int DataList::next() {
	//End of list
	if (activeElement >= records.size() - 1) {
		return 1;
	}

	//Search next unhidden element
	int i = activeElement + 1;
	while (i < getSize() && getRecordByID(i)->hidden) {
		i++;
	}

	//Found any?
	if (i >= getSize()) {
		return 1;
	}

	//Set active
	activeElement = i;
	return 0;
}

int DataList::prev() {
	if (activeElement <= 0) {
		return 1;
	}

	//Search next unhidden element
	int i = activeElement - 1;
	while (i > 0 && getRecordByID(i)->hidden) {
		i--;
	}

	//Found any?
	if (i < 0) {
		return 1;
	}

	//Set active
	activeElement = i;
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

void DataList::filter(string &s) {
	for (auto &r : records) {
		r->hidden = !r->matchString(s);
	}

	int i = 0;
	while (i < getSize() && setActiveElementByID(i++));
}










