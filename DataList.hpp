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
		Title = 0,
		Author = 1,
		Signature = 2,
		State = 3,
	};

	/**
	 * Create DataList
	 */
	DataList();

	/**
	 * Add record to list
	 * @param r Record
	 */
	void addRecord(Record *r);

	/**
	 * Remove record from list
	 * @param i Record id
	 */
	void removeRecordByID(int i);

	/**
	 * Get handle to record
	 * @param i Record id
	 * @return Record handle
	 */
	Record *getRecordByID(int i) const;

	/**
	 * Get handle to active record
	 * @return Record handle
	 */
	Record *getActiveRecord() const;

	/**
	 * Get id of an active element
	 * @return id
	 */
	int getActiveElementID() const;

	/**
	 * Set active element by id
	 * @param i id
	 */
	int setActiveElementByID(int i);

	/**
	 * Get list size
	 * @return size
	 */
	int getSize() const;

	/**
	 * Next unhidden record
	 * @return 0 if ok, 1 if error
	 */
	int next();

	/**
	 * Previous unhidden record
	 * @return 0 if ok, 1 if error
	 */
	int prev();

	/**
	 * Sort records by given field
	 * @param sortBy Field to sort by
	 */
	void sort(SortBy sortBy = SortBy::Title);

	/**
	 * Filters out records that do not match string
	 * @param s string
	 */
	void filter(string &s);
};


#endif //LIBRARYDB_DATALIST_HPP
