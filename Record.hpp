//
// Created by rd on 16/05/2019.
//

#ifndef LIBRARYDB_RECORD_HPP
#define LIBRARYDB_RECORD_HPP

#include <string>
#include "Utils.hpp"

using namespace std;

/**
 * Record data class
 */
class Record {
public:
	enum class State : int {
		Available = 0,
		Lend = 1,
		Unavailable = 2,
	};

	string name, description, signature, author;

	bool hidden = false;

private:
	Record::State state;

public:
	/***
	 * Constructor
	 * @param name Book name
	 * @param author Author full name
	 * @param description Description
	 * @param signature Unique book signature
	 */
	Record(string name, string author, string description = "", string signature = "", State state = State::Available)
			: name(std::move(name)),
			  author(std::move(author)),
			  description(std::move(description)),
			  signature(std::move(signature)),
			  state(state) {};

	/***
	 * Copy constructor
	 * @param record Record object to copy
	 */
	Record(const Record &record);

	/**
	 * Get state as int
	 * @return state State as int
	 */
	const int getIntState() const;

	/**
	 * Get state
	 * @return state State
	 */
	const State getState() const;

	/**
	 * Set state from int
	 * @param state State as int
	 */
	void setState(const State &state);

	/**
	 * Returns true if any of fields matches given string
	 * @param s String
	 * @return Bool
	 */
	bool matchString(const string &s);

	/**
	 * Compare Records by name
	 * @param a
	 * @param b
	const  * @re&turn
	 */
	static bool compareByName(Record *a, Record *b);

	/**
	 * Compare Records by Author
	 * @param a
	 * @param b
	 * @return
	 */
	static bool compareByAuthor(Record *a, Record *b);

	/**
	 * Compare Records by Signature
	 * @param a
	 * @param b
	 * @return
	 */
	static bool compareBySignature(Record *a, Record *b);

	/**
	 * Compare Records by State
	 * @param a
	 * @param b
	 * @return
	 */
	static bool compareByState(Record *a, Record *b);
};

#endif //LIBRARYDB_RECORD_HPP
